// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include <algorithm>
#include <vector>
#include <utility>
#include <string>

static bool isLatin(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
static char toLowerCase(char c) {
  return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "Error: Cannot open sacred text '" << filename << "'\n";
    return;
  }
  std::string currentLexeme;
  while (file) {
    int ch = file.get();
    if (ch == std::char_traits<char>::eof()) break;
    char glyph = static_cast<char>(ch);
    if (isLatin(glyph)) {
      currentLexeme.push_back(toLowerCase(glyph));
    } else if (!currentLexeme.empty()) {
      tree.insert(currentLexeme);
      currentLexeme.clear();
    }
  }
  if (!currentLexeme.empty()) {
    tree.insert(currentLexeme);
  }
  std::cout << "File analyzed successfully.\n";
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> vec;
  tree.getFreqList(vec);
  std::sort(vec.begin(), vec.end(),
    [](const std::pair<std::string, int>& a,
      const std::pair<std::string, int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
  std::ofstream out("result/freq.txt");
  for (const auto& p : vec) {
    std::cout << p.first << " " << p.second << "\n";
    out << p.first << " " << p.second << "\n";
  }
}
