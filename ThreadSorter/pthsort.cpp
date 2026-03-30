#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <pthread.h>

int n;
int *in_arr;
int *out_arr;

typedef struct{
  int start;
  int end;
} parameters;

void *sort(void *param) {
  parameters *p = (parameters*)param;
  int start = p->start;
  int end = p->end;
  for (int i = start; i <= end; i++) {
    for (int j = start; j < end - (i - start); j++) {
      if (in_arr[j] > in_arr[j + 1]) {
        int tmp = in_arr[j];
        in_arr[j] = in_arr[j + 1];
        in_arr[j + 1] = tmp;
      }
    }
  }
  return nullptr;
}

void *merge(void *param) {
  int left = 0;
  int right = n / 2;
  int k = 0;
  while (left < n / 2 && right < n) {
    if (in_arr[left] <= in_arr[right]) {
      out_arr[k++] = in_arr[left++];
    }
    else {
      out_arr[k++] = in_arr[right++];
    }
  }
  while (left < n / 2) {
    out_arr[k++] = in_arr[left++];
  }
  while (right < n) {
    out_arr[k++] = in_arr[right++];
  }
  return nullptr;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "usage: pthsort <file>\n";
    return 1;
  }
  std::ifstream in(argv[1]);

  if (!in.is_open()) {
    std::cerr << "file " << argv[1] << " does not exist";
    return 1;
  }

  in >> n;
  in_arr = new int[n];
  out_arr = new int[n];
  
  for (int i = 0; i < n; i++) {
    in >> in_arr[i];
  }

  pthread_t s1, s2, m;
  parameters s1p, s2p;
  s1p.start = 0;
  s1p.end = n / 2 - 1;
  s2p.start = n / 2;
  s2p.end = n - 1;

  pthread_create(&s1, nullptr, sort, &s1p);
  pthread_create(&s2, nullptr, sort, &s2p);

  pthread_join(s1, nullptr);
  pthread_join(s2, nullptr);

  pthread_create(&m, nullptr, merge, nullptr);
  pthread_join(m, nullptr);

  for (int i = 0; i < n; i++) {
    std::cout << out_arr[i] << "\n";
  }

  delete[] in_arr;
  delete[] out_arr;

  return 0;
}