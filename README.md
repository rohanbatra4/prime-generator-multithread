# Prime Number Finder
Experimenting with the use of multithreading for simple applications like generating prime numbers
## Compilation
To compile the file, you will need a C++11 compliant compiler. You can use the following command to compile the file on a Linux or MacOS system:
```
g++ -std=c++11 -pthread prime_finder.cpp -o prime_finder
```
On Windows, you can use the following command:
```
g++ -std=c++11 -lpthread prime_finder.cpp -o prime_finder
```
You can then run the program by executing the binary file:
```
./prime_finder
```
## Usage
The program prompts the user to enter the range of numbers to check for primes. The range should be entered as two integers separated by a space (e.g. 1 100). The program will then find all prime numbers in that range and print them to the console.
## Output example:
```
Enter the range of numbers to check for primes (start end): 1 100
Primes found in the range [1, 100]: 2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97
```

