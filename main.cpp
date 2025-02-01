#include <iostream>
#include <unordered_map>
#include "compress_functions.h"

int main() {
    std::string input;
    std::cout << "Please enter a message:\n";
    std::getline(std::cin, input);
    FrequencyTable freq = build_frequency_table(input);

    HuffmanTree huff_tree;

    std::cout << "\nFrequency Table:\n";
    for (auto x : freq) {
        std::cout << x.first << ": " << x.second << '\n';
        Node* n = new Node{std::string(1, x.first), x.second}; // Changing x.first (type char) to std::string type for Node
        huff_tree.push(n);
    }

    print_pq(huff_tree);

    build_huffman_tree(huff_tree);
    print_huffman_tree(huff_tree);

    HuffmanCodes huff_codes;

    assign_huffman_codes(huff_tree.top(), huff_codes);
    print_huffman_codes(huff_codes);

    std::cout << "\nUncompressed bit sequence:\n";
    const std::string binary_input = binary(input);
    std::cout << binary_input << '\n';

    std::cout << "\nEncoded:\n";
    const std::string encoded_input = encode_string(input, huff_codes);
    std::cout << encoded_input << '\n';

    std::cout << "\nDecoded:\n";
    const std::string decoded_input = decode_string(encoded_input, huff_tree);
    std::cout << decoded_input << '\n';

    const float compress_percent = encoded_input.length() * 100.0 / binary_input.length();
    std::cout << "\nCompressed to " << compress_percent << "% of original size\n";
}