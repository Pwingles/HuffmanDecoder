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

The decoder skeleton has been created with the following components:

**Completed:**
- Basic project structure and file organization
- HuffmanTree class with declarations for decoder methods
- TreeNode structure for Huffman tree nodes
- Utility functions for error handling (utils.hpp, utils.cpp)
- Main function with command-line argument parsing
- Input/output test files provided in `input_output/` directory
- Git repository initialized and pushed to GitHub

**TODO Implementation:**
- `buildFromHeader()` - Reconstruct Huffman tree from header file
- `decode()` - Decode bitstream using the reconstructed tree
- `readHeader()` - Parse header file into (word, code) pairs
- Generate output filename from input filename
- File validation and error checking

### What Needs to be Done

1. **Implement `readHeader()` function** in `main.cpp`
   - Read `.hdr` file line by line
   - Parse "word code" format
   - Store pairs in vector

2. **Implement `buildFromHeader()` method** in `HuffmanTree.cpp`
   - Start with empty root node
   - For each (word, code) pair:
     - Traverse tree following code path (0=left, 1=right)
     - Create nodes as needed
     - Assign word to leaf node

3. **Implement `decode()` method** in `HuffmanTree.cpp`
   - Read bitstream from code file
   - Skip newline characters
   - Traverse tree for each bit (0=left, 1=right)
   - When leaf reached, output word and reset to root
   - Continue until stream consumed

4. **Complete `main()` function** in `main.cpp`
   - Validate command-line arguments
   - Extract base name and create output path
   - Read header file
   - Build Huffman tree
   - Open streams
   - Decode and write output
   - Add error handling

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
- No AI-generated code implementations (all core logic will be student-written)

**Original Work:**
- All decoder-specific implementations (buildFromHeader, decode, readHeader)
- Main function logic and orchestration
- File parsing and validation logic

---

## Testing & Status

### Current Status

**Implementation Progress:** 0% complete (skeleton only)

**Files:**
- `main.cpp` - Basic structure with argument parsing
- `HuffmanTree.cpp` - Method declarations with TODOs
- `HuffmanTree.h` - Interface defined
- `TreeNode.h` - Structure defined
- `utils.hpp/cpp` - Utility functions available

**Testing Plan:**

Once implementation is complete:
1. Test with `lab08_input` files (smallest test case)
2. Test with chapter files (medium complexity)
3. Test with complete book files (largest test case)
4. Verify output matches original `.tokens` files using `diff`
5. Test error handling (invalid files, malformed input)
6. Ensure program compiles and runs on blue.cs.sonoma.edu

### Expected Behavior

```
$ ./huff_decode.x input_output/lab08_input.hdr input_output/lab08_input.code
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
g++ -std=c++20 -Wall *.cpp -o huff_decode.x
```

**To run:**
```bash
./huff_decode.x <header.hdr> <code.code>
```

**Example:**
```bash
./huff_decode.x input_output/lab08_input.hdr input_output/lab08_input.code
```

---

## Notes

This project is a standalone decoder that works with the output of Project 3 (Huffman encoder). The decoder reconstructs the Huffman tree from header files and uses it to decode bitstreams back into word sequences.

This project focuses specifically on decoding functionality and does not include any encoder components.

