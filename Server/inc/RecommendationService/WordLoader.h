#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

class WordLoader {
public:
    std::unordered_set<std::string> loadWords(const std::string& filename) ;
};