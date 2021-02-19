#include <iostream>
#include <vector>

std::vector<std::pair<char, int>> input;

void init() {
  char ch;
  int x;

  while(std::cin >> ch) {
    std::cin >> x;
    input.emplace_back(ch, x);
  }
}

int part_one() {
  int direction = 90; // We assume 0 is the north and it increases clockwise.
  int east_pos = 0, north_pos = 0;

  for(const auto &move : input) {
    int x = move.second;
    switch(move.first) {
      case 'N': north_pos += x; break;
      case 'E': east_pos += x; break;
      case 'S': north_pos -= x; break;
      case 'W': east_pos -= x; break;
      case 'L': direction = (direction + 360 - x) % 360; break;
      case 'R': direction = (direction + x) % 360; break;
      case 'F': switch (direction) {
          case 0: north_pos += x; break;
          case 90: east_pos += x; break;
          case 180: north_pos -= x; break;
          case 270: east_pos -= x; break;
          default: std::cout << "WRONG VALUE: " << direction << "\n"; break;
        } break;
          default: std::cout << "WRONG COMMAND\n"; break;
    }
  }

  return abs(east_pos) + abs(north_pos);
}

void turn_left(int times, int &north, int &east) {
  for(int i = 0; i < times; i++) {
    int temp = north;
    north = east;
    east = -temp;
  }
}

void turn_right(int times, int &north, int &east) {
  for(int i = 0; i < times; i++) {
    int temp = north;
    north = -east;
    east = temp;
  }
}

int part_two() {
  int east_pos = 0, north_pos = 0;
  int waypoint_east = 10, waypoint_north = 1;

  for(const auto &move : input) {
    int x = move.second;
    switch(move.first) {
      case 'N': waypoint_north += x; break;
      case 'E': waypoint_east += x; break;
      case 'S': waypoint_north -= x; break;
      case 'W': waypoint_east -= x; break;
      case 'L': turn_left(x/90, waypoint_north, waypoint_east); break;
      case 'R': turn_right(x/90, waypoint_north, waypoint_east); break;
      case 'F': east_pos += x * waypoint_east; north_pos += x * waypoint_north; break;
      default: std::cout << "WRONG COMMAND\n"; break;
    }
  }

  return abs(east_pos) + abs(north_pos);
}

int main() {
  init();
  std::cout << part_one() << " " << part_two() << "\n";
  return 0;
}