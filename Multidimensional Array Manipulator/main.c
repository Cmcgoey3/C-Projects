/* Connor McGoey */
/* November 9, 2021 */

#include "headers.h"

// This is the main function of the program which prompts the user repetitiously until they input 0 to terminate
// the program. It prompts for a number of arrays, and then rows and columns. The original pointer to the dynamic
// memory along with the user input is then passed to other functions to populate, print, sort, or free
// the dynamic memory.
int main() {
	int nArrs, row, column; // Variables for number of arrays, rows, and columns
	int ***nTables;		// Triple pointer variable that is the root pointer for the arrays
	
	printf("\nEnter the number of arrays (0 to quit):"); 
	scanf("%d", &nArrs);
	
	while (nArrs != 0) {
		
		printf("\nEnter values for Rows, Columns (e.g. 2 3):");
		scanf("%d %d", &row, &column);

		nTables = (int ***)calloc(nArrs + 1, sizeof(int **));

		InitArray(nTables, nArrs, row, column);

		PrintArray(nTables, nArrs, row, column, ALLBUTLAST);

		combineArrays(nTables, nArrs, row, column);

		PrintArray(nTables, nArrs, row, column, LASTUNSORTED);

		arraySort(nTables, nArrs, row, column);

		PrintArray(nTables, nArrs, row, column, LASTSORTED);

		freeMemory(nTables, nArrs, row);

		printf("\n\n\nXXXXXX END OF SESSION XXXXXX \n\n");

		printf("\nEnter the number of arrays (0 to quit):");
		scanf("%d", &nArrs);
	}
}
			
