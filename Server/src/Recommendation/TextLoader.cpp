
#include"Server/inc/RecommendationService/TextLoader.h"


    std::string TextProcessor::toLower(const std::string& str) {
        std::string lowerStr = str;
        for (char& c : lowerStr) {
            c = std::tolower(c);
        }
        return lowerStr;
    }

    std::string TextProcessor::removePunctuation(const std::string& str) {
        std::string cleanStr;
        for (char c : str) {
            if (std::isalnum(c) || std::isspace(c)) {
                cleanStr += c;
            }
        }
        return cleanStr;
    }

    std::vector<std::string> TextProcessor::tokenize(const std::string& text) {
        std::vector<std::string> tokens;
        std::istringstream stream(text);
        std::string word;
        while (stream >> word) {
            tokens.push_back(word);
        }
        return tokens;
    }
