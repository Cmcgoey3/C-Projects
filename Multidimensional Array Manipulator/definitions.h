/* Connor McGoey */
/* November 9, 2021 */

// These macro definitions are used for the print function to ease the clarification
#define ALLBUTLAST 0
#define LASTUNSORTED 1
#define LASTSORTED 2

// Include the individual functions that were made
#include "initializeArrays.c"
#include "printArrays.c"
#include "sortArrays.c"
#include "combineArrays.c"
#include "freeMemory.c"

// Function prototypes for the above included functions
int InitArray(int *** , int , int , int );
int PrintArray(int *** , int , int , int , int );
int combineArrays(int *** , int , int , int );
int arraySort(int *** , int , int , int );
int freeMemory(int *** , int , int);
