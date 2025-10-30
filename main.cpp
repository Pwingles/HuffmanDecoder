//
// Huffman Decoder - Project 4
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "utils.hpp"
#include "HuffmanTree.h"
#include <filesystem>
namespace fs = std::filesystem;


// Function to read header file
error_type readHeader(const std::string& hdrPath, 
                      std::vector<std::pair<std::string, std::string>>& headerPairs){
    
    // Open File
    std::ifstream hdrFile(hdrPath);
    if (!hdrFile.is_open()) {
        return UNABLE_TO_OPEN_FILE;
    }

    //Read each line from the file
    std::string line;
    while (std::getline(hdrFile, line)) {
        
        // Skip empty lines - if line has nothing in it, go to next line
        if (line.empty()) {
            continue;
        }
        // Find where the space is between word and code
        int spacePosition = -1;
        for (unsigned int i = 0; i < line.length(); i++) {
            if (line[i] == ' ') {
                spacePosition = i;
                break;  // found the first space, we're done
            }
        }
        // If no space found, skip this line
        if (spacePosition == -1) {
            continue;
        }
        // Extract the word (everything before the space)
        std::string word;
        for (int i = 0; i < spacePosition; i++) {
            word += line[i];
        }
        // Extract the code (everything after the space)
        std::string code;
        for (unsigned int i = spacePosition + 1; i < line.length(); i++) {
            code += line[i];
        }
        // Push the word and code to the vector
        headerPairs.push_back({word, code});
    }

    hdrFile.close();
    return NO_ERROR;
}






int main(int argc, char* argv[]) {
    // Check command-line arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <header.hdr> <code.code>\n";
        return 1;
    }
    
    // Resolve inputs under input_output/ to match project conventions
    const fs::path dir = "input_output";
    const fs::path hdrPathFs = dir / argv[1];
    const fs::path codePathFs = dir / argv[2];
    const std::string hdrPath = hdrPathFs.string();
    const std::string codePath = codePathFs.string();
    
    // Read the header into the vector pair 
    std::vector<std::pair<std::string, std::string>> headerPairs;
    error_type status = readHeader(hdrPath, headerPairs);
    if (status != NO_ERROR) {
        std::cerr << "Failed to read header file\n";
        return 1;
    }

    // Pass headerPairs to decoder to build the tree, HuffmanTree owns 
    HuffmanTree decoder;
    status = decoder.buildFromHeader(headerPairs);
    if(status != NO_ERROR) {
        std::cerr << "Failed to build HuffmanTree\n";
        return 1;
    }

    // Build output path in same directory using base name (to mirror encoder style)
    const std::string base = codePathFs.stem().string();
    const fs::path out = dir / (base + ".tokens_decoded");
    std::string outputPath = out.string();

    // Open streams
    std::ifstream codeStream(codePath);
    if (!codeStream.is_open()) {
        std::cerr << "Error: unable to open code file: " << codePath << "\n";
        return 1;
    }

    std::ofstream outStream(outputPath);
    if (!outStream.is_open()) {
        std::cerr << "Error: unable to open output file: " << outputPath << "\n";
        return 1;
    }

    // pass both streams to decode
    if (decoder.decode(codeStream, outStream) != NO_ERROR) {
        std::cerr << "Error: decode failed\n";
        return 1;
    }
    

    return 0;
}





















// Function tests 


/**
    readHeader test



    std::vector<std::pair<std::string, std::string>> testPairs;
    error_type status = readHeader(hdrPath, testPairs);
    
    if (status == NO_ERROR) {
        std::cout << "Successfully read " << testPairs.size() << " pairs\n";
        
        // Print first 5 pairs to see if they're correct
        std::cout << "\nFirst 5 pairs:\n";
        for (int i = 0; i < std::min(5, (int)testPairs.size()); i++) {
            std::cout << "Word: " << testPairs[i].first 
                      << " | Code: " << testPairs[i].second << std::endl;
        }
    } 
    else {
        std::cout << "Error reading header file!\n";
    }

*/