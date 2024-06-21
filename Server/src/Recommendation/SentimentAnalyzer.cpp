#include "SentimentAnalyzer.h"
#include <iostream>



   
    int SentimentAnalyzer::analyzeSentiment(const std::string& text) {
        std::vector<std::string> words = textProcessor.tokenize(
            textProcessor.removePunctuation(textProcessor.toLower(text)));
        int sentimentScore = 0;

        for (const std::string& word : words) {
            if (positiveWords.count(word) > 0) {
                sentimentScore++;
            } else if (negativeWords.count(word) > 0) {
                sentimentScore--;
            }
        }

    return sentimentScore;
}
