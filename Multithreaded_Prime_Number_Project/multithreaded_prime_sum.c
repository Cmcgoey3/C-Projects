/**
 * Name: Connor McGoey
 * Date: March 3, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

int count = 0;
long long int primeSum = 0;

/**
 * findPrimes method to return the prime numbers between a range. Counts the number of prime numbers between a range and the sum of those prime numbers. Adds the count and sum
 * to the global count and primeSum variables. Takes in a void pointer parameter to an array of information and returns nothing.
*/
void* findPrimes(void* args) {
    // Read from the array pointed at by parameter to retrieve the thread number and the range represented by low and high.
    int* array = (int*)args;
    int thread = array[0];
    int low = array[1];
    int high = array[2];

    // Initialize variables to count the number of primes and their sum for this specific range, print that information after.
    int threadCount = 0;
    long long int threadSum = 0;
    printf("Thread # %d is finding primes from low = %d to high = %d\n", thread, low, high);

    // Iterate until low is not equal to high.
    while (low < high)
    {
        int flag = 0;

        // Ignore numbers less than 2.
        if (low <= 1)
        {
            low++;
            continue;
        }

        // If low is a non-prime number, flag will be 1.
        for (int i = 2; i <= low / 2; i++)
        {
            if (low % i == 0)
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {
            threadCount++;
            threadSum += low;
        }

        // Increment low to check the prime for the next number.
        low++;
    }

    // Print the count and sum of the primes for this range, then add them to the global count and primeSum.
    printf("Sum of thread %d is %lld, Count is %d\n", thread, threadSum, threadCount);
    count += threadCount;
    primeSum += threadSum;

    return 0;
}

// Main driver to create threads and pointers to the information passed to each thread.
int main(int argc, char const* argv[]) {

    // Check for valid command-line argument input.
    if (!(argc == 3))
    {
        printf("Proper usage is ./assignment-3 <threadCount> <highestInt>\n");
        return 0;
    }

    // Typecast the number of threads and range from the command line arguments into integers.
    int numThreads = atoi(argv[1]);
    int range = atoi(argv[2]);

    // Determine the range of values to be checked per thread/
    int perThread = range / numThreads;

    // If the number of threads does not evenly divide the range, increase the perThread variable by 1.
    if (range % numThreads != 0) perThread += 1;

    // Initialize worker threads and an array to contain the worker thread parameters.
    pthread_t workerThread[numThreads];
    int threadNumber[numThreads][3];    // [thread number, low, high].
    for (int i = 0; i < numThreads; i++)
    {
        // Calculate the low and high per thread.
        int low = i * perThread;
        int high;

        // If it is the last thread, the high range will be whatever the range was passes in through the command line. Otherwise, the high will be low + perThread.
        if (i == numThreads - 1) {
            high = range;
        }
        else {
            high = low + perThread;
        }

        // Initialize the parameter array 'threadNumber' with the thread's number and the low/high for that thread
        threadNumber[i][0] = i;
        threadNumber[i][1] = low;
        threadNumber[i][2] = high;
        
        // Create the thread
        if (pthread_create(&workerThread[i], NULL, findPrimes, &threadNumber[i])) {
            printf("Error while creating thread\n");
        }
    }

    // Join the created threads
    for (int i = 0; i < numThreads; i++) {
        if (pthread_join(workerThread[i], NULL)) {
            printf("Error joining with thread");
        }
    }

    // Print final sum and count
    printf("\n\tGRAND SUM IS %lld, COUNT IS %d\n", primeSum, count);

    return 0;
}
