#include <iostream>
#include <vector>

using std::vector;

class PriorityQueue{
public:
    PriorityQueue(unsigned int number);
    void insert(int num);
    int extractMax();

private:
    vector<int> queue;
    void siftUp(int index);
    void siftDown(int index);
    int findMax(int ind1, int ind2);
};

PriorityQueue::PriorityQueue(unsigned int number) {
    vector<int> queue(number);
}

void PriorityQueue::insert(int num) {
    queue.push_back(num);
    int index = static_cast<unsigned int>(queue.size() - 1);
    siftUp(index);
}

int PriorityQueue::extractMax() {
    int max = queue[0];
    queue[0] = queue[queue.size() - 1];
    queue.pop_back();
    siftDown(0);
    return max;
}

void PriorityQueue::siftDown(int index) {
    unsigned int max_index, ch1, ch2;
    max_index = static_cast<unsigned int>(queue.size() - 1);
    if (index == 0) {
        ch1 = 1;
        ch2 = 2;
    } else {
        ch1 = index * 2;
        ch2 = index * 2 + 1;
    }
    if (max_index < ch1) {
        return;
    }
    if (max_index >= ch2) {
        int max_ch = findMax(ch1, ch2);
        if (queue[index] >= queue[max_ch]) {
            return;
        } else {
            int helper;
            helper = queue[index];
            queue[index] = queue[max_ch];
            queue[max_ch] = helper;
            siftDown(max_ch);
        }
    }
    if (max_index == ch1) {
        if (queue[index] >= queue[ch1]) {
            return;
        } else {
            int helper;
            helper = queue[index];
            queue[index] = queue[ch1];
            queue[ch2] = helper;
            return;
        }

    }
}

void PriorityQueue::siftUp(int index) {
    int parent_index = index / 2;
    if (queue[parent_index] < queue[index]) {
        int helper;
        helper = queue[parent_index];
        queue[parent_index] = queue[index];
        queue[index] = helper;
        siftUp(parent_index);
    }
}

int PriorityQueue::findMax(int ind1, int ind2) {

    if (queue[ind1] < queue[ind2]) {
        return ind2;
    } else {
        return ind1;
    }
}


int main() {

    unsigned int number_operation;
    std::cin >> number_operation;
    auto *queue = new PriorityQueue(number_operation);

    vector<int> output;

    for (int i = 0; i < number_operation; i++) {
        std::string command;
        int num;
        std::cin >> command;
        if (command == std::string("ExtractMax")) {
            output.push_back(queue->extractMax());
        } else {
            std::cin >> num;
            queue->insert(num);
        }
    }

    for (auto out : output) {
        std::cout << out << std::endl;
    }


    return 0;
}