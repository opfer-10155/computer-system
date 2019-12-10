#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_VALUE 1000000000
#define MAX_LEN 1000000000

int bucket[MAX_VALUE];
int array[MAX_LEN];

int max(int *array, int array_size) {
  int m = INT32_MIN;
  for (int i=0; i < array_size; i++) {
    if (m < array[i]) {
      m = array[i];
    }
  }
  return m;
}

int min_i(int *array, int array_size) {
  int m_i = 0;
  for (int i=1; i < array_size; i++) {
    if (array[m_i] > array[i]) {
      m_i = i;
    }
  }
  return m_i;
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void print_array(int *array, int n) {
  for(int i=0; i < n-1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d\n", array[n-1]);
}

/*
void sort_int_array(int *array, int array_size) {

}
*/

void bucket_sort(int *array, int array_size) {
  int m = max(array, array_size);
  if (m > MAX_VALUE) {
    fprintf(stderr, "array has value which exceed 1000000000");
    exit(1);
  }
  for (int i=0; i < array_size; i++) {
    if (array[i] < 0) {
      fprintf(stderr, "array value must be natural number (including 0)");
      exit(1);
    }
    bucket[array[i]]++;
  }

  for (int i=0, j=0; i <= m; i++) {
    if (bucket[i] > 0) {
      array[j] = i;
      j++;
      bucket[i]--;
      i--;
    }
  }
}

void selection_sort(int *array, int array_size) {
  for (int i=0; i < array_size-1; i++) {
    // i番目以降の要素の最大値のインデックス
    int m_i = min_i(array+i, array_size-i) + i;
    swap(array+i, array+m_i);
  }
}


// just a joke
// ソートされていない要素を粛清することでソートされた配列を生み出す
void stalin_sort(int *array, int *array_size) {
  int j=1;
  for (int i=1; i < *array_size; i++) {
    if (array[j-1] <= array[i]) {
      array[j] = array[i];
      j++;
    }
  }
  *array_size = j;
}


int main() {
  int n;
  scanf("%d", &n);
  for (int i=0; i < n; i++) {
    scanf("%d", array + i);
  }

  size_t array_size = sizeof(array[0]) * n;

  int *cp_array = malloc(array_size);
  memcpy(cp_array, array, array_size);
  puts("bucket sort");
  bucket_sort(cp_array, n);
  print_array(cp_array, n);
  puts("");

  memcpy(cp_array, array, array_size);
  puts("original array");
  print_array(cp_array, n);
  puts("");

  puts("selection sort");
  selection_sort(cp_array, n);
  print_array(cp_array, n);
  free(cp_array);
  puts("");

  puts("just a joke");
  puts("stalin sort");
  stalin_sort(array, &n);
  print_array(array, n);
}
