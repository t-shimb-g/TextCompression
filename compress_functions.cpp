#include "compress_functions.h"
#include <iostream>
#include <iomanip>
#include <bitset>

// using FrequencyTable = std::unordered_map<char, int>;
FrequencyTable build_frequency_table(const std::string& text) {
    FrequencyTable freq_table;
    for (char c : text) {
        if (freq_table.contains(c)) {
            ++freq_table.find(c)->second;
        }
        else {
            freq_table.insert({c, 1});
        }
    }
    return freq_table;
}

void build_huffman_tree(HuffmanTree& tree) {
    while (tree.size() > 1) {
        Node* node_right = new Node{*tree.top()};
        tree.pop();
        Node* node_left = new Node{*tree.top()};
        tree.pop();
        Node* root = new Node{node_left->letters + node_right->letters, node_left->frequency + node_right->frequency, node_left, node_right};
        tree.push(root);
    }
}

void print_pq(HuffmanTree copy) {
    std::cout << "\nPriority Queue:\n";
    while (!copy.empty()) {
        std::cout << '(' << copy.top()->letters << ", " << copy.top()->frequency << ") -> ";
        copy.pop();
    }
    std::cout << "nullptr\n";
}

void print_tree(Node* n, int level)  {
    if (n) {
        if (n->right) {
            print_tree(n->right, level+4);
            std::cout << std::setw(level+2) << "/\n";
        }

        std::cout << std::setw(level-1) << '(' << n->letters << ", " << n->frequency << ')' << '\n';

        if (n->left) {
            std::cout << std::setw(level+2) << "\\\n";
            print_tree(n->left, level+4);
        }
    }
}

void print_huffman_tree(const HuffmanTree& tree) { // Printing order: Right -> Root -> Left
    std::cout << "\nHuffman encoding tree: \n";
    print_tree(tree.top(), 1);
}

void assign_huffman_codes(Node* n, HuffmanCodes& codes, const std::string& code) {
    if (n->left == nullptr && n->right == nullptr) { // Found a char
        codes.insert( {n->letters[0], code} ); // n->letters is string, aka a vector of chars, [0] is the char
        return;
    }
    assign_huffman_codes(n->left, codes, code + "0");
    assign_huffman_codes(n->right, codes, code + "1");
}

void print_huffman_codes(const HuffmanCodes& codes) {
    std::cout << "\nHuffman codes:\n";
    for (auto x : codes) {
        std::cout << x.first << ": " << x.second << '\n';
    }
}

std::string binary(const std::string& text) {
    std::stringstream ss;
    for (char c : text) {
        ss << std::bitset<8>(c);
    }
    return ss.str();
}

std::string encode_string(const std::string& input, const HuffmanCodes& codes) {
    std::string encoded_str;
    for (char c : input) {
        encoded_str += codes.find(c)->second;
    }
    return encoded_str;
}

std::string decode_string(const std::string& input, const HuffmanTree& tree) {
    Node n = *tree.top();
    std::string decoded_str;
    for (char c : input) {
        if (c == '0') {
            n = *n.left;
        }
        else {
            n = *n.right;
        }
        if (n.left == nullptr && n.right == nullptr) {
            decoded_str += n.letters;
            n = *tree.top();
        }
    }
    return decoded_str;
}