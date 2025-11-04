# CS 315 — Project 4: Huffman Decoder

**Student:** Kevin Rodriguez  
**Instructor:** Prof. Ali Kooshesh  
**Semester:** Fall 2025  
**Student ID:** 008858727  
**Course:** CS 315 – Data Structures  
**Repository:** [https://github.com/Pwingles/HuffmanDecoder](https://github.com/Pwingles/HuffmanDecoder)

---

## Overview

This project implements a Huffman decoder that reconstructs the original token sequence from compressed Huffman-encoded files. The decoder reads header files (`.hdr`) containing the Huffman tree structure and code files (`.code`) containing the encoded bitstream, then outputs a decoded tokens file (`.tokens_decoded`) that should match the original `.tokens` file.

---

## Project Status

### Current State

The decoder implementation is **complete**:

**Completed:**
- ✓ Basic project structure and file organization
- ✓ HuffmanTree class with decoder methods implemented
- ✓ TreeNode structure for Huffman tree nodes
- ✓ Utility functions for error handling (utils.hpp, utils.cpp)
- ✓ Main function with command-line argument parsing
- ✓ `readHeader()` - Parses header file into (word, code) pairs
- ✓ `buildFromHeader()` - Reconstructs Huffman tree from header pairs
- ✓ `decode()` - Decodes bitstream using the reconstructed tree
- ✓ Output filename generation from code file base name
- ✓ Basic error checking (command-line args, file opening)
- ✓ Input/output test files provided in `input_output/` directory
- ✓ Git repository initialized and pushed to GitHub

---

## Collaboration & Sources

**Project 3 Reused Code:**
- `TreeNode.h` - Node structure for Huffman trees
- `utils.hpp` and `utils.cpp` - Error handling and file utilities
- `HuffmanTree.h` and `HuffmanTree.cpp` - Base class structure (significantly modified for decoder-only functionality)

**External Resources:**
- Project specification provided by instructor
- C++ reference documentation for file I/O and data structures
- Course textbook and lecture materials on Huffman coding

**AI-Assisted Development:**
- Used AI for code organization and skeleton generation
- Used AI for README formatting and structure
- No AI-generated code implementations (all core logic is written by me, Kevin Rodriguez)

**Original Work:**
- All decoder-specific implementations (buildFromHeader, decode, readHeader)
- Main function logic and error checking
- File parsing and validation logic

---

## Testing & Status

### Current Status

**Implementation Progress:** 100% complete

**Files:**
- `main.cpp` - Complete implementation with argument parsing and file handling
- `HuffmanTree.cpp` - All methods implemented (buildFromHeader, decode, destroy)
- `HuffmanTree.h` - Interface fully defined
- `TreeNode.h` - Structure defined
- `utils.hpp/cpp` - Utility functions available

**Testing Plan:**

1. Test with `lab08_input` files (smallest test case)
2. Test with chapter files (medium complexity)
3. Test with complete book files (largest test case)
4. Verify output matches original `.tokens` files using `diff`
5. Test error handling (invalid files, malformed input)
6. Ensure program compiles and runs on blue.cs.sonoma.edu

### Expected Behavior

```
$ ./huffman_decoder.x lab08_input.hdr lab08_input.code
```

Should generate:
```
input_output/lab08_input.tokens_decoded
```

And the output should match:
```
input_output/lab08_input.tokens
```

Verified with:
```
diff input_output/lab08_input.tokens_decoded input_output/lab08_input.tokens
```

**Note:** The program expects input file names (without the `input_output/` prefix) as arguments, but automatically resolves them under the `input_output/` directory. The output file is also placed in `input_output/` with the base name of the code file.

---

## File Structure

```
HuffmanDecoder/
├── main.cpp                    # Main entry point with argument handling
├── HuffmanTree.h              # Huffman tree class declaration
├── HuffmanTree.cpp            # Tree building and decoding methods
├── TreeNode.h                 # Node structure
├── utils.hpp                  # Utility function declarations
├── utils.cpp                  # Utility implementations
├── input_output/              # Test files
│   ├── lab08_input.hdr
│   ├── lab08_input.code
│   ├── lab08_input.tokens
│   └── [other test files]
└── README.md                  # This file
```

---

## Build Instructions

**To compile:**
```bash
g++ -std=c++20 -Wall *.cpp -o huffman_decoder.x
```

**To run:**
```bash
./huffman_decoder.x <header.hdr> <code.code>
```

**Example:**
```bash
./huffman_decoder.x lab08_input.hdr lab08_input.code
```

**Note:** The program automatically resolves input files under the `input_output/` directory and places output files there as well. Pass only the filenames (not full paths) as arguments.

---

## Implementation Details

### Decoding Process

1. Reads header file line by line and parses (word, code) pairs using `readHeader()`
2. Reconstructs Huffman tree by following code paths (0=left, 1=right) using `buildFromHeader()`
3. Reads code file character by character and skips newlines
4. Traverses tree based on each bit (0=left, 1=right)
5. Outputs word when leaf is reached and resets to root
6. Writes decoded output to `.tokens_decoded` file

## Notes

This project is a standalone decoder that works with the output of Project 3 (Huffman encoder). The decoder reconstructs the Huffman tree from header files and uses it to decode bitstreams back into word sequences.

This project focuses specifically on decoding functionality and does not include any encoder components.

The implementation follows the requirements specified in Project4.txt.

