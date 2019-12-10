#define _CRT_SECURE_NO_WARNINGS
#define MAX_VOCAB_NUM 100000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vocab_size;

char* set_delimiters() {
	char* delimiters = "";
	int num_delimiter = 1;

	for (int i = 0; i < 128; i++) {
		if (i < 48 || (i > 57 && i < 65) || (i > 90 && i < 97) || i > 122) {
			char add_delimiter = i;
			char ctostr[2];
			char* temp;

			ctostr[1] = '\0';
			ctostr[0] = add_delimiter;
			temp = malloc(sizeof(char) * ++num_delimiter);
			strcpy(temp, delimiters);
			strcat(temp, ctostr);
			delimiters = temp;
			//free(temp);
		}
	}
	return delimiters;
}

void calc_vacab_set(char** vocab_set, int* vocab_cnt, char* input_vocab) {
	for (int i = 0; i < vocab_size; i++) {
		if (strcmp(vocab_set[i], input_vocab) == 0) {
			vocab_cnt[i]++;
			return;
		}
	}
	vocab_set[vocab_size] = input_vocab;
	vocab_cnt[vocab_size] = 1;
	vocab_size++;
}

int main(int argc, char* argv[]) {
	FILE *fp1, *fp2;
	int size;
	int count;
	char* vocab_set[MAX_VOCAB_NUM] = { 0, };
	int vocab_cnt[MAX_VOCAB_NUM] = { 0, };

	int toknum = 0;
	char* src;
	char* delimiters = set_delimiters();
	//printf("delimiters: %s\n", delimiters);

	if ((fp1 = fopen(argv[1], "r")) == NULL) { //fail to open file for read
		printf("fail to open file.");
		return 0;
	}
	if ((fp2 = fopen(argv[2], "wt")) == NULL) { //fail to open file for write
		printf("fail to create file for write.");
		return 0;
	}

	fseek(fp1, 0, SEEK_END);
	size = ftell(fp1);

	src = malloc(size + 1);
	memset(src, 0, size + 1);

	fseek(fp1, 0, SEEK_SET);
	count = fread(src, size, 1, fp1);

	char* token = strtok(src, delimiters);

	while (token != NULL) {
		strlwr(token);
		calc_vacab_set(vocab_set, vocab_cnt, token);
		token = strtok(NULL, delimiters);		
	}

	for (int i = 0; i < vocab_size; i++) {
		printf("[%04d]vocab: %s (%d)\n", i + 1, vocab_set[i], vocab_cnt[i]);
		fprintf(fp2, "[%04d]vocab: %s (%d)\n", i + 1, vocab_set[i], vocab_cnt[i]);
	}

	fputs("1q2w3e4r!@#1q2w3e4r!@#1\n", fp2);
	fputs("Seong Hyun\n", fp2);
	fputs("Student ID : 20154120\n", fp2);
	fputs("q2w3e4r!@#1q2w3e4r!@#1q\n", fp2);
	/* source is now "Hello\0, world\0\0" */
	free(delimiters);
	return 0;
}
