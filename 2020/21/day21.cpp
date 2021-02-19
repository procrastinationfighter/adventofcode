#include <iostream>
#include <vector>
#include <regex>
#include <set>
#include <algorithm>

std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>> input;
std::set<std::string> all_ingredients;
std::set<std::string> all_allergens;

std::map<std::string, std::vector<std::string>> candidates;

void init() {
    std::string curr;
    std::regex word_regex(R"((\w+))");
    std::smatch match;
    while(std::getline(std::cin, curr)) {
        std::vector<std::string> ingredients, allergens;
        std::string curr_r = curr;

        while(std::regex_search(curr_r, match, word_regex) && match[0].str() != "contains") {
            auto curr_ingr = match[0].str();
            ingredients.push_back(curr_ingr);
            curr_r = match.suffix();
            all_ingredients.insert(curr_ingr);
        }

        curr_r = match.suffix();

        while(std::regex_search(curr_r, match, word_regex)) {
            auto curr_aller = match[0].str();
            allergens.push_back(curr_aller);
            curr_r = match.suffix();
            all_allergens.insert(curr_aller);
        }

        std::sort(ingredients.begin(), ingredients.end());
        std::sort(allergens.begin(), allergens.end());
        input.emplace_back(ingredients, allergens);
    }
}

int part_one() {
    for(const auto &aller : all_allergens) {
        std::vector<std::string> c;
        std::copy(all_ingredients.begin(), all_ingredients.end(), std::back_inserter(c));
        std::sort(c.begin(), c.end());
        candidates[aller] = c;
    }

    for(const auto &line : input) {
        for(const auto &curr_aller : line.second) {
            auto &cands = candidates[curr_aller];

            auto it = std::set_intersection(line.first.begin(), line.first.end(), cands.begin(), cands.end(), cands.begin());
            cands.resize(it - cands.begin());
        }
    }

    auto legal_set = all_ingredients;

    for(const auto &cands : candidates) {
        for(const auto &x : cands.second) {
            legal_set.erase(x);
        }
    }

    int sum = 0;
    for(const auto &x : legal_set) {
        for(const auto &y : input) {
            for(const auto &z : y.first) {
                if(x == z) {
                    sum++;
                }
            }
        }
    }

    return sum;
}

std::string part_two() {
    std::vector<std::pair<std::string, std::set<std::string>>> result;
    for(const auto &cands : candidates) {
        std::set<std::string> new_set(cands.second.begin(), cands.second.end());
        result.emplace_back(cands.first, new_set);
    }

    std::sort(result.begin(), result.end());

    std::vector<bool> removed(result.size(), false);

    int omitted = 0;
    while(omitted < removed.size()) {
        omitted = 0;

        for(int i = 0; i < result.size(); i++) {
            if(!removed[i] && result[i].second.size() == 1) {
                removed[i] = true;
                for(int j = 0; j < result.size(); j++) {
                    if(j != i) {
                        result[j].second.erase(*result[i].second.begin());
                    }
                }
            }
            else {
                omitted++;
            }
        }
    }

    std::string answer;

    for(auto &x : result) {
        answer.append(*x.second.begin());
        answer.push_back(',');
    }

    return answer;
}

int main() {
    init();
    std::cout << part_one() << " " << part_two() << "\n";
    return 0;
}