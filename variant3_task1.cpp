#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

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

constexpr int kNumZones = 2;
constexpr int kMinStock = 5;

std::mutex g_mtx;
std::condition_variable g_cv;
bool need_refill[kNumZones] = {false, false};

std::atomic<int> stock[kNumZones]{15, 12};
std::atomic<bool> checker_finished{false};

std::mutex cout_mtx;

void safe_log(const std::string& msg) {
    std::lock_guard<std::mutex> lock(cout_mtx);
    std::cout << msg << std::flush;
}

void checker_operator() {
    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> consume{1, 3};

    for (int round = 1; round <= 6; ++round) {
        for (int z = 0; z < kNumZones; ++z) {
            std::unique_lock<std::mutex> lk(g_mtx);
            const int q = stock[z].load();
            safe_log("Проверяющий оператор, зона " + std::to_string(z + 1) +
                     ": текущий остаток " + std::to_string(q) + " (раунд " +
                     std::to_string(round) + ")\n");

            if (q >= kMinStock) {
                lk.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                continue;
            }

            need_refill[z] = true;
            g_cv.notify_one();
            g_cv.wait(lk, [z] { return !need_refill[z]; });
            lk.unlock();
        }

        for (int z = 0; z < kNumZones; ++z) {
            stock[z].fetch_sub(consume(rng));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    {
        std::lock_guard<std::mutex> lk(g_mtx);
        checker_finished.store(true);
    }
    g_cv.notify_all();
}

void filler_operator() {
    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> add_qty{8, 15};

    for (;;) {
        std::unique_lock<std::mutex> lk(g_mtx);
        g_cv.wait(lk, [] {
            return need_refill[0] || need_refill[1] || checker_finished.load();
        });

        if (checker_finished.load() && !need_refill[0] && !need_refill[1]) {
            break;
        }

        int zone = -1;
        if (need_refill[0]) {
            zone = 0;
        } else if (need_refill[1]) {
            zone = 1;
        }
        if (zone < 0) {
            continue;
        }

        lk.unlock();
        const int added = add_qty(rng);
        const int before = stock[zone].fetch_add(added);
        safe_log("Оператор пополнения, зона " + std::to_string(zone + 1) + ": +" +
                 std::to_string(added) + " (было " + std::to_string(before) + ")\n");

        lk.lock();
        need_refill[zone] = false;
        g_cv.notify_all();
    }
}

}

int main() {
    init_console_utf8();
    std::cout << "=== Вариант 3, задача 1: склад (mutex + condition_variable + atomic) ===\n";

    std::thread checker(checker_operator);
    std::thread filler(filler_operator);

    checker.join();
    filler.join();

    std::cout << "Итоговые остатки: зона 1 = " << stock[0].load() << ", зона 2 = " << stock[1].load()
              << "\n";
    return 0;
}
