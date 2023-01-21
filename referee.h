#ifndef H_REFEREE
#define H_REFEREE

#include "dataworker.h"

class Referee
{
public:
    Referee();
    DataWorker dataWorker;
    friend class Bot;
    double getWordScore(std::string word);
    private:
    
        std::string answer;
        struct result
        {
            bool verdict;
            std::vector<std::pair<int, char>> goodLetters, badLetters;
            std::vector<char> wrongLetters;
        };

        result evaluateWord(std::string word);

};

#endif /// H_REFEREE