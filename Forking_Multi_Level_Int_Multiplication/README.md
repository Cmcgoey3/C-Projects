# Multi-Level Integer Multiplication

## Author
Connor McGoey
Date: February 9, 2023

## Description
This program performs a multi-level integer multiplication operation on two 4-digit integers using a parent-child process model. It splits the calculation into smaller tasks performed by the child process, and then combines the results to obtain the final product.

## Note
This program uses system libraries from Unix-based operating systems for forking processes.

## How to Run/Compile
1. **Compile:** Open a terminal and navigate to the directory containing the source code (`multi_level_integer_multiplication.c`).
    ```bash
    gcc -o main multi_level_integer_multiplication.c
    ```
    This will compile the code and create an executable named `main`.

2. **Run:** After compiling, you can run the program with two 4-digit integers as command line arguments.
    ```bash
    ./main <4_digit_integer> <4_digit_integer>
    ```
    Replace `<4_digit_integer>` with the actual 4-digit integers you want to multiply.

    Example:
    ```bash
    ./main 1234 5678
    ```
    This will perform the multi-level multiplication operation on the integers 1234 and 5678.

3. **Output:** The program will output the steps of the calculation process and the final result.

Note: Make sure you have a C compiler (like GCC) installed on your system before compiling the code and that you are running the program in a Unix-based operating system environment.
