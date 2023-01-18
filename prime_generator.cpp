#include <iostream>
#include <thread>
#include <vector>
#include <cmath>

void check_primes(int start, int end, std::vector<int>& primes) {
    for (int i = start; i <= end; i++) {
        bool is_prime = true;
        for (int j = 2; j <= sqrt(i); j++) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            primes.push_back(i);
        }
    }
}

int main() {
    int start, end;
    std::cout << "Enter the range of numbers to check for primes: ";
    std::cin >> start >> end;

    std::vector<int> primes;
    std::vector<std::thread> threads;

    int range = (end - start) / 4;
    for (int i = 0; i < 4; i++) {
        int thread_start = start + (i * range);
        int thread_end = thread_start + range - 1;
        if (i == 3) {
            thread_end = end;
        }
        threads.push_back(std::thread(check_primes, thread_start, thread_end, std::ref(primes)));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Primes found in the range [" << start << ", " << end << "]: ";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}
