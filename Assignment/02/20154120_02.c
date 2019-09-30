#include <stdio.h>
int main(int argc, char *argv[]) {
	int init = 0;
	for (int i = 1; i < argc; i += 2) {
		if (!strcmp(argv[i], "+")) 
			init += atoi(argv[i + 1]);
		else if (!strcmp(argv[i], "-")) 
			init -= atoi(argv[i + 1]);
		else {
			printf("\nnot invalid input");
			return -1;
		}
	}
	printf("%d\n", init);
	printf("1q2w3e4r!@#1q2w3e4r!@#1\n");
	printf("Seong Hyun\n");
	printf("Student ID : 20154120\n");
	printf("q2w3e4r!@#1q2w3e4r!@#1q");

	return 0;
}