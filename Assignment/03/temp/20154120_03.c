#include <stdio.h>
#include <stdlib.h>

char *input;
int *flag;
int isEmpty = 1;

void subset(int depth) {
	int isPrint;
	int size = _msize(input);
	if (depth == size) {
		isPrint = 0;
		for (int i = 0; i < size; i++) {
			if (isEmpty) {
				printf("%c", 155);
				isEmpty = 0;
				continue;
			}
			if (flag[i]) {						
				if (i < size && isPrint)
					printf(", ");
				isPrint = 1;
				printf("%c", input[i]);	
			}
		}
		printf("\n");
		return;
	}
	else {
		flag[depth] = 0;
		subset(depth + 1);
		flag[depth] = 1;
		subset(depth + 1);
	}
}

int main(int argc, char *argv[]) {
	system("chcp 437");
	input = (char*)malloc(sizeof(char) * (argc - 1));
	flag = (int*)malloc(sizeof(int) * (argc - 1));

	for (int i = 1; i < argc; i++)	
		input[i - 1] = *argv[i];
	
	for (int i = 0; i < argc - 1; i++)
		flag[i] = 0;

	subset(0);
	
	printf("1q2w3e4r!@#1q2w3e4r!@#1\n");
	printf("Seong Hyun\n");
	printf("Student ID : 20154120\n");
	printf("q2w3e4r!@#1q2w3e4r!@#1q\n");

	return 0;
}