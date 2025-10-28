//
// Huffman decoder
// Decodes project 3 encoder output
//

#include "HuffmanTree.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

/**
 * Destructor - deletes the entire Huffman tree
 * Recursively destroys all nodes starting from the root
 */
HuffmanTree::~HuffmanTree() {
    destroy(root_);
}

/**
 * TODO: Build tree from header file
 * - Loop through each (word, code) pair
 * - Start at root, follow code path: 0=left, 1=right
 * - Create nodes if they don't exist
 * - Put word in leaf node when you reach end of code
 */
error_type HuffmanTree::buildFromHeader(const std::vector<std::pair<std::string, std::string>>& headerPairs) {
    // TODO: Implement this function
    return NO_ERROR;
}

/**
 * TODO: Decode the bitstream
 * - Read each character from codeStream
 * - Skip newline characters (ignore them)
 * - 0 = go left, 1 = go right in tree
 * - When you hit a leaf, write the word to outStream
 * - Go back to root and repeat
 */
error_type HuffmanTree::decode(std::istream& codeStream, std::ostream& outStream) {
    // TODO: Implement this function
    return NO_ERROR;
}

/**
 * Helper: Recursively destroy the entire tree
 * 
 * Performs a post-order traversal to delete all nodes
 * starting from the given node.
 * 
 * @param n Pointer to the root of the subtree to destroy
 */
void HuffmanTree::destroy(TreeNode* n) noexcept {
    if(n == nullptr) {
        return;
    }
    
    destroy(n->left);
    destroy(n->right);
    delete n;
}
