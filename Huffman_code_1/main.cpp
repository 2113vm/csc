#include <utility>

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>


std::map <char, int> counter(std::string s) {
    std::map <char, int> freq;

    for (auto chr : s) {
        if (freq.find(chr) != freq.end()) {
            freq[chr] += 1;
        } else {
            freq[chr] = 1;
        }
    }

    return freq;
}

struct Node {

    Node *left;
    Node *right;
    double f;
    char chr;

    Node(double f, char chr, Node* left, Node* right) : f(f), chr(chr), left(left), right(right) { }

    bool operator<(const Node& rhs) const {
        return f > rhs.f;
    }

};


std::priority_queue<Node> build_queue(std::map <char, int> freq) {

    std::priority_queue <Node> queue;

    for (auto f: freq) {

        Node* n = new Node(f.second, f.first, nullptr, nullptr);
        queue.push(*n);
    }

    return queue;
}


Node build_tree(std::map <char, int> freq) {
    std::priority_queue<Node> queue = build_queue(std::move(freq));

    while (queue.size() > 1) {
        Node node1 = queue.top();
        Node* node1_ = new Node(node1.f, node1.chr, node1.left, node1.right);
        queue.pop();
        Node node2 = queue.top();
        Node* node2_ = new Node(node2.f, node2.chr, node2.left, node2.right);
        queue.pop();
        Node* parent = new Node(node1_->f+node2_->f, ' ', node1_, node2_);
        queue.push(*parent);
    }

    Node root = queue.top();
    queue.pop();

    return root;
}

std::string find_leaf(Node *root, std::string output, char chr) {
    if (root->chr == chr) {
        return output;
    }
    if (root->left != nullptr) {
        std::string output_ = output + std::string("0");
        std::string res = find_leaf(root->left, output_, chr);
        if (res != std::string("")) {
            return res;
        }
    }
    if (root->right != nullptr) {
        std::string output_ = output + std::string("1");
        std::string res = find_leaf(root->right, output_, chr);
        if (res != std::string("")) {
            return res;
        }
    }
    return std::string("");
}


int main() {

    std::string s;

    std::cin >> s;

    std::map<char, int> freq = counter(s);

    int count_chars = (int) freq.size();

    if (freq.size() == 1) {

        std::string output("0");
        for (int i=0; i < s.size() - 1; i++) {
            output += "0";
        }
        std::cout << 1 << " " << output.size() << "\n";
        std::cout << freq.begin()->first << ": " << 0 << "\n";
        std::cout << output;
        return 0;
    }

    Node root = build_tree(freq);

    std::map <char, std::string> mapping;

    std::string output("");
    for (auto chr: s) {
        std::string helper("");
        std::string out = find_leaf(&root, helper, chr);
        output += out;
        mapping[chr] = out;
    }

    std::cout << count_chars << " " << output.size() << "\n";
    for (auto f: mapping) {
        std::cout << f.first << ": " << f.second << "\n";
    }
    std::cout << output;


    return 0;
}
