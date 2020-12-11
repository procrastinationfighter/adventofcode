#include <iostream>
#include <vector>

std::vector<std::string> initial_state_1;
auto &seats_plane_part_one = initial_state_1;
std::vector<std::string> initial_state_2;
auto &seats_plane_part_two = initial_state_2;

constexpr char seat = '#';
constexpr char empty_seat = 'L';

void init() {
  std::string curr;
  while(std::getline(std::cin, curr)) {
    seats_plane_part_one.push_back(curr);
  }
  initial_state_2 = initial_state_1;
}

inline bool are_indices_in_bound(int i, int j) {
  return i >= 0 && i < seats_plane_part_one.size() && j >= 0 && j < seats_plane_part_one[0].size();
}

int count_adj_taken_seats(int i, int j) {
  int count = 0;
  for(int a = -1; a < 2; a++) {
    for(int b = -1; b < 2; b++) {
      if(are_indices_in_bound(i + a, j + b)
        && !(a == 0 && b == 0)
        && seats_plane_part_one[i + a][j + b] == seat) {
        count++;
      }
    }
  }

  return count;
}

int part_one() {
  int changes;
  std::vector<std::string> new_vector = seats_plane_part_one;
  do {
    changes = 0;
    for(int i = 0; i < seats_plane_part_one.size(); i++) {
      for(int j = 0; j < seats_plane_part_one[0].size(); j++) {
        int x = count_adj_taken_seats(i, j);
        if(seats_plane_part_one[i][j] == seat && x >= 4) {
          new_vector[i][j] = empty_seat;
          changes++;
        }
        else if(seats_plane_part_one[i][j] == empty_seat && x == 0) {
          new_vector[i][j] = seat;
          changes++;
        }
      }
    }

    seats_plane_part_one = new_vector;
  } while(changes != 0);

  int count_occupied = 0;
  for (int i = 0; i < seats_plane_part_one.size(); i++) {
    for (int j = 0; j < seats_plane_part_one[0].size(); j++) {
      if (seats_plane_part_one[i][j] == seat) {
        count_occupied++;
      }
    }
  }
  return count_occupied;
}

int count_adj_taken_seats_part_two(int i, int j) {
  static int dir_changes[8][2] = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
  int count = 0;
  for(auto &dir_change: dir_changes) {
    int curr_i = i + dir_change[0], curr_j = j + dir_change[1];
    while(are_indices_in_bound(curr_i, curr_j)) {
      if(seats_plane_part_two[curr_i][curr_j] == seat) {
        count++;
        break;
      }
      else if(seats_plane_part_two[curr_i][curr_j] == empty_seat) {
        break;
      }

      curr_i += dir_change[0];
      curr_j += dir_change[1];
    }
  }

  return count;
}

int part_two() {
  int changes;
  std::vector<std::string> new_vector = seats_plane_part_two;
  do {
    changes = 0;
    for(int i = 0; i < seats_plane_part_two.size(); i++) {
      for(int j = 0; j < seats_plane_part_two[0].size(); j++) {
        int x = count_adj_taken_seats_part_two(i, j);
        if(seats_plane_part_two[i][j] == seat && x >= 5) {
          new_vector[i][j] = empty_seat;
          changes++;
        }
        else if(seats_plane_part_two[i][j] == empty_seat && x == 0) {
          new_vector[i][j] = seat;
          changes++;
        }
      }
    }

    seats_plane_part_two = new_vector;
  } while(changes != 0);

  int count_occupied = 0;
  for (int i = 0; i < seats_plane_part_two.size(); i++) {
    for (int j = 0; j < seats_plane_part_two[0].size(); j++) {
      if (seats_plane_part_two[i][j] == seat) {
        count_occupied++;
      }
    }
  }
  return count_occupied;
}

int main() {
  init();
  std::cout << part_one() << " " << part_two() << "\n";
  return 0;
}