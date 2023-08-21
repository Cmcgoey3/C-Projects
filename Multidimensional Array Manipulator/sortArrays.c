/* Connor McGoey */
/* November 9, 2021 */ 

// This function takes in the original triple pointer and the user input for the number of arrays, rows, and columns,
// and then sorts the last array. To do this, it makes use of the known information that the final array is the same
// size as other arrays depending on the number of rows and columns. Using this information, the function creates
// a one-dimensional array of the size of rows x columns, sorts the created array, and then places those values back 
// into the array in memory.
int arraySort(int ***arrayPointer, int arrNum, int Rws, int Clmns) {
	int tempArr[Rws * Clmns]; // The one-dimensional array to be used to sort the elements
	int arrIndex = 0;	  // Setting the array index to properly populate the tempArr array.
	for (int i = 0; i < Rws; i++) {
		for (int j = 0; j < Clmns; j++) {
			tempArr[arrIndex] = arrayPointer[arrNum][i][j];
			arrIndex++;
		}
	}
	for (int i = 0; i < arrIndex; i++) {
		for (int j = i + 1; j < arrIndex; j++) {
			if (tempArr[j] < tempArr[i]) {
				int temp = tempArr[i];
				tempArr[i] = tempArr[j];
				tempArr[j] = temp;
			}
		}
	}
	arrIndex = 0; // Reset the index back to 0 so that the repopulation is in correct order.
	for (int i = 0; i < Rws; i++) {
		for (int j = 0; j < Clmns; j++) {
			arrayPointer[arrNum][i][j] = tempArr[arrIndex];
			arrIndex++;
		}
	}
}
