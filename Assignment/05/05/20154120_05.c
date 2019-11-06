#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

void printIndex(int cnt, int value, FILE* fp) {
	int cipher = 1;
	char num[4] = "000";
	sprintf(num, "%d", cnt);
	char s[10] = "[000]";
	int temp = cnt;
	int idx = 0;

	while (temp / 10 >= 1) {
		cipher++;
		temp /= 10;
	}
	for (int i = 1; i < strlen(s) - 1; i++) {
		if (i < strlen(s) - 1 - cipher)
			s[i] = '0';
		else {
			s[i] = num[idx];
			idx++;
		}
	}
	fprintf(fp, "%s %d\n", s, value);
}

int sumNumbers(int* inputArr, int curr, int index, FILE* fp){
	int sumResult = 0;
	// basis step
	if (index <= curr) {
		return 0;
	}
	// recursive step
	else {
		sumResult += inputArr[curr];
		sumResult += sumNumbers(inputArr, ++curr, index, fp);
		printIndex(curr, sumResult, fp);
		return sumResult;
	}
}

int main(int argc, char* argv[]) {
	FILE* fp1, * fp2;
	char inputStr[64];   // change the number appropriately to your program
	int numInput;
	int* inputArr;
	int result;
	// read_file = argv[1]
	// write_file = argv[2]
	// see the usage of r, rt, w, wt, r+, w+
	if ((fp1 = fopen(argv[1], "r")) == NULL) { //fail to open file for read
		printf("fail to open file.");
		return 0;
	}
	if ((fp2 = fopen(argv[2], "wt")) == NULL) { //fail to open file for write
		printf("fail to create file for write.");
		return 0;
	}

	fgets(inputStr, sizeof(inputStr), fp1);
	numInput = atoi(inputStr);
	inputArr = (int*)calloc(numInput, sizeof(int));

	for (int i = 0; i < numInput; i++) {
		fgets(inputStr, sizeof(inputStr), fp1);
		inputArr[i] = atoi(inputStr);
	}

	result = sumNumbers(inputArr, 0, numInput, fp2);

	fputs("1q2w3e4r!@#1q2w3e4r!@#1\n", fp2);
	fputs("Seong Hyun\n", fp2);
	fputs("Student ID : 20154120\n", fp2);
	fputs("q2w3e4r!@#1q2w3e4r!@#1q\n", fp2);

	free(inputArr);
	fclose(fp1);
	fclose(fp2);
	return 0;
}
