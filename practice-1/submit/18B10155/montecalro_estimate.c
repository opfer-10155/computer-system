/**
 * 点の数nのモンテカルロ法をn回実行して円周率を区間推定してみたかった
 */
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

double A[10000000];

double my_random() {
  return (rand() * 1.0) / RAND_MAX;
}

int is_in_circle(double x, double y) {
  return x*x + y*y <= 1;
}

double monte_calro(int n) {
  if (n < 0) return -1;

  int cnt = 0;
  for (int i=0; i < n; i++) {
    double x = my_random();
    double y = my_random();
    if (is_in_circle(x, y)) cnt++;
  }

  return 4 * ((cnt * 1.0) / n);
}

int main() {
  srand((unsigned)time(NULL));

  int n, m;
  printf("点の数 = "); scanf("%d", &n);
  printf("試行回数 = "); scanf("%d", &m);


  double sum = 0;
  for (int i=0; i < m; i++) {
    A[i] = monte_calro(n);
    // printf("%d,", A[i]);
  }
  puts("");

  // 標本平均
  double avg = 0;
  for(int i=0; i<m; i++) {
    avg += A[i];
  }
  avg /= m;

  // 不偏分散
  double var = 0;
  for(int i=0; i<m; i++) {
    var += (A[i]-avg) * (A[i]-avg);
  }
  if (m <= 1) m = 2;
  var /= (m - 1);

  double tmp = 1.96 * sqrt(var / m);

  printf("πの95パーセント信頼区間は[%lf, %lf]\n", avg - tmp, avg + tmp);
  return 0;
}
