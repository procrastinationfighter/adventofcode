#include <iostream>
#include <vector>
#include <map>

std::vector<std::string> input;

void init() {
    std::string curr;
    while (std::getline(std::cin, curr)) {
        input.push_back(curr);
    }
}

int w_or_e(char ch) {
    if (ch == 'e') {
        return 1;
    } else if (ch == 'w') {
        return -1;
    } else {
        std::cerr << "Direction neither -east or -west. Strange." << std::endl;
        return 42;
    }
}

std::pair<int, int> calculate_tile_position(const std::string &line) {
    int x = 0, y = 0;

    int i = 0;
    while (i < line.size()) {
        switch (line[i]) {
            case 'e':x += 2;
                break;
            case 'w':x -= 2;
                break;
            case 'n':y++;
                i++;
                x += w_or_e(line[i]);
                break;
            case 's':y--;
                i++;
                x += w_or_e(line[i]);
                break;
            default:break;
        }
        i++;
    }

    return {x, y};
}

std::map<std::pair<int, int>, int> tiles;

int part_one() {
    for (const auto &line : input) {
        auto location = calculate_tile_position(line);
        tiles[location]++;
    }

    int black_count = 0;

    for (const auto &x : tiles) {
        if (x.second % 2 == 1) {
            black_count++;
        }
    }

    return black_count;
}

const int floor_size = 400;

bool is_in_bound(int i, int j) {
    return i >= 0 && i < floor_size && j >= 0 && j < floor_size;
}

std::vector<std::vector<bool>> flip_day(const std::vector<std::vector<bool>> &floor) {
    auto floor_copy = floor;
    static int neighbors[6][2] = {{2, 0}, {-2, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (int i = 0; i < floor_size; i++) {
        for (int j = 0; j < floor_size; j++) {
            if (i % 2 == j % 2) {
                int black_neighbors = 0;
                for (const auto &neighbor : neighbors) {
                    if (is_in_bound(i + neighbor[0], j + neighbor[1])) {
                        if (floor[i + neighbor[0]][j + neighbor[1]]) {
                            black_neighbors++;
                        }
                    }
                }

                if (floor[i][j]) {
                    if (black_neighbors != 1 && black_neighbors != 2) {
                        floor_copy[i][j] = false;
                    }
                } else if (black_neighbors == 2) {
                    floor_copy[i][j] = true;
                }
            }
        }
    }

    return floor_copy;
}

int part_two() {
    const int days = 100;
    // True means a tile is black.
    std::vector<std::vector<bool>> floor(floor_size, std::vector<bool>(floor_size, false));

    for (const auto &p : tiles) {
        floor[floor_size / 2 + p.first.first][floor_size / 2 + p.first.second] =
            (p.second % 2 == 1);
    }

    for (int i = 0; i < days; i++) {
        floor = flip_day(floor);
    }

    int black_count = 0;

    for (const auto &x : floor) {
        for (bool y : x) {
            if (y) {
                black_count++;
            }
        }
    }

    return black_count;
}

int main() {
    init();
    std::cout << part_one() << " " << part_two() << "\n";
    return 0;
}