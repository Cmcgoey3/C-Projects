/* Connor McGoey */
/* Sunday, October 3, 2021 */


#include <stdio.h> 
#include <time.h>
#include <stdlib.h>

//The following macro definitions are for taking in the number of iterations that the program will run through (ITERATIONS) and whether or not the program will run in debug mode
// if DEBUG is defined, it will run in debug mode, if undefined, it will not.
#define ITERATIONS 3 
#undef DEBUG

//This is the main program that runs through each iteration depending on the macro given
//This program runs through an array of a random size, each time populating the array with numbers ranging from 1 to a power of 10 based on the total iterations, decreasing in range by a factor of 10 each time after
int main (void) {
	printf("Assignment Two \n");

	srand(time(NULL));
	int sizeOfArray; //This variable is used to determine the size of the array, it is used throughout the program to iterate through the array
	//The following section of code containded within the if/else is used todetermine the size of the array based on the number of iterations
	//It checks whether the macro ITERATIONS is set to a number above 1 first, if it is above 1 then it will generate a random number between 1 and 50 times the number of total iterations until
	//the number generated is above or equal to 50. If ITERATIONS is not set to a number greater than 1, the program assigns the sizeOfArray the value of 50.
	
	int run = ITERATIONS; //this variable is used to determine whether ot not some blocks of code will run depending on whether or not the macro ITERATIONS is set to 0. It is used in place of the macro due to complilation errors with the macro within conditionals
	
	if (run != 0){
		if (run > 1){
			sizeOfArray = (rand() % (run * 50));
			while (sizeOfArray < 50) {
				sizeOfArray = (rand() % (run * 50));
			}
		} else {
			sizeOfArray = 50;
		}
	}

	//These print statements print the randomly generated array size and the number of bytes it will take up in memory. The amount of bytes is based on the fact that a single int is 4 bytes.
	if (run != 0) {
		printf("\n	Value of random size of array: %d \n", sizeOfArray);
		printf("	Size of array: %d bytes", (sizeOfArray * 4));
	}
	int array[sizeOfArray]; //This variable is the array that will be used for the remainder of the program to store random values, this array will also store the values once duplcates are removed, and once the numbers are sorted

	int iteration = ITERATIONS; //This variable is used to determine the current iteration of the program, it is set to the macro definition and will decremenet after each run through the following while loop

	int iterationTotal = ITERATIONS; //This variable is set to the total amount of times the program will run, it does not change
	int iterationCount = 1; //This variable counts the amount of times the program has run, it is set to 1 because the variable does not increment until the end of each run through the while loop

	// The following section of code populates the array with random numbers in a range depending on the iteration, prints the original array, removes duplicates from the array, prints again, sorts the array, 
	// and prints a final time 
	while((iteration > 0) && (run != 0)){
		printf("\n\nTHIS IS ITERATION NUMBER: %d of %d", iterationCount, iterationTotal);
		int range = 1; // this variable is used to evaluate the range of number to be populated, it is set to 1 so that it produces whole numbers that are products of 10
		int exponent = iteration; // this variable will be used to count the amount of times the range has to be multiplied by 10, it begins at the iteration amount, and decreases by one after each run through
		
		// the following section evaluates what the range will be for the random numbers to be generated based on the current iteration
		while (exponent != 0) {
			range = range * 10;
			exponent--;
		}
		// debug statement printing the upper range for each iteration
#		if defined ( DEBUG ) 
			printf("\nUpper Range Value: %d", range);
#endif
		// more print statements to preceed the original array in terminal
		printf("\n\n	This is the original array populated with values in the range of 1 and %d \n", range);
		printf("	Number of elements in the original array is: %d\n", sizeOfArray);
		
		// this section of code populates the array with a random number based on the upper range of each iteration
		for(int i = 0; i < sizeOfArray; i++) {
			int numberToAdd = (rand() % range) + 1;
			array[i] = numberToAdd;
		}
		
		int numberPrinted = 0; //this varible will be used each time the program prints out the array, it is a counter to evaluate how many numbers in the array have been printed
		
		//this section of code prints out the elements in the array in an evenly-spaced manner, and prints a new line if the total number of characters printed in a line is to exceed 30
		//this is to ensure that (for most terminal sizes) the array appears neat and evenly spaced
		for(int i = 0; i < sizeOfArray; i++) {
			if (numberPrinted % 30 == 0) {
				printf("\n");
			}
			printf("%6d", array[i]);
			numberPrinted++;
		}
		
		// This section of code runs through each element of the the array and compares it to every other element, if any two elements are even, the array will make that duplicate value 0 and then
		// shift the remaining elements to the left such that the last element in the array will be 0. 
		// NOTE: there are two for loops that run through the array, this is to ensure that no matter how many duplicate elements proceed eachother, they will be replaced with a 0
		// (in the rare case that each element in the array is the same value, this double for-loop will eliminate all but one instance of the number)
		for (int i = 0; i < sizeOfArray; i++) {
			for (int i = 0; i < sizeOfArray; i++){
				for (int j = i + 1; j < sizeOfArray; j++) {
					if (array[i] == array[j]){
						if (array[i] != 0) {
							//The following debug code prints out a line that displays when a duplicate is found, where the indexes of the original/duplicate are, and what the value of the duplicate is
							//Note, those who run the program must remember that the design of the program shifts the elements of the array each time a duplicate is found. 
							//Therefore, the debug's printed lines and array indices may not match those of the original array due to the nature of the program (each time a duplicate is found, the index
							//of the remainding values changes as well)
#if defined ( DEBUG )
							printf("\nThe value of %d at array index %d and the value of %d at array index %d are the same.", array[i], i, array[j], j);
#endif
						}
						array[j] = 0;
						int place = j; //this variable is used to iterate through the array one element at a time starting at the duplicate value to ensure that the index being tested does not change (j)
						for (place; place < sizeOfArray; place++) {
							if (place < (sizeOfArray - 1)) {
								array[place] = array[place + 1];		
							}
							if (place == sizeOfArray) {
								array[place] = 0;
							}
						}
					}
				}
			}
		}

		int uniqueElements = 0; // this variable is used in combination with the below for-loop to count the total number of non-zero values in the array AFTER duplicates have been removed
		//This section of code counts the total non-zero non-duplicate values remaining in the array
		for (int i = 0; i < sizeOfArray; i++) {
			if (array[i] != 0) {
				uniqueElements++;
			}
		}
		// more print statements to be printed before the contents of the updated array including the number of unique elements
		printf("\n\n	This is the current state of the array with all duplicates removed \n");
		printf("	Number of unique (non-zero, non-duplicate) elements in the array is: %d \n", uniqueElements);
		
		numberPrinted = 0; //using the same variable for printing as before, just resetting to 0 in order to preserve memory
		// this section of code prints out the elements of the array evenly spaced out just as before, but also making sure not to print the zeros that exist in the array
		for (int i = 0; i < sizeOfArray; i++) {
			if (numberPrinted % 30 == 0) {
				printf("\n");
			}
			if (array[i] != 0) {
				printf("%6d", array[i]);
				numberPrinted++;
			}
		}

		// this section of code sorts the array in in order from least to greatest
		for (int i = 0; i < sizeOfArray; i++) {
			for (int j = i + 1; j < sizeOfArray; j++) {
				if ((array[j] < array[i]) && (array[j] != 0)) {
					int tempInt = array[i]; //variable used to store an integer value in the array because the following line will replace the value otherwise
					array[i] = array[j];
					array[j] = tempInt;
				} 
			}
		}

		// final print statement to be printed before the final printing of the array
		printf("\n\n	These are unique, non-zero elements in the array sorted in ascending order: \n");
		numberPrinted = 0; // again resetting the same iteratorn to 0
		// this final print section of code will print out the final array in sorted order without the zeros that exist within the array
		for (int i = 0; i < sizeOfArray; i++) {
			if (numberPrinted % 30 == 0) {
				printf("\n");
			}
			if (array[i] != 0) {
				printf("%6d", array[i]);
				numberPrinted++;
			}
		}
		//decrement the amount of iterations left and increment the amount of iterations that have been complete
		iteration--;
		iterationCount++;

	}

	return 0;
}
