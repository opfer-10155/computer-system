#include<stdio.h>
#include<stdlib.h>

#define MAX_VALUE 1000000000
#define MAX_LEN 1000000000

int bucket[MAX_VALUE];
int array[MAX_LEN];

int max(int *array, int array_size) {
  int max = INT32_MIN;
  for (int i=0; i < array_size; i++) {
    if (max < array[i]) {
      max = array[i];
    }
  }
  return max;
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

// x^n ただし n >= 0
int my_pow(int x, int n) {
  if (n <= 0) return 1;
  else return x * my_pow(x, n-1);
}

// xの10^rの位の数を取り出す
int radix_number(int x, int r) {
  int tmp = x % my_pow(10, r+1);
  return tmp / my_pow(10, r);
}

void radix_sort(int *array, int array_size) {
  int m = max(array, array_size);
  if (m > MAX_VALUE) {
    fprintf(stderr, "array has value which exceed 1000000000");
    exit(1);
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
  // puts("bucket sort");
  // bucket_sort(array, n);
  // print_array(array, n);
  puts("just a joke");
  puts("stalin sort");
  stalin_sort(array, &n);
  print_array(array, n);
}
