#ifndef H_REFEREE
#define H_REFEREE

#include "dataworker.h"

class Referee
{

public:
    Referee();
    void printStats();

    friend class Bot;

private:

    DataWorker dataWorker;
    struct result
    {
        bool verdict;
        std::vector<std::pair<int, char>> goodLetters, badLetters;
        std::vector<char> wrongLetters;
    };

    std::string answer;

    std::vector<std::pair<double, std::string>> stats;
    Referee::result evaluateWord(std::string word);

    double findEntropy(std::string word);
    double evaluatePattern(int pattern[], std::string word);
    double getWordScore(std::string word);

    bool judgeByResult(result rez, std::string word);
};

#endif /// H_REFEREE
