#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <climits>
#include <mutex>

std::mutex primes_mutex;

void check_primes(int start, int end, std::vector<int>& primes) {
    for (int i = start; i <= end; i += 2) { 
        bool is_prime = true;
        for (int j = 3; j <= sqrt(i); j += 2) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            std::lock_guard<std::mutex> lock(primes_mutex);
            primes.push_back(i);
        }
    }
}

int main() {
    int start, end;
    std::cout << "Enter the range of numbers to check for primes (start end): ";
    if(!(std::cin >> start >> end)){
        std::cerr << "Invalid input\n";
        return 1;
    }
    if(start < 0 || end < start || end > INT_MAX){
        std::cerr << "Invalid range\n";
        return 1;
    }

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
