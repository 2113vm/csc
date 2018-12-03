#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int get_pos(const std::vector<int> &numbers, int number) {

    int l=0, r=numbers.size() - 1;


    if ((number > numbers[r]) or (number < numbers[0])) {
        return -1;
    }

    while (l <= r) {
        int m = l + (r - l) / 2;
        if (numbers[m] == number) {
            return m + 1;
        }
        if (numbers[m] > number) {
            r = m - 1;
        }
        if (numbers[m] < number) {
            l = m + 1;
        }
    }
    return -1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    size_t number_count;
    std::cin >> number_count;
    std::vector<int> numbers(number_count);
    for (auto &number:numbers) {
        std::cin >> number;
    }

    size_t query_count;
    std::cin >> query_count;
    while (query_count-- > 0) {
        int number;
        std::cin >> number;
        std::cout << get_pos(numbers, number) << " ";
    }
    std::cout << std::endl;
}