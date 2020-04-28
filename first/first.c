#include <stdio.h>
#include <stdlib.h>

char entries[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

//int findHyphen(char hexa[16][16], int row, int col);
//int validity(char hexa[16][16], int row, int col, char entry);
//int* solve(char** hexa[16][16]);

int findHyphen(char **hexa){
	int i;
	int j;
	for(i = 0; i < 16; i++){
		for(j = 0; j < 16; j++){
			if(hexa[i][j] == '-'){
				//*row = i;
				//*col = j;
				return 1;
			}
		}
	}
	return 0;
}

int validity(char **hexa, int row, int col, char entry){
	int i;
	int j;
	//int a;
	//int b;
	//int c;

	for(i = 0; i < 16; i++){
		if(hexa[row][i] == entry){
			return 0;
		}
	}
	
	for(j = 0; j < 16; j++){
		if(hexa[j][col] == entry){
			return 0;
		}
	}
	
	int startR = (row/4)*4;
	int startC = (col/4)*4;

	for(i = startR; i < startR + 4; i++){
		for(j = startC; j < startC + 4; j++){
			if(hexa[i][j] == entry){
				return 0;
			}
		}
	}
	
	return 1;
}

int solve(char **hexa){
	//int row;
	//int col;
	int n;
	char entry;
	char temp;
	int count = 0;
	int i;
	int j;
	//search for hyphen
	if(findHyphen(hexa) == 0){
		//if true, no hyphen found. matrix solved
		return 1;
	}

	for(i = 0; i < 16; i++){
		for(j = 0; j < 16; j++){
			if(hexa[i][j] == '-'){
				for(n = 0; n < 16; n++){
					entry = entries[n];
					if(validity(hexa, i, j, entry) == 1){
						temp = entry;
						count++;
					}
					else{
						continue;
					}
				}
				if(count == 1){
					hexa[i][j] = temp;
					solve(hexa);
					return 1;
				}
				/*else if(count > 1){
					break;
				}*/
			}
		}
	}
	return 0;
}

void printHexa(char** arr){
	int i, j;
	for(i = 0; i < 16; i++){
		for(j = 0; j < 16; j++){
			if(j == 15){
				printf("%c", arr[i][j]);
			}
			else{
				printf("%c\t", arr[i][j]);
			}
		}
		if(i != 15){
			printf("\n");
		}
	}
}

int finalCheck(char **hexa){
	int i;
	int j;
	int k;
	int a = 1;
	int b = 1;
	int row = 0;
	int col = 0;
	
	

	//check rows and columns
	for(i = 0; i < 16; i++){
		for(j = 0; j < 15; j++){
			for(k = j + 1; k < 16; k++){
				if(hexa[i][j] == hexa[i][k]){
					a = 0;
				}
			}
		}
	}
	
	for(i = 0; i < 16; i++){
		for(j = 0; j < 15; j++){
			for(k = j + 1; k < 16; k++){
				if(hexa[j][i] == hexa[k][i]){
					b = 0;
				}
			}
		}
	}

	//check 4x4 submatrix
	int startR = (row/4)*4;
	int startC = (col/4)*4;
	// two foru loops etc etc start c - start c + 4

	if(a == 1 && b ==1){
		return 1;
	}
	else{
		return 0;
	}
}

int main(int argc, char** argv){
	
	int i;
	int j;
	//open file
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		return 0;
	}
	//create hexadoku matrix
	char** hexa = (char**) malloc(16*sizeof(char*));
	for(i = 0; i < 16; i++){
		hexa[i] = (char*) malloc(16*sizeof(char*));
	}
	//feed data from file into hexa
	char data;
	for(i = 0; i < 16; i++){
		for(j = 0; j < 16; j++){
			fscanf(fp, "%c\t", &data);
			hexa[i][j] = data;
		}
	}
	
	if(solve(hexa) == 1){
		if(findHyphen(hexa) == 0){
			if(finalCheck(hexa) == 1){
				printHexa(hexa);
			}
			else if(finalCheck(hexa) == 0){
				printf("no-solution");
			}
		}
		else if(findHyphen(hexa) == 1){
			printf("no-solution");
		}
		else if(finalCheck(hexa) == 0){
			printf("no-solution");
		}
	}
	else if(solve(hexa) == 0){
		printf("no-solution");
	}

	for(i = 0; i < 16; i++){
		char* ptr = hexa[i];
		free(ptr);
	}

	free(hexa);

	fclose(fp);

	return 0;
}
