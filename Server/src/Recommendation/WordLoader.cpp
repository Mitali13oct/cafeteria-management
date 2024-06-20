#include"Server/inc/RecommendationService/WordLoader.h"

    std::unordered_set<std::string> WordLoader::loadWords(const std::string& filename) {
        std::unordered_set<std::string> words;
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string word;
            while (file >> word) {
                words.insert(word);
            }
            file.close();
        } else {
            std::cerr << "Unable to open file " << filename << std::endl;
        }
        return words;
    }
