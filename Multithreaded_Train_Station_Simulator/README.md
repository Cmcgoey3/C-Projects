# Multithreaded Train Station Simulator

## Author
- Name: Connor McGoey
- Date: March 27, 2023

## Description
The **Multithreaded Train Station Simulator** is a program written in C that simulates the operation of a train station with multiple trains and passenger stations. The project uses multithreading to simulate trains arriving at and departing from stations, picking up and dropping off passengers based on predefined capacities.

## How to Run/Compile
To compile and run the program, follow these steps:

1. Open a terminal in your Unix-based system.
2. Navigate to the directory containing the `train_station_simulation.c` file.
3. Compile the program using the following command:
    gcc -o train_station_simulation train_station_simulation.c -pthread -lm
4. After compilation, you can run the program with the following command:
    ./train_station_simulation
5. The simulation will start, and you'll see the interactions between trains and stations in the terminal output.

## Usage in Unix-based System
This project is designed to be used in a Unix-based system. The program utilizes POSIX threads (pthreads) for multithreading, which is a standard feature in Unix-like operating systems. The `-pthread` flag is used during compilation to link the pthread library, and the `-lm` flag is used to link the math library for the `math.h` functions used in the program.

**Note**: If you're using a system other than Unix-based (such as Windows), you may need to adapt the program and build process accordingly.

