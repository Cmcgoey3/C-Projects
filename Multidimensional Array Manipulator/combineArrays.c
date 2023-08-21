/* Connor McGoey */
/* November 9, 2021 */ 


// This function is used to combine the arrays by adding each array's elements at a specific index and 
// placing the sum into the final array. Note the array is the final for loop iteration to ensure the same
// index is being examined.
int combineArrays(int ***arrayPointer, int arrNum, int Rws, int Clmns) {
	for (int i = 0; i < Rws; i++){
		for (int j = 0; j < Clmns; j++){
			for (int k = 0; k < arrNum; k++) {
				arrayPointer[arrNum][i][j] = arrayPointer[arrNum][i][j] + arrayPointer[k][i][j];
			}
		}
	}
}
