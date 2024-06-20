#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include"TextLoader.h"


class SentimentAnalyzer {
private:
    std::unordered_set<std::string> positiveWords;
    std::unordered_set<std::string> negativeWords;
    TextProcessor textProcessor;

public:
    SentimentAnalyzer(const std::unordered_set<std::string>& positiveWords,
                      const std::unordered_set<std::string>& negativeWords)
        : positiveWords(positiveWords), negativeWords(negativeWords) {}

    int analyzeSentiment(const std::string& text) ;
};