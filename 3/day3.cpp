#include <iostream>

constexpr char tree = '#';
constexpr char open = '.';

int part_one() {
  unsigned long index = 0;
  std::string line;
  int tree_count = 0;

  while(std::getline(std::cin, line)) {
    if(line[index] == tree) {
      tree_count++;
    }
    index = (index + 3) % line.size();
  }

  return tree_count;
}

unsigned long part_two() {
  // Checked paths:
  //  Right 1, down 1.
  //  Right 3, down 1. (part one)
  //  Right 5, down 1.
  //  Right 7, down 1.
  //  Right 1, down 2.

  unsigned long index[5] = {0, 0, 0, 0, 0};
  std::string line;
  unsigned long tree_count[5] = {0, 0, 0, 0, 0,};
  int line_count = 0;

  while(std::getline(std::cin, line)) {
    unsigned long line_size = line.size();
    if(line[index[0]] == tree) {
      tree_count[0]++;
    }
    if(line[index[1]] == tree) {
      tree_count[1]++;
    }
    if(line[index[2]] == tree) {
      tree_count[2]++;
    }
    if(line[index[3]] == tree) {
      tree_count[3]++;
    }
    if(line_count % 2 == 0) {
      if (line[index[4]] == tree) {
        tree_count[4]++;
      }
      index[4] = (index[4] + 1) % line_size;
    }

    index[0] = (index[0] + 1) % line_size;
    index[1] = (index[1] + 3) % line_size;
    index[2] = (index[2] + 5) % line_size;
    index[3] = (index[3] + 7) % line_size;

    line_count++;
  }

  return tree_count[0] * tree_count[1] * tree_count[2] * tree_count[3] * tree_count[4];
}

int main() {
  std::cout << part_two() << "\n";
  return 0;
}