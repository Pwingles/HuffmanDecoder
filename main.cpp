//
// Huffman Decoder - Project 4
//

#include <iostream>
#include <string>
#include <vector>
#include "utils.hpp"

// Function to read header file
error_type readHeader(const std::string& hdrPath, 
                      std::vector<std::pair<std::string, std::string>>& headerPairs);

int main(int argc, char* argv[]) {
    // Check command-line arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <header.hdr> <code.code>\n";
        return 1;
    }
    
    std::string hdrPath = argv[1];
    std::string codePath = argv[2];
    
    // TODO: Extract base name from codePath and create output path
    // Output should be: base_name.tokens_decoded
    
    return 0;
}

