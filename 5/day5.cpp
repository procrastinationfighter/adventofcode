#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using Seat = std::pair<int, int>;

constexpr int ROWS = 128;
constexpr int ROW_COUNT = 7;
constexpr int COLUMNS = 8;
constexpr int COL_COUNT = 3;
constexpr char ROW_LEFT = 'F';
constexpr char ROW_RIGHT = 'B';
constexpr char COL_LEFT = 'L';
constexpr char COL_RIGHT = 'R';

std::set<Seat> seats;
std::vector<unsigned long> IDs;

void init() {
  std::string line;
  while(std::getline(std::cin, line)) {
    int left = 0, right = ROWS - 1;
    for(int i = 0; i < ROW_COUNT; i++) {
      if(line[i] == ROW_LEFT) {
        right = (left + right) / 2;
      }
      else {
        left = (left + right) / 2 + 1;
      }
    }
    int row = left;

    left = 0, right = COLUMNS - 1;
    for(int i = 0; i < COL_COUNT; i++) {
      if(line[ROW_COUNT + i] == COL_LEFT) {
        right = (left + right) / 2;
      }
      else {
        left = (left + right) / 2 + 1;
      }
    }

    int column = left;
    std::cout << row << " " << column << "\n";
    seats.insert({row, column});
  }
}

unsigned long part_one() {
  unsigned long max = 0;
  for(const auto &seat: seats) {
    unsigned long curr = 8 * seat.first + seat.second;
    IDs.push_back(curr);
    max = std::max(max, curr);
  }
  std::sort(IDs.begin(), IDs.end());
  return max;
}

unsigned long part_two() {
  unsigned long previous = 0;
  for(const auto &id: IDs) {
    if(id - previous == 2) {
      return id - 1;
    }
    else {
      previous = id;
    }
  }
  return 0;
}

int main() {
  init();
  std::cout << part_one() << " " << part_two() << std::endl;
  return 0;
}
