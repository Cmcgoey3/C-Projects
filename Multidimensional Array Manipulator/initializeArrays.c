/* Connor McGoey */
/* November 9, 2021 */

// This function takes in a triple pointer, the the following from user input: number of arrays, number of rows,
// and number of columns. Using this information, more space is allocated in dynamic memory for the arrays which are
// created and populated with random numbers based on the following upper limit: 
// (number of arrays x number of rows x number of columns x 10)
//
// The final for loop is to populate the final array with zeros which will be used later on.
int InitArray(int ***arrayPointer, int arrNum, int Rws, int Clmns) {
	int randNum = arrNum * Rws * Clmns * 10; // The upper limit of the random number to be generated
	for (int i = 0; i < (arrNum + 1); i++) {
		arrayPointer[i] = (int **)calloc(Rws, sizeof(int *));
		for (int j = 0; j < Rws; j++) {
			arrayPointer[i][j] = (int *)calloc(Clmns, sizeof(int));
		}
	}
	for (int i = 0; i < arrNum; i++) {
		for (int j = 0; j < Rws; j++) {
			for (int k = 0; k < Clmns; k++) {
				arrayPointer[i][j][k] = (rand() % randNum);
			}
		}
	}
	for (int i = 0; i < Rws; i++) {
		for (int j = 0; j < Clmns; j++) {
			arrayPointer[arrNum][i][j] = 0;
		}
	}
}
