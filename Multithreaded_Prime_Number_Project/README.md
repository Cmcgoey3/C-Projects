# Multithreaded Prime Number Sum Calculator

## Author
Connor McGoey
Date: March 3, 2023

## Description
This program calculates the sum and count of prime numbers within a given range using multithreading. It divides the range into smaller segments and assigns each segment to a separate thread for parallel processing. The prime numbers found are accumulated to calculate the total sum and count of prime numbers within the specified range.

## How to Run
To compile and run this program, follow these steps:

1. **Compile:** Open a terminal and navigate to the directory containing the source code `multithreaded_prime_sum.c`.
    ```bash
    gcc -o multithreaded_prime_sum multithreaded_prime_sum.c -pthread -lm
    ```
    This will compile the code and create an executable named `multithreaded_prime_sum`. Note the use of the `-pthread` flag for linking the pthread library and the `-lm` flag for linking the math library.

2. **Run:** After compiling, you can run the program with the desired number of threads and the highest integer to check for prime numbers as command-line arguments.
    ```bash
    ./multithreaded_prime_sum <threadCount> <highestInt>
    ```
    Replace `<threadCount>` with the desired number of threads to use for processing and `<highestInt>` with the highest integer within the range to check for prime numbers.

    Example:
    ```bash
    ./multithreaded_prime_sum 4 1000000
    ```
    This will use 4 threads to calculate the sum and count of prime numbers within the range from 1 to 1000000.

3. **Output:** The program will output progress messages for each thread's processing, as well as the final sum and count of prime numbers across all threads.

## Note for Unix-Based Environments
This program uses POSIX threads (`pthread`) for multithreading and the math library (`-lm`) for mathematical calculations. Therefore, it is designed to be run in a Unix-based environment (e.g., Linux, macOS). Ensure that you have a C compiler (like GCC) installed on your system before compiling the code.

Keep in mind that multithreading introduces complexities like synchronization and potential race conditions. The code handles these aspects internally, but it's important to understand the concepts if you're modifying or adapting this code for other purposes.

Please remember to adjust the compilation and running instructions according to your system and the actual name of the source code file if it's different from `multithreaded_prime_sum.c`.
