#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <climits>
#include <mutex>
 
std::mutex primes_mutex; // mutex to protect the primes vector

void check_primes(int start, int end, std::vector<int>& primes) { // function to check for primes
    for (int i = start; i <= end; i += 2) { // check only odd numbers
        bool is_prime = true; // assume the number is prime
        for (int j = 3; j <= sqrt(i); j += 2) { // check only odd numbers
            if (i % j == 0) { // if the number is divisible by any number, it is not prime
                is_prime = false; // set the flag to false
                break;
            }
        }
        if (is_prime) { // if the number is prime, add it to the primes vector
            std::lock_guard<std::mutex> lock(primes_mutex); // lock the mutex
            primes.push_back(i); // add the prime to the vector
        }
    }
}

int main() {
    int start, end; // range of numbers to check for primes
    std::cout << "Enter the range of numbers to check for primes (start end): "; // prompt the user for the range
    if(!(std::cin >> start >> end)) { // check if the input is valid
        std::cerr << "Invalid input\n"; // if not, print an error message
        return 1; // and exit
    }
    if(start < 0 || end < start || end > INT_MAX){ // check if the range is valid
        std::cerr << "Invalid range\n"; // if not, print an error message
        return 1; // and exit
    }

    std::vector<int> primes; // vector to store the primes
    std::vector<std::thread> threads; // vector to store the threads

    int range = (end - start) / 4; // calculate the range for each thread
    for (int i = 0; i < 4; i++) { // create 4 threads
        int thread_start = start + (i * range); // calculate the start of the range for the thread
        int thread_end = thread_start + range - 1; // calculate the end of the range for the thread
        if (i == 3) { // if it is the last thread
            thread_end = end; // set the end of the range to the end of the range
        }
        threads.push_back(std::thread(check_primes, thread_start, thread_end, std::ref(primes))); // create the thread
    }

    for (auto& thread : threads) { // wait for all threads to finish
        thread.join(); // join the thread
    }

    std::cout << "Primes found in the range [" << start << ", " << end << "]: "; // print the primes
    for (int prime : primes) { // iterate over the primes
        std::cout << prime << " "; // print the prime
    }
    std::cout << std::endl; // print a new line

    return 0; // exit
}
