//
// Modified for Project 4 - Huffman Decoder
// Based on original by Kevin Rodriguez
//

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#pragma once
#include <vector>
#include <string>
#include <utility> // std::pair
#include <ostream>
#include <istream>
#include "TreeNode.h"
#include "utils.hpp"

class HuffmanTree {
public:
    HuffmanTree() = default;
    ~HuffmanTree(); // deletes the entire Huffman tree
    
    // Build Huffman tree from header file (for decoder)
    // Takes vector of (word, code) pairs and reconstructs the tree
    error_type buildFromHeader(const std::vector<std::pair<std::string, std::string>>& headerPairs);
    
    // Decode bitstream from code file and write decoded words to output
    error_type decode(std::istream& codeStream, std::ostream& outStream);

private:
    TreeNode* root_ = nullptr; // owns the full Huffman tree
    
    // Helper: destroy the entire tree
    static void destroy(TreeNode* n) noexcept;
};

#endif //HUFFMANTREE_H
