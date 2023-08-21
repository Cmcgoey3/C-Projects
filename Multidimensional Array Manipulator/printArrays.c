/* Connor McGoey */
/* November 9, 2021 */

// This function prints the array in one of three ways depending on the value of printNum (PN). If PN is 0,
// (ALLBUTLAST as the preprocessor definition) it prints all but the last array. If PN is 1, (LASTUNSORTED as
// the preprocessor definition) it prints the final array with the prefixed statement telling the user the
// final array is unsorted. Finally, if PN is 2 (LASTSORTED as the preprocessor definition), it will print
// the last array with a prefixed statement telling the user the array is sorted.
int PrintArray(int ***arrayPointer, int arrNum, int Rws, int Clmns, int printNum) {
	if (printNum == 0) {
		for (int i = 0; i < arrNum; i++) {
			printf("\n\nArray Number %d:\n", (i + 1));
			for (int j = 0; j < Rws; j++) {
				printf("\n");
				for (int k = 0; k < Clmns; k++) {
					printf("%5d  ", arrayPointer[i][j][k]);
				}
			}
		}
	}
	if ((printNum == 1) || (printNum == 2)) {
		if (printNum == 1) printf("\n\nLast Array Unsorted: \n");
		if (printNum == 2) printf("\n\nLast Array Sorted: \n");
		for (int i = 0; i < Rws; i++){
			printf("\n");
			for (int j = 0; j < Clmns; j++){
				printf("%5d  ", arrayPointer[arrNum][i][j]);
			}
		}
	}
}
