#include <iostream>
#include <map>
#include <string>
#include <vector>


int main() {

    int k, l;
    std::cin >> k >> l;

    std::map<std::string, std::string> matching;

    for (int i=0; i < k; i++) {
        std::string letter_, code;
        std::cin >> letter_ >> code;
        std::string letter = letter_.substr(0, letter_.size() - 1);
        matching[code] = letter;
    }

    std::string input;
    std::cin >> input;

    std::string helper("");
    std::string output("");

    for (auto chr: input) {
        helper += chr;
        if (matching.find(helper) != matching.end()) {
            output += matching[helper];
            helper = std::string("");
        }
    }

    std::cout << output;

    return 0;
}