#include<stdio.h>
#include<stdlib.h>
#include<time.h>

double my_random() {
  return (rand() * 1.0) / RAND_MAX;
}

int is_in_circle(double x, double y) {
  return x*x + y*y <= 1;
}

int monte_calro(int n, double *pi) {
  if (n < 0) return -1;

  int cnt = 0;
  for (int i=0; i < n; i++) {
    double x = my_random();
    double y = my_random();
    if (is_in_circle(x, y)) cnt++;
  }
  *pi = 4 * (cnt * 1.0 / n);

  return 0;
}

int main() {
  srand((unsigned)time(NULL));
  int n;
  scanf("%d", &n);

  double pi = 0;

  printf("initial pi = %lf\n", pi);

  if (monte_calro(n, &pi) != 0) {
    fprintf(stderr, "something wrong (ex: inputed n is not natural number)");
    return 1;
  }

  printf("calculated pi = %lf\n", pi);
  return 0;
}
