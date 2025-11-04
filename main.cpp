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
        // If no space found, skip this line as we dont have a pair to write out (though we wont have that issue)
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
    
    // Verify that both input arguments are readable files
    error_type status = regularFileExistsAndIsAvailable(hdrPath);
    if (status != NO_ERROR) {
        std::cerr << "Error: Header file not found or cannot be opened: " << hdrPath << "\n";
        return 1;
    }
    
    status = regularFileExistsAndIsAvailable(codePath);
    if (status != NO_ERROR) {
        std::cerr << "Error: Code file not found or cannot be opened: " << codePath << "\n";
        return 1;
    }
    
    // The header file should start with a letter (not 0 or 1)
    std::ifstream hdrCheck(hdrPath);
    if (!hdrCheck.is_open()) {
        std::cerr << "Error: Unable to open header file for validation\n";
        return 1;
    }
    std::string firstLine;
    if (std::getline(hdrCheck, firstLine)) {
        if (!firstLine.empty()) {
            char firstChar = firstLine[0];
            if (firstChar == '0' || firstChar == '1') {
                std::cerr << "Error: Header file should start with a letter, not a digit\n";
                hdrCheck.close();
                return 1;
            }
        }
    }
    hdrCheck.close();
    
    //  The code file should start with a 0 or 1
    std::ifstream codeCheck(codePath);
    if (!codeCheck.is_open()) {
        std::cerr << "Error: Unable to open code file for validation\n";
        return 1;
    }
    char firstCodeChar;
    bool foundValidChar = false;
    while (codeCheck.get(firstCodeChar)) {
        if (firstCodeChar == '0' || firstCodeChar == '1') {
            foundValidChar = true;
            break;
        } else if (firstCodeChar != '\n' && firstCodeChar != '\r') {
            // If we find a non-whitespace character that's not 0 or 1, it's invalid
            std::cerr << "Error: Code file should start with 0 or 1\n";
            codeCheck.close();
            return 1;
        }
    }
    codeCheck.close();
    
    if (!foundValidChar) {
        std::cerr << "Error: Code file does not contain valid bits (0 or 1)\n";
        return 1;
    }
    
    // Read the header into the vector pair 
    std::vector<std::pair<std::string, std::string>> headerPairs; // Declared outside, passed by ref inside

    status = readHeader(hdrPath, headerPairs);
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


    const std::string base = codePathFs.stem().string();
    const fs::path out = dir / (base + ".tokens_decoded");
    std::string outputPath = out.string();
    
    // Confirm that the output file can be created and opened for writing
    status = canOpenForWriting(outputPath);
    if (status != NO_ERROR) {
        std::cerr << "Error: Cannot open output file for writing: " << outputPath << "\n";
        return 1;
    }

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
    //  If code file ends while traversal is at internal node, print error and exit
    status = decoder.decode(codeStream, outStream);
    if (status != NO_ERROR) {
        if (status == INCOMPLETE_CODE) {
            std::cerr << "Error: Code file ended while traversal was still at an internal node (incomplete code)\n";
        } else {
            std::cerr << "Error: decode failed\n";
        }
        codeStream.close();
        outStream.close();
        return 1;
    }
    codeStream.close();
    outStream.close();
    

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