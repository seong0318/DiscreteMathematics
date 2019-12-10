#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


/** original lock.
  * not changed
*/

#define TEST_NUM 1000


int test_and_set(int *ptr, int new) {
	int old = *ptr;
	*ptr = new;
	return old;
}

typedef struct __lock_t {
	int flag;
} lock_t;

void init(lock_t *lock) {
	lock->flag = 0;
}

void lock(lock_t *lock) {
	while (test_and_set(&lock->flag, 1) == 1);
}

void unlock(lock_t *lock) {
	lock->flag = 0;
}

/* advanced lock.
 * while mutex lock, execute another function.
*/
typedef struct __ad_lock_t {
	int flag;
} ad_lock_t;

void ad_init(ad_lock_t *lock) {
	lock->flag = 0;
}

void ad_lock(ad_lock_t *lock, void (*fp)(void)) {
	while (test_and_set(&lock->flag, 1) == 1) {
		fp();
	}
}

void ad_unlock(ad_lock_t *lock) {
	lock->flag = 0;
}

int t1 = 0;
int t2 = 0;
lock_t mutex;
ad_lock_t ad_mutex;

void test(void *p) {
	int idx = (int)p;
	while (t2 < TEST_NUM) {
		printf("idx: %d, lock: %d, %d\n", idx, t1, t2);
		lock(&mutex);
		printf("idx:%d\n", idx);
		if (t1 < TEST_NUM) {
			printf("1\n");
			t1++;
		}
		else
			t2++;
		printf("2\n");
		Sleep(50);
		unlock(&mutex);
		printf("idx: %d unlock\n", idx);
		//printf("thread idx: %d, t1: %d, t2: %d\n", idx, t1, t2);
	}
	printf("end\n");
	_endthread();
}

void ad_test_other() {
	//printf("t2: %d\n", t2);
	if (t1 < TEST_NUM)
		t1++;
	else if (t2 < TEST_NUM)
		t2++;
	else
		return;
}

void ad_test_origin(void *p) {
	int idx = (int)p;
	while (t2 < TEST_NUM) {
		//printf("lock: %d, %d\n", t1, t2);
		ad_lock(&ad_mutex, ad_test_other);
		if (t1 < TEST_NUM)
			t1++;
		else
			t2++;
		Sleep(50);
		ad_unlock(&ad_mutex);
		//printf("unlock\n");
		//printf("thread idx: %d, t1: %d, t2: %d\n", idx, t1, t2);
	}
	_endthread();
}

int main(int argc, char *argv[]) {
	clock_t start, end;
	double result;

	start = clock();
	for (int i = 0; i < 4; i++)
		_beginthread(test, 0, (void*)i);

	while (t1 < TEST_NUM && t2 < TEST_NUM) {
		//printf("%d\n", t1);
	}
	end = clock();

	Sleep(5000);
	printf("result: %d, %d\n", t1, t2);
	result = (double)(end - start);	
	printf("%f\n", result / CLOCKS_PER_SEC);

	t1 = 0;
	t2 = 0;
	start = clock();
	for (int i = 0; i < 4; i++) 
		_beginthread(ad_test_origin, 0, (void*)i);

	while (t1 < TEST_NUM && t2 < TEST_NUM) {
		//printf("%d, %d\n", t1, t2);
	}
	end = clock();

	Sleep(500);
	printf("result: %d, %d\n", t1, t2);
	result = (double)(end - start);
	printf("%f\n", result / CLOCKS_PER_SEC);

	return 0;
}