
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

class TextProcessor {
public:
    std::string toLower(const std::string& str) ;

    std::string removePunctuation(const std::string& str) ;

    std::vector<std::string> tokenize(const std::string& text) ;
};