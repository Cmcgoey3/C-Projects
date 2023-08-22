/**
 * Name: Connor McGoey
 * Date: March 27, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

/**
 * Initialize variables for the stations, trains, and maximum train capacity.
 * Station0 is positive to represent how many passengers remain to be transported.
 * Stations 1-4 are negative to represent how many passengers are to be taken to those stations.
*/
int station0 = 500;
int station1 = -50;
int station2 = -100;
int station3 = -250;
int station4 = -100;

int train0Cap = 100;
int train1Cap = 50;
int train0 = 0;
int train1 = 0;

// Array of pointers to the station to be user as pass-by-reference to helper functions
int* stations[4] = {&station1, &station2, &station3, &station4};

// Mutex locks for each station and standard output
pthread_mutex_t s0;
pthread_mutex_t s1;
pthread_mutex_t s2;
pthread_mutex_t s3;
pthread_mutex_t s4;
pthread_mutex_t STDOUT;

// Helper function to get the address of one of the two trains based off of their integer representation 0 or 1
int* getTrain(int trainNum) {
    if (trainNum == 0) {
        return &train0;
    }
    return &train1;
}

// Helper function to lock a station, using an integer 0-4 to represent which station to lock
void lockStation(int station) {
    if (station == 0) {
        pthread_mutex_lock(&s0);
    } else if (station == 1) {
        pthread_mutex_lock(&s1);
    } else if (station == 2) {
        pthread_mutex_lock(&s2);
    } else if (station == 3) {
        pthread_mutex_lock(&s3);
    } else if (station == 4) {
        pthread_mutex_lock(&s4);
    }
}

// Helper function to unlock a station, using an integer 0-4 to represent which station to unlock
void unlockStation(int station) {
    if (station == 0) {
        pthread_mutex_unlock(&s0);
    } else if (station == 1) {
        pthread_mutex_unlock(&s1);
    } else if (station == 2) {
        pthread_mutex_unlock(&s2);
    } else if (station == 3) {
        pthread_mutex_unlock(&s3);
    } else if (station == 4) {
        pthread_mutex_unlock(&s4);
    }
}

/**
 * Helper function to pick up passengers from station 0. Takes in an integer representing which train is picking up as parameter.
 * Depending on the train's capacity and how many passengers remain, the train will fill itself either until full or until there are 
 * no remaining passengers at the station.
*/
void pickUpPassengers(int train) {
    printf("Train %d ENTERS Station 0\n", train);
    printf("\tStation 0 has %d passengers to pick up\n", station0);
    printf("\tPicking up passengers...\n");
    if (train == 0) {
        if (station0 >= train0Cap) {
            sleep(train0Cap / 10);
            station0 -= train0Cap;
            train0 = train0Cap;
        } else {
            sleep(station0 / 10);
            train0 = station0;
            station0 = 0;
        }
        printf("\tTrain 0 is at Station 0 and has %d/%d passengers\n", train0, train0Cap);
    } else if (train == 1) {
        if (station0 >= train1Cap) {
            sleep(train1Cap / 10);
            station0 -= train1Cap;
            train1 = train1Cap;
        } else {
            sleep(station0 / 10);
            train1 = station0;
            station0 = 0;
        }
        printf("\tTrain 1 is at Station 0 and has %d/%d passengers\n", train1, train1Cap);
    }
    printf("\tStation 0 has %d passengers to pick up\n", station0);
}

/**
 * Helper function to drop of passengers at a station. Parameters are a pointer to the train at the station and a pointer
 * to the station itself. If the station is already full, then nothing happens. Otherwise, unload the passengers until either
 * the station itself is full or the train is empty.
*/
void dropOffPassengers(int* train, int* station) {
    if (abs(*station) > 0) {
        printf("\tUnloading passengers...\n");
        if (*train >= abs(*station)) {
            sleep((*train - abs(*station)) / 10);
            *train -= abs(*station);
            *station = 0;
        } else if (*train < abs(*station)) {
            sleep(*train / 10);
            *station += *train;
            *train = 0;
        }
    }
}

/**
 * Void function to be passed to each thread, takes in a pointer parameter which houses only the train number.
 * Starts at station 0, fills the train using the helper function, traverses each station 1-4 until there are no passengers
 * remaining on the train. Locks each station using the mutex lock along with the standard output upon arrival at a station,
 * unlocks them upon exit. After the train has emptied, traverse back each station in reverse order.
*/
void* trainSim(void* args) {
    int* array = (int*)args;
    int trainNum = array[0];
    int* train = getTrain(trainNum);
    int trainCap;
    if (trainNum == 0) {
        trainCap = train0Cap;
    } else {
        trainCap = train1Cap;
    }

    lockStation(0);
    pthread_mutex_lock(&STDOUT);
    pickUpPassengers(trainNum);
    printf("Train %d LEAVES Station 0\n", trainNum);
    pthread_mutex_unlock(&STDOUT);
    unlockStation(0);

    int stationIndex = 0;
    while (*train != 0) {
        lockStation(stationIndex + 1);
        pthread_mutex_lock(&STDOUT);

        printf("Train %d ENTERS Station %d\n", trainNum, stationIndex + 1);
        printf("\tStation %d has %d passengers to drop off\n", stationIndex + 1, abs(*stations[stationIndex]));
        dropOffPassengers(train, stations[stationIndex]);
        printf("\tTrain %d is at Station %d and has %d/%d passengers\n", trainNum, stationIndex + 1, *train, trainCap);
        printf("\tStation %d has %d passengers to drop off\n", stationIndex + 1, abs(*stations[stationIndex]));
        printf("Train %d LEAVES Station %d\n", trainNum, stationIndex + 1);

        pthread_mutex_unlock(&STDOUT);
        unlockStation(stationIndex + 1);
        stationIndex++;
    }
    stationIndex -= 2;
    while (stationIndex >= 0) {
        lockStation(stationIndex + 1);
        pthread_mutex_lock(&STDOUT);

        printf("Train %d ENTERS Station %d\n", trainNum, stationIndex + 1);
        printf("\tStation %d has %d passengers to drop off\n", stationIndex + 1, abs(*stations[stationIndex]));
        printf("\tTrain %d is at Station %d and has %d/%d passengers\n", trainNum, stationIndex + 1, *train, trainCap);
        printf("\tStation %d has %d passengers to drop off\n", stationIndex + 1, abs(*stations[stationIndex]));
        printf("Train %d LEAVES Station %d\n", trainNum, stationIndex + 1);

        pthread_mutex_unlock(&STDOUT);
        unlockStation(stationIndex + 1);
        stationIndex--;
    }

    return 0;
}

/**
 * Main function driver. 
*/
int main(int argc, char const *argv[])
{

    (void)argv;
    (void)argc;

    // Initialize the mutex locks, thread variables, and parameters to be passed to each thread.
    if (pthread_mutex_init(&s0, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
    if (pthread_mutex_init(&s1, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
    if (pthread_mutex_init(&s2, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
    if (pthread_mutex_init(&s3, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
    if (pthread_mutex_init(&s4, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
    if (pthread_mutex_init(&STDOUT, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    pthread_t t0, t1;
    int t0Arg[1] = {0};
    int t1Arg[1] = {1};

    // While there are still passengers that need to be transported, create one thread for each train.
    while (station0 > 0) {
        // Start the train 1 thread and then wait a couple seconds
        if (pthread_create(&t0, NULL, trainSim, &t0Arg)) {
            printf("Error while creating thread\n");
        }
        sleep(2);
        // Start the train 2 thread
        if (pthread_create(&t1, NULL, trainSim, &t1Arg)) {
            printf("Error while creating thread\n");
        }
        // Join the two threads after returning
        if (pthread_join(t0, NULL)) {
            printf("Error joining with thread");
        }
        if (pthread_join(t1, NULL)) {
            printf("Error joining with thread");
        }
    }
    // Destroy the mutex locks
    pthread_mutex_destroy(&s0);
    pthread_mutex_destroy(&s1);
    pthread_mutex_destroy(&s2);
    pthread_mutex_destroy(&s3);
    pthread_mutex_destroy(&s4);
    pthread_mutex_destroy(&STDOUT);
    return 0;
}
