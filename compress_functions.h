#pragma once

#include <unordered_map>
#include <string>
#include <queue>

struct Node {
    Node (std::string letters, int frequency, Node* left = nullptr, Node* right = nullptr)
        : letters{letters}, frequency{frequency}, left{left}, right{right} {}

    std::string letters;
    int frequency;
    Node* left, * right;
};

using FrequencyTable = std::unordered_map<char, int>;
FrequencyTable build_frequency_table(const std::string& text);

// Changing PQ to use std::greater to compare which results in a min PQ (default is max PQ)
inline auto compare_func = [](Node* left, Node* right) { return left->frequency > right->frequency; };
using HuffmanTree = std::priority_queue<Node*, std::vector<Node*>, decltype(compare_func)>;
void build_huffman_tree(HuffmanTree& tree);
void print_pq(HuffmanTree copy);
void print_huffman_tree(const HuffmanTree& tree);

using HuffmanCodes = std::unordered_map<char, std::string>;
void assign_huffman_codes(Node* n, HuffmanCodes& codes, const std::string& code = "");
void print_huffman_codes(const HuffmanCodes& codes);

std::string binary(const std::string& text);

std::string encode_string(const std::string& input, const HuffmanCodes& codes);
std::string decode_string(const std::string& input, const HuffmanTree& tree);