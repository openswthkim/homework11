/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command; // 문자형 변수 선언
	int *array = NULL; // 포인터 array 선언 후 초기화
	int *hashtable = NULL; // 포인터 hastable 선언 후 초기화
	int key = -1; // 정수형 변수 key -1로 초기화
	int index = -1; // 정수형 변수 index -1로 초기화

	srand(time(NULL)); // 난수 생성


	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': // z를 입력 받으면
			initialize(&array); // array 초기화
			break;
		case 'q': case 'Q': // q를 입력 받으면
			freeArray(array); // array에 할당된 메모리 해제
			break;
		case 's': case 'S': // s를 입력 받으면
			selectionSort(array); // 선택 정렬
			break;
		case 'i': case 'I': //  i를 입력 받으면
			insertionSort(array); // 삽입 정렬
			break;
		case 'b': case 'B': // b를 입력 받으면
			bubbleSort(array); // 버블 정렬
			break; 
		case 'l': case 'L': // l을 입력 받으면
			shellSort(array); // 셸 정렬
			break;
		case 'k': case 'K': // k를 입력 받으면
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); // 배열 출력
			quickSort(array, MAX_ARRAY_SIZE); // 퀵 정렬
			printf("----------------------------------------------------------------\n");
			printArray(array); // 배열 출력

			break;

		case 'h': case 'H': // h를 입력 받으면
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); // 배열 출력
			hashing(array, &hashtable); // hashing
			printArray(hashtable); // 배열 출력
			break;

		case 'e': case 'E': // e를 입력 받으면
			printf("Your Key = ");
			scanf("%d", &key); // key 입력 받고
			printArray(hashtable); // 해싱 한 배열 출력
			index = search(hashtable, key); // index에 탐색 주소 저장
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P': // p를 입력 받으면
			printArray(array); // 배열 출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q를 입력 받을 때까지 반복

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL; // temp 포인터에 NULL값 저장

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) { // 포인터 a에 NULL값 저장
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // temp에 int형 크기 만큼 MAX_ARRAY_SIZE 메모리 할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a; // temp에 포인터 a값 저장

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 크기만큼 반복
		temp[i] = rand() % MAX_ARRAY_SIZE; // temp[i]에 랜덤값 저장

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL) // array a가 NULL이 아닐 경우
		free(a); // a에 할당된 메모리 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) { // a가 NULL일 경우
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 크기만큼 반복
		printf("a[%02d] ", i); // i값 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 크기만큼 반복
		printf("%5d ", a[i]); // a에 저장된 배열 값 출력
	printf("\n");
}


int selectionSort(int *a)
{
	int min; // 최솟값 변수 선언
	int minindex; // 최솟값 인덱스 변수 선언 
	int i, j; // 정수형 변수 선언

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 배열 a 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // 배열 크기만큼 반복
	{
		minindex = i; // minindex에 i 저장
		min = a[i]; // min에 a[i] 저장
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) // 배열만큼 반복
		{
			if (min > a[j]) // min이 a[j]보다 크면
			{
				min = a[j]; // min에 a[j] 저장
				minindex = j; // minindex에 j 저장
			}
		}
		a[minindex] = a[i]; // a[minindex]에 a[i] 저장
		a[i] = min; // a[i]에 min 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 a 출력
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t; // 정수형 변수 선언

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 배열 a 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++) // 배열의 크기만큼 반복
	{
		t = a[i]; // t에 a[i] 저장
		j = i; // j에 i 저장
		while (a[j-1] > t && j > 0) // a[j-1]이 t보다 크거나 j가 0보다 클 동안 반복
		{
			a[j] = a[j-1]; // a[j]에 a[j-1] 저장
			j--; // j 감소
		}
		a[j] = t; // a[j]에 t 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 a 출력

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t; // 정수형 변수 선언

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 배열 a 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++) // i를 배열의 크기만큼 반복
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++) // j를 배열의 크기만큼 반복
		{
			if (a[j-1] > a[j]) // a[j-1]가 a[j]보다 크면
			{
				t = a[j-1]; // t에 a[j-1] 저장
				a[j-1] = a[j]; // a[j-1]에 a[j] 저장
				a[j] = t; // a[j]에 t 저장
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 a 출력

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v; // 정수형 변수 선언

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 배열 a 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // h에 배열 크기의 반을 저장하고 간격을 반으로 나누면서 반복 
	{
		for (i = 0; i < h; i++) // i를 h값까지 반복
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // j를 i부터 배열 크기만큼 h만큼 증가하면서 반복한다
			{
				v = a[j]; // v에 a[j]값 저장
				k = j; // k에 j값 저장
				while (k > h-1 && a[k-h] > v) // k가 h보다 크고 이전 요소가 현재 요소보다 크면 반복한다
				{
					a[k] = a[k-h]; // a[k]에 a[k-h] 반복
					k -= h; // k를 h만큼 감소
				}
				a[k] = v; // a[k]에 v 저장
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 배열 a 출력

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t; 
	int i, j; // 정수형 변수 선언

	if (n > 1) // n이 1보다 클 경우
	{
		v = a[n-1]; // v에 a[n-1] 저장
		i = -1; // i에 -1 초기화
		j = n - 1; // j에 n-1 저장

		while(1)
		{
			while(a[++i] < v); // a[++i]가 v보다 적을 동안 i 값 증가
			while(a[--j] > v); // a[--j]가 v보다 클 동안 j 값 감소

			if (i >= j) break; // i가 j보다 크거나 같으면 종료
			t = a[i]; // t에 a[i]값 저장
			a[i] = a[j]; // a[i]에 a[j] 저장
			a[j] = t; // a[j]에 t 저장
		}
		t = a[i]; // t에 a[i] 저장
		a[i] = a[n-1]; // a[i]에 a[n-1] 저장
		a[n-1] = t; //  a[n-1]에 t 저장

		quickSort(a, i); // a 배열 왼쪽 정렬
		quickSort(a+i+1, n-i-1); // 오른쪽 정렬
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; // key로 hastable 크기로 나는 나머지 리턴
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL; // 포인터 hastable에 NULL 저장 

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) { // 포인터 ht가 NULL이면
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // hastable에 정수 크기만큼 배열 크기의 메모리 할당
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // HASH_TABLE 크기 만큼 반복
		hashtable[i] = -1; // hashtable[i]에 -1로 초기화

	int key = -1; 
	int hashcode = -1;
	int index = -1; // 정수형 변수 선언 후 초기화
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // 정수형 변수 크기 동안 반복 
	{
		key = a[i]; // key에 a[i] 저장
		hashcode = hashCode(key); // hashcode에 hashCode함수 호출한 값 저장

		if (hashtable[hashcode] == -1) // hashtable[hashcode]가 -1 인 경우
		{
			hashtable[hashcode] = key; // hastable[hashcode]에 key 저장
		} else 	{

			index = hashcode; // index에 hashcode 저장

			while(hashtable[index] != -1) // hastable[index]가 -1이 아닐동안 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // index를 1 증가시키고 HASH_TABLE의 크기로 나눈 나머지를 index에 저장 
			}
			hashtable[index] = key; // hashtable[index]에 key 저장
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); // hashCode 호출 값을 index에 저장

	if(ht[index] == key) // ht[index]가 key와 같으면
		return index; // index 리턴

	while(ht[++index] != key) // ht[index]가 key와 같지 않을 동안 index 증가
	{
		index = index % MAX_HASH_TABLE_SIZE; // MAX_HASH_TABLE_SIZE로 나눈 나머지를 index에 저장
	}
	return index; // index 리턴
}
