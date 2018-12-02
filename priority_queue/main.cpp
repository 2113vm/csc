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
    void siftDown(unsigned int index);
    unsigned int findMax(unsigned int ind1, unsigned int ind2);
};

PriorityQueue::PriorityQueue(unsigned int number) {
    vector<int> queue(number);
}

void PriorityQueue::insert(int num) {
    queue.push_back(num);
    int index = static_cast<unsigned int>(queue.size());
    siftUp(index);
}

int PriorityQueue::extractMax() {
    int max = queue[0];
    queue[0] = queue[queue.size() - 1];
    queue.pop_back();
    siftDown(1);
    return max;
}

void PriorityQueue::siftDown(unsigned int index) {
    unsigned int max_index, ch1, ch2;
    max_index = static_cast<unsigned int>(queue.size());

    ch1 = index * 2;
    ch2 = index * 2 + 1;

    if (max_index < ch1) {
        return;
    }
    if (max_index >= ch2) {
        unsigned int max_ch = findMax(ch1, ch2);
        if (queue[index - 1] >= queue[max_ch - 1]) {
            return;
        } else {
            int helper;
            helper = queue[index - 1];
            queue[index - 1] = queue[max_ch - 1];
            queue[max_ch - 1] = helper;
            siftDown(max_ch);
        }
    }
    if (max_index == ch1) {
        if (queue[index - 1] >= queue[ch1 - 1]) {
            return;
        } else {
            int helper;
            helper = queue[index - 1];
            queue[index - 1] = queue[ch1 - 1];
            queue[ch1 - 1] = helper;
            return;
        }

    }
}

void PriorityQueue::siftUp(int index) {
    int parent_index = index / 2;
    if (parent_index == 0) {
        return;
    }
    if (queue[parent_index - 1] < queue[index - 1]) {
        int helper;
        helper = queue[parent_index - 1];
        queue[parent_index - 1] = queue[index - 1];
        queue[index - 1] = helper;
        siftUp(parent_index);
    }
}

unsigned int PriorityQueue::findMax(unsigned int ind1, unsigned int ind2) {

    if (queue[ind1 - 1] < queue[ind2 - 1]) {
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