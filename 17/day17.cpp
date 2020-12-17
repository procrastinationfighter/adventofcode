#include <iostream>
#include <vector>

// MY CRAPPIEST SOLUTION SO FAR
using Cube = std::vector<std::vector<std::string>>;

Cube input;

void init() {
    std::vector<std::string> initial;
    std::string curr;
    while(std::getline(std::cin, curr)) {
        initial.push_back(curr);
    }
    input.push_back(initial);
}

namespace part_1 {
void make_cube_greater(Cube &curr_input) {
    size_t new_size = curr_input[0].size() + 2;
    for (auto &face: curr_input) {
        for (auto &line : face) {
            line.insert(0, ".");
            line.push_back('.');
        }
        face.insert(face.begin(), std::string(new_size, '.'));
        face.emplace_back(new_size, '.');
    }
    curr_input.insert(curr_input.begin(),
                      std::vector<std::string>(new_size, std::string(new_size, '.')));
    curr_input.push_back(std::vector<std::string>(new_size, std::string(new_size, '.')));

}

bool ok(int val, int low, int up) {
    return val >= low && val < up;
}

bool is_same_point(int k, int i, int j) {
    return i == 0 && j == 0 && k == 0;
}

int count_neighbors(int k, int i, int j, const Cube &curr_input) {
    int faces = curr_input.size();
    int size = curr_input[0].size();

    int count = 0;

    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            for (int z = -1; z < 2; z++) {
                if (ok(k + x, 0, faces) && ok(i + y, 0, size) && ok(j + z, 0, size)
                    && !is_same_point(x, y, z)) {
                    if (curr_input[k + x][i + y][j + z] == '#') {
                        count++;
                    }
                }
            }
        }
    }

    return count;
}

Cube run_cycle(Cube &curr_input) {
    make_cube_greater(curr_input);
    Cube new_cube = curr_input;

    for (int k = 0; k < new_cube.size(); k++) {
        for (int i = 0; i < new_cube[k].size(); i++) {
            for (int j = 0; j < new_cube[k][i].size(); j++) {
                int active_neighbors = count_neighbors(k, i, j, curr_input);
                char curr = new_cube[k][i][j];
                if (curr == '.') {
                    if (active_neighbors == 3) {
                        new_cube[k][i][j] = '#';
                    }
                } else {
                    if (active_neighbors != 2 && active_neighbors != 3) {
                        new_cube[k][i][j] = '.';
                    }
                }
            }
        }
    }

    return new_cube;
}

int count_active(const Cube &result) {
    int count = 0;
    for (const auto &f : result) {
        for (const auto &l : f) {
            for (const auto c : l) {
                if (c == '#')
                    count++;
            }
        }
    }

    return count;
}
}

int part_one() {
    Cube curr = input;
    for(int i = 0; i < 6; i++) {
        curr = part_1::run_cycle(curr);
    }

    return part_1::count_active(curr);
}

using HyperCube = std::vector<Cube>;

namespace part_2 {
void make_cube_greater(HyperCube &curr_input) {
    size_t new_size = curr_input[0][0].size() + 2;
    for(auto &cube : curr_input) {
        for (auto &face: cube) {
            for (auto &line : face) {
                line.insert(0, ".");
                line.push_back('.');
            }
            face.insert(face.begin(), std::string(new_size, '.'));
            face.emplace_back(new_size, '.');
        }
        cube.insert(cube.begin(),
                          std::vector<std::string>(new_size, std::string(new_size, '.')));
        cube.emplace_back(new_size, std::string(new_size, '.'));
    }
    curr_input.insert(curr_input.begin(),
                          Cube(new_size - 2, std::vector<std::string>(new_size, std::string(new_size, '.'))));
    curr_input.emplace_back(new_size - 2, std::vector<std::string>(new_size, std::string(new_size, '.')));

}

bool ok(int val, int low, int up) {
    return val >= low && val < up;
}

bool is_same_point(int l, int k, int i, int j) {
    return i == 0 && j == 0 && k == 0 && l == 0;
}

int count_neighbors(int l, int k, int i, int j, const HyperCube &curr_input) {
    int faces = curr_input.size();
    int size = curr_input[0][0].size();

    int count = 0;

    for(int u = -1; u < 2; u++) {
        for (int x = -1; x < 2; x++) {
            for (int y = -1; y < 2; y++) {
                for (int z = -1; z < 2; z++) {
                    if (ok(k + x, 0, faces) && ok(i + y, 0, size) && ok(j + z, 0, size) && ok(l + u, 0, faces)
                        && !is_same_point(x, y, z, u)) {
                        if (curr_input[l + u][k + x][i + y][j + z] == '#') {
                            count++;
                        }
                    }
                }
            }
        }
    }

    return count;
}

HyperCube run_cycle(HyperCube &curr_input) {
    make_cube_greater(curr_input);
    HyperCube new_cube = curr_input;

    for(int l = 0; l < new_cube.size(); l++) {
        for (int k = 0; k < new_cube[l].size(); k++) {
            for (int i = 0; i < new_cube[l][k].size(); i++) {
                for (int j = 0; j < new_cube[l][k][i].size(); j++) {
                    int active_neighbors = count_neighbors(l, k, i, j, curr_input);
                    char curr = new_cube[l][k][i][j];
                    if (curr == '.') {
                        if (active_neighbors == 3) {
                            new_cube[l][k][i][j] = '#';
                        }
                    } else {
                        if (active_neighbors != 2 && active_neighbors != 3) {
                            new_cube[l][k][i][j] = '.';
                        }
                    }
                }
            }
        }
    }

    return new_cube;
}

int count_active(const HyperCube &result) {
    int count = 0;
    for(const auto &cb : result) {
        for (const auto &f : cb) {
            for (const auto &l : f) {
                for (const auto c : l) {
                    if (c == '#')
                        count++;
                }
            }
        }
    }

    return count;
}
}

int part_two() {
    HyperCube curr;
    curr.push_back(input);
    for(int i = 0; i < 6; i++) {
        curr = part_2::run_cycle(curr);
    }

    return part_2::count_active(curr);
}

int main() {
    init();
    std::cout << part_one() << " " << part_two() << "\n";
    return 0;
}