#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <pthread.h>

int argc_g;
char **argv_g;

int turn = 1;

bool is_prime(long long n) {
  if (n < 2) return false;
  for (long long i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

void *zerof(void *param) {
  for (int i = 1; i < argc_g; i++) {
    if (atoll(argv_g[i]) == 0) {
      while (turn != i) {sched_yield();}
      std::cout << "     ZERO:  " << argv_g[i] << "\n";
      turn = i + 1;
    }
  }
  return nullptr;
}

void *negativef(void *param) {
  for (int i = 1; i < argc_g; i++) {
    if (atoll(argv_g[i]) < 0) {
      while (turn != i) {sched_yield();}
      std::cout << " NEGATIVE: " << argv_g[i] << "\n";
      turn = i + 1;
    }
  }
  return nullptr;
}

void *primef(void *param) {
  for (int i = 1; i < argc_g; i++) {
    if (atoll(argv_g[i]) > 0 && is_prime(atoll(argv_g[i]))) {
      while (turn != i) {sched_yield();}
      std::cout << "    PRIME:  " << argv_g[i] << "\n";
      turn = i + 1;
    }
  }
  return nullptr;
}

void *not_primef(void *param) {
  for (int i = 1; i < argc_g; i++) {
    if (atoll(argv_g[i]) > 0 && !is_prime(atoll(argv_g[i]))) {
      while (turn != i) {sched_yield();}
      std::cout << "NOT PRIME:  " << argv_g[i] << "\n";
      turn = i + 1;
    }
  }
  return nullptr;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cerr << "usage: pthii <list of integers>\n";
    return 1;
  }

  argc_g = argc;
  argv_g = argv;

  pthread_t zero, neg, prime, non_prime;

  pthread_create(&zero, nullptr, zerof, nullptr);
  pthread_create(&neg, nullptr, negativef, nullptr);
  pthread_create(&prime, nullptr, primef, nullptr);
  pthread_create(&non_prime, nullptr, not_primef, nullptr);

  pthread_join(zero, nullptr);
  pthread_join(neg, nullptr);
  pthread_join(prime, nullptr);
  pthread_join(non_prime, nullptr);

  return 0;
}