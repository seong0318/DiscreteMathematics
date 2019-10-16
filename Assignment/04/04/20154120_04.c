#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input;
int *flag;
int isEmpty = 1;
int cnt = 0;
char fname[20];
FILE *fp;

void printIdx(int cnt) {
	int cipher = 1;
	char num[5] = "0000";
	sprintf(num, "%d", cnt);
	char s[10] = "[0000]";
	int temp = cnt;
	int idx = 0;

	while (temp / 10 >= 1) {
		cipher++;
		temp /= 10;
	}
	for (int i = 1; i < 5; i++) {
		if (i < 5 - cipher)
			s[i] = '0';
		else {
			s[i] = num[idx];
			idx++;
		}
	}
	printf("%s ", s);
	fprintf(fp, "%s ", s);
}

void subset(int depth) {
	int isPrint;
	int size = _msize(input);
	if (depth == size) {
		isPrint = 0;
		cnt++;
		printIdx(cnt);
		for (int i = 0; i < size; i++) {
			if (isEmpty) {
				printf("%c", 155);
				fprintf(fp, "%c", 155);
				isEmpty = 0;
				continue;
			}
			if (flag[i]) {
				if (i < size && isPrint) {
					printf(", ");
					fputs(", ", fp);
				}
				isPrint = 1;
				printf("%c", input[i]);
				fprintf(fp, "%c", input[i]);
			}
		}
		printf("\n");
		fputs("\n", fp);
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
	strcpy(fname, argv[1]);
	input = (char*)malloc(sizeof(char) * (argc - 2));
	flag = (int*)malloc(sizeof(int) * (argc - 2));

	fp = fopen(fname, "w");

	for (int i = 2; i < argc; i++)
		input[i - 2] = *argv[i];

	for (int i = 0; i < argc - 2; i++)
		flag[i] = 0;

	subset(0);

	printf("1q2w3e4r!@#1q2w3e4r!@#1\n");
	printf("Seong Hyun\n");
	printf("Student ID : 20154120\n");
	printf("q2w3e4r!@#1q2w3e4r!@#1q\n");

	fclose(fp);

	return 0;
}