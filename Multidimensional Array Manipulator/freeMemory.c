/* Connor McGoey */
/* November 9, 2021 */

// This function takes in the a pointer to an array of arrays within dynamic memory and frees the space that was made
// for each array/row based on the user input
int freeMemory(int ***arrayPointer, int arrNum, int Rws) {
	for (int i = 0; i < (arrNum + 1); i++){
		for (int j = 0; j < Rws; j++){
			free(arrayPointer[i][j]);
		}
		free(arrayPointer[i]); 
	}
	free(arrayPointer);
}
