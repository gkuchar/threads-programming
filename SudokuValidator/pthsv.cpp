#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <atomic>
#include <pthread.h>

std::atomic<int> dup_found(0);
int board[9][9] = {};

void *check_row(void *param) {
  int row = *(int*)param;
  std::unordered_set<int> s = {};

  for (int i = 0; i < 9; i ++) {
    if (s.find(board[row][i]) != s.end()) {
      dup_found = 1;
      return nullptr;
    }
    else {
      s.insert(board[row][i]);
    }
  }

  return nullptr;
}

void *check_col(void *param) {
  int col = *(int*)param;
  std::unordered_set<int> s = {};

  for (int i = 0; i < 9; i ++) {
    if (s.find(board[i][col]) != s.end()) {
      dup_found = 1;
      return nullptr;
    }
    else {
      s.insert(board[i][col]);
    }
  }

  return nullptr;
}

void *check_square(void *param) {
    int square = *(int*)param;
    std::unordered_set<int> s = {};
    int start_row = (square / 3) * 3;
    int start_col = (square % 3) * 3;
    for (int i = start_row; i < start_row + 3; i++) {
      for (int j = start_col; j < start_col + 3; j++) {
        if (s.find(board[i][j]) != s.end()) {
          dup_found = 1;
          return nullptr;
        }
        else {
          s.insert(board[i][j]);
        }
      }
    }
    return nullptr;
}

void populate_board(std::ifstream *file) {
  int row = 0;
  std::string line;
  while (std::getline(*file, line)) {
    std::istringstream ss(line);
    int val;
    int col = 0;
    while (ss >> val) {
      board[row][col++] = val;
    }
    row++;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "usage: pthsv <file>\n";
    return 1;
  }
  std::ifstream in(argv[1]);

  if (!in.is_open()) {
    std::cerr << "file " << argv[1] << " does not exist\n";
    return 1;
  }

  populate_board(&in);

  pthread_t threads[27];
  int args[27];

  for (int i = 0; i < 27; i++) {
    args[i] = i % 9;
  }

  for (int i = 0; i < 9; i++) {
    pthread_create(&threads[i], nullptr, check_row, &args[i]);
  }
  for (int i = 9; i < 18; i++) {
    pthread_create(&threads[i], nullptr, check_col, &args[i]);
  }
  for (int i = 18; i < 27; i++) {
    pthread_create(&threads[i], nullptr, check_square, &args[i]);
  }

  for (int i = 0; i < 27; i++) {
    pthread_join(threads[i], nullptr);
  }

  if (dup_found == 1) {
    std::cout << "FALSE\n";
  }
  else {
    std::cout << "TRUE\n";
  }

  return 0;
}
