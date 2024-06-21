#ifndef SENTIMENT_ANALYZER_H
#define SENTIMENT_ANALYZER_H

#include <unordered_set>
#include <string>
#include "TextLoader.h"
#include<vector>

class SentimentAnalyzer {
private:
    std::unordered_set<std::string> positiveWords;
    std::unordered_set<std::string> negativeWords;
    TextProcessor textProcessor;

public:
    SentimentAnalyzer(const std::unordered_set<std::string>& positiveWords,
                      const std::unordered_set<std::string>& negativeWords)
        : positiveWords(positiveWords), negativeWords(negativeWords),textProcessor() {}

    int analyzeSentiment(const std::string& text) ;
};

#endif // SENTIMENT_ANALYZER_H
