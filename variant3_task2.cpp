#include <chrono>
#include <iostream>
#include <mutex>
#include <semaphore>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

static void init_console_utf8() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

namespace {

std::binary_semaphore sem_load_allow{1};
std::binary_semaphore sem_process_allow{0};
std::binary_semaphore sem_pack_allow{0};

std::mutex cout_mtx;

void log_line(const std::string& line) {
    std::lock_guard<std::mutex> lock(cout_mtx);
    std::cout << line << std::endl;
}

void stage_load(int item_id) {
    sem_load_allow.acquire();
    log_line("[Загрузка]  начало партии материала #" + std::to_string(item_id));
    std::this_thread::sleep_for(std::chrono::milliseconds(400 + (item_id * 30) % 200));
    log_line("[Загрузка]  материал #" + std::to_string(item_id) + " подан на обработку");
    sem_process_allow.release();
}

void stage_process(int item_id) {
    sem_process_allow.acquire();
    log_line("[Обработка] начало обработки #" + std::to_string(item_id));
    std::this_thread::sleep_for(std::chrono::milliseconds(500 + (item_id * 40) % 250));
    log_line("[Обработка] деталь #" + std::to_string(item_id) + " готова к упаковке");
    sem_pack_allow.release();
}

void stage_pack(int item_id) {
    sem_pack_allow.acquire();
    log_line("[Упаковка]  упаковка готовой продукции #" + std::to_string(item_id));
    std::this_thread::sleep_for(std::chrono::milliseconds(350 + (item_id * 25) % 150));
    log_line("[Упаковка]  продукт #" + std::to_string(item_id) + " отправлен на склад");
    sem_load_allow.release();
}

}

int main() {
    init_console_utf8();
    std::cout << "=== Вариант 3, задача 2: конвейер (std::binary_semaphore) ===\n";

    const int kItems = 5;
    std::vector<std::thread> threads;
    threads.reserve(3);

    threads.emplace_back([kItems] {
        for (int i = 1; i <= kItems; ++i) {
            stage_load(i);
        }
    });
    threads.emplace_back([kItems] {
        for (int i = 1; i <= kItems; ++i) {
            stage_process(i);
        }
    });
    threads.emplace_back([kItems] {
        for (int i = 1; i <= kItems; ++i) {
            stage_pack(i);
        }
    });

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Все " << kItems << " единиц прошли этапы: загрузка -> обработка -> упаковка.\n";
    return 0;
}
