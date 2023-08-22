/**
 * Name: Connor McGoey
 * Date: March 20, 2023
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Custom structure to store process information.
*/
typedef struct Process
{
    int arrived;            // 0 if the process has not arrived, 1 if it has
    int arrivalTime;        // 0 being arrived at the beginning
    int burstTime;          // burst time in number of ticks
    int waitTime;           // how long the process has been waiting
    int turnAroundTime;     // the accumulated turnaround time for the process
    int pNum;               // process number
    int isActive;           // flag to determine whether or not the process is active. 1 for active, 0 for inactive
} Process;

/**
 * Custom comparator to compare two processesm for use in the Shortest Job First algorith.
 * Preference is for processes that have arrived before those who have not.
 * Secondary comparison is which process has the lower burst time.
*/
int ProcessComparatorSJF(const void* a, const void* b) {
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;
    if (p1->arrived == 1 && p2->arrived == 0) {
        return -1;
    }
    if (p2->arrived == 1 && p1->arrived == 0) {
        return 1;
    } else {
        if (p1->burstTime < p2->burstTime) {
            return -1;
        }
        if (p2->burstTime < p1->burstTime) {
            return 1;
        } else {
            return 0;
        }
    }
}

/**
 * Helper function to the first process in the dynamic memory processes queue and reallocate memory accordingly.
 * Returns the the amount of elements in the queue.
*/
int deleteProcess(Process* processes, int processIndex){
    for (int i = 0; i < processIndex - 1; i++) {
        processes[i] = processes[i+1];
    }
    processIndex--;
    processes = (Process*)realloc(processes, processIndex * sizeof(Process));
    return processIndex;
}

/**
 * Helper function to update processes in the queue based on conditions.
 * The wait time will  incremented every time the current time is greater than or equal to the arrival time, 
 * the burst time is not 0, and it is not the active process. The turnaround time will be incremented every 
 * time the current time is greater than or equal to the arrival time, and the burst time is not 0. This is 
 * irrespective of whether this is the active process or not
*/
void updateProcesses(Process* processes, int numProcesses, int currentTime){
    for (int i = 0; i < numProcesses; i++) {
        if (currentTime >= (processes[i].arrivalTime) && processes[i].isActive == 0) {
            processes[i].waitTime++;
        }
        if (currentTime >= (processes[i].arrivalTime)) {
            processes[i].turnAroundTime++;
            processes[i].arrived = 1;
        }

    }
}

// Main program driver
int main(int argc, char const *argv[])
{
    // Initialize variables for which algorithm was passed, the time quantum, and file name
    int algorithm, quantum;
    char filename[100];
    argc = argc;
    argv = argv;

    if (argc == 1 || argc > 4) {    // Error check for incorrect amount of arguments passed
        printf("Proper usage is ./assignment-4 [-f|-s|-r <quantum>] <Input file name>\n");
        return 0;
    }
    else {
        if (strcmp(argv[1], "-f") == 0) {   // If the algorithm to be used is First Come First Serve
            algorithm = 0;
            printf("First Come First Served\n");
            strcpy(filename, argv[2]);
        }
        if (strcmp(argv[1], "-s") == 0) {   // If the algorithm to be used is Shortest Job first
            algorithm = 1;
            printf("Shortest Job First\n");
            strcpy(filename, argv[2]);
        }
        if (strcmp(argv[1], "-r") == 0) {   // If the algorithm to be used is Round Robin
            algorithm = 2;
            quantum = atoi(argv[2]);
            printf("Round Robin with Quantum %d\n", quantum);
            strcpy(filename, argv[3]);
        }
    }

    // Initialize the number of processes passed and the index to keep track of how many processes are still in the queue 
    int numProcesses = 0;
    int processIndex = 0;

    // Pointer to be used to point to a dynamic memory array of Process objects
    Process* processes = NULL;
    
    // Variable to keep track of the arrival time of a process, first one is 0
    int arrival = 0;

    // Initialize variables to keep track of the process number, the burst of the process, and the file pointer
    int process, burst;
    char buffer[100];
    FILE* ptr;
    
    if (!(ptr = fopen(filename, "r"))) {    // Error check to see if the file to be used exists
        printf("Could not open %s\n", filename);
        return 0;
    }
    while (fscanf(ptr, "%s", buffer) == 1){ // Read from the file passed
        // Parse each line for the process number and burst amount
        char * token = strtok(buffer, ",");
        char* p = token + 1;
        process = atoi(p);
        token = strtok(NULL, " ");
        burst  = atoi(token);

        // Create a new process with the information, set the wait time, turnaround time, active flag, and arrived flag to 0
        Process* newProcess = (Process*)malloc(sizeof(Process));
        newProcess->arrivalTime = arrival;
        newProcess->burstTime = burst;
        newProcess->waitTime = 0;
        newProcess->turnAroundTime = 0;
        newProcess->pNum = process;
        newProcess->isActive = 0;
        newProcess->arrived = 0;

        // Incremenet counters
        processIndex++;
        numProcesses++;
        arrival++;

        // Copy the process to the dynamic memory region
        processes = (Process*)realloc(processes, processIndex * sizeof(Process));
        processes[processIndex - 1] = *newProcess;

        // Free the created process
        free(newProcess);
    }

    if (algorithm == 0) {   // For First Come First Serve
        int time = 0;           // Initialize the current time/tick to 0
        float avgWait = 0;      // Initialize total/average wait time of all processes to 0
        float avgTurnaround = 0;    // Initialize total/average turnaround time of all processes to 0
        while (processIndex > 0) {  // While there are still processes in the queue
            // Set the first process to the active process and obtain the information for printing
            processes[0].isActive = 1;
            int processID = processes[0].pNum;
            int burstLeft = processes[0].burstTime;
            int waitTime = processes[0].waitTime;
            int turnaround = processes[0].turnAroundTime;
            printf("T%d : P%d  - Burst left  %d, Wait time  %d, Turnaround time  %d\n", time, processID, burstLeft, waitTime, turnaround);

            // Update processes in the queue
            updateProcesses(processes, processIndex, time);

            // Decrease burst time of the current active processes and incremene the time/tick
            processes[0].burstTime--;
            time++;
            
            // If the current process has finished
            if (processes[0].burstTime == 0) {
                // Add the process' turnaround time and wait time to the total variables
                avgTurnaround  = avgTurnaround + processes[0].turnAroundTime;   
                avgWait = avgWait + processes[0].waitTime;
                processIndex = deleteProcess(processes, processIndex);  // Delete the process
            }
        }
        // Find the average wait time and turnaround time by dividing by the original amount of processes
        avgWait = avgWait / numProcesses;
        avgTurnaround = avgTurnaround / numProcesses;

        printf("\n\nTotal average waiting time:\t %.1f\n", avgWait);
        printf("Total average turnaround  time:\t %.1f\n\n", avgTurnaround);
    }
    
    if (algorithm == 1) {   // If the algorithm is Shortest job First
        processes[0].arrived = 1;   // Set process P0.arrived to 1 for the quicksort algorithm

        // Sort the processes based on the ProcessComparatorSJF comparator
        qsort(processes, processIndex, sizeof(Process), ProcessComparatorSJF);

        int time = 0;           // Initialize the current time/tick to 0
        float avgWait = 0;      // Initialize total/average wait time of all processes to 0
        float avgTurnaround = 0;    // Initialize total/average turnaround time of all processes to 0
        while (processIndex > 0) {  // While there are still processes
            // Set the first process to the active process and obtain the information for printing
            processes[0].isActive = 1;
            int processID = processes[0].pNum;
            int burstLeft = processes[0].burstTime;
            int waitTime = processes[0].waitTime;
            int turnaround = processes[0].turnAroundTime;
            printf("T%d : P%d  - Burst left  %d, Wait time  %d, Turnaround time  %d\n", time, processID, burstLeft, waitTime, turnaround);
            
            // Update processes in the queue
            updateProcesses(processes, processIndex, time);

            // Decrease burst time of the current active processes and incremene the time/tick
            processes[0].burstTime--;
            time++;
            
            // If the current process has finished
            if (processes[0].burstTime == 0) {
                // Add the process' turnaround time and wait time to the total variables
                avgTurnaround  = avgTurnaround + processes[0].turnAroundTime;
                avgWait = avgWait + processes[0].waitTime;
                // Delete the process
                processIndex = deleteProcess(processes, processIndex);
            }

            // Sort the processes again after every tick to move the process with the shortest time remaining to the front
            qsort(processes, processIndex, sizeof(Process), ProcessComparatorSJF);


        }

        // Find the average wait time and turnaround time by dividing by the original amount of processes
        avgWait = avgWait / numProcesses;
        avgTurnaround = avgTurnaround / numProcesses;

        printf("\n\nTotal average waiting time:\t %.1f\n", avgWait);
        printf("Total average turnaround  time:\t %.1f\n\n", avgTurnaround);
    }
    
    if (algorithm == 2) {   // If the algorithm is Round Robin
        int time = 0;           // Initialize the current time/tick to 0
        float avgWait = 0;      // Initialize total/average wait time of all processes to 0
        float avgTurnaround = 0;    // Initialize total/average turnaround time of all processes to 0
        int timeCycle = 0;  // Variable to keep track of the current time cycle. Used in comparison to the time quantum
        while (processIndex > 0) {  // While there are still processes in the queue
            // Set the first process to the active process and get the information for printing
            processes[0].isActive = 1;
            int processID = processes[0].pNum;
            int burstLeft = processes[0].burstTime;
            int waitTime = processes[0].waitTime;
            int turnaround = processes[0].turnAroundTime;
            printf("T%d : P%d  - Burst left  %d, Wait time  %d, Turnaround time  %d\n", time, processID, burstLeft, waitTime, turnaround);

            // Update processes, reduce the burst time of the current process, and increment the total time and the time cycle
            updateProcesses(processes, processIndex, time);
            processes[0].burstTime--;
            time++;
            timeCycle++;
            
            // If the current process has finished
            if (processes[0].burstTime == 0) {
                // Add the process' turnaround time and wait time to the total variables
                avgTurnaround  = avgTurnaround + processes[0].turnAroundTime;
                avgWait = avgWait + processes[0].waitTime;
                // Delete the process
                processIndex = deleteProcess(processes, processIndex);
                timeCycle = 0; // Reset the time cycle to 0
            }

            // If the process has not finished, but has run out of time
            if (timeCycle == quantum) {
                // Copy the process into a new Process object
                Process* processCopy = (Process*)malloc(sizeof(Process));
                processCopy->arrivalTime = processes[0].arrivalTime;
                processCopy->burstTime = processes[0].burstTime;
                processCopy->waitTime = processes[0].waitTime;
                processCopy->turnAroundTime = processes[0].turnAroundTime;
                processCopy->pNum = processes[0].pNum;
                processCopy->isActive = 0;      // Set the active flag to 0
                processCopy->arrived = processes[0].arrived;

                // Shift all arrived processes to the left and place the copied process between the arrived and not arrived processes
                int index = 0;
                while ((index + 1) < processIndex && processes[index + 1].arrived == 1) {
                    processes[index] = processes[index + 1];
                    index++;
                }
                processes[index] = *processCopy;

                // Free the copy process
                free(processCopy);

                // Rest the time cycle
                timeCycle = 0;
            }
            
        }
        // Find the average wait time and turnaround time by dividing by the original amount of processes
        avgWait = avgWait / numProcesses;
        avgTurnaround = avgTurnaround / numProcesses;

        printf("\n\nTotal average waiting time:\t %.1f\n", avgWait);
        printf("Total average turnaround  time:\t %.1f\n\n", avgTurnaround);
    }

    return 0;
}
