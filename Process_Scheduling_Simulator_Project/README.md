# Process Scheduling Simulator

**Author:** Connor McGoey
**Date:** March 20, 2023
**Description:** This program simulates different process scheduling algorithms and calculates various metrics such as average waiting time and average turnaround time.

## How to Use the Makefile

To compile the source code and create the executable, navigate to the directory containing the Makefile and the source code file "process_scheduling_simulator.c" using the terminal. Then, run the following command:
make

This will use the Makefile to compile the source code using the specified compiler flags. It will generate an executable named "process_scheduling_simulator".

To clean up and remove the compiled executable, run:
make clean

## Example Inputs
The file to use as input is provided with processes and their arrival times. This file is a CSV file named "processes.csv". 
After making the executable file via the "make" command, you can run the program with varying inputs such as:

./process_scheduling_simulator

./process_scheduling_simulator 1 2 3 4

./process_scheduling_simulator -f file-does-not-exist.txt

./process_scheduling_simulator -f processes.csv

./process_scheduling_simulator -s processes.csv

./process_scheduling_simulator -r 3 processes.csv

./process_scheduling_simulator -r 12 processes.csv