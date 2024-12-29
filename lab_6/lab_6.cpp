#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <bitset>
#include <windows.h>

using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    HuffmanNode(HuffmanNode* l, HuffmanNode* r) : ch(0), freq(l->freq + r->freq), left(l), right(r) {}

    bool operator>(const HuffmanNode& other) const {
        return freq > other.freq;
    }
};

void generateCodes(HuffmanNode* root, const std::string& code, std::unordered_map<char, std::string>& codes) {
    if (!root) return;
    if (root->ch != 0) {
        codes[root->ch] = code;
    }
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& freqMap) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, std::greater<HuffmanNode*>> minHeap;

    for (const auto& entry : freqMap) {
        minHeap.push(new HuffmanNode(entry.first, entry.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* internalNode = new HuffmanNode(left, right);
        minHeap.push(internalNode);
    }

    return minHeap.top();
}

std::unordered_map<char, int> calculateFrequencies(const std::string& text) {
    std::unordered_map<char, int> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }
    return freqMap;
}

std::string decodeString(HuffmanNode* root, const std::string& encodedText) {
    std::string decodedText;
    HuffmanNode* current = root;

    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->ch;
            current = root;
        }
    }

    return decodedText;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    std::string input;
    std::cout << "Введите текст для кодирования: ";
    std::getline(std::cin, input);

    auto freqMap = calculateFrequencies(input);

    HuffmanNode* root = buildHuffmanTree(freqMap);

    std::unordered_map<char, std::string> codes;
    generateCodes(root, "", codes);

    std::cout << "\nТаблица частот символов:\n";
    int totalChars = input.size();
    for (const auto& entry : freqMap) {
        double percentage = (double(entry.second) / totalChars) * 100;
        std::cout << entry.first << ": " << entry.second << " (" << percentage << "%)\n";
    }

    std::cout << "\nТаблица соответствия символа и кода:\n";
    for (const auto& entry : codes) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }

    std::cout << "\nЗакодированная строка:\n";
    std::string encodedText;
    for (char c : input) {
        encodedText += codes[c];
    }
    std::cout << encodedText << std::endl;

    std::cout << "\nДекодированная строка:\n";
    std::string decodedText = decodeString(root, encodedText);
    std::cout << decodedText << std::endl;

    return 0;
}
