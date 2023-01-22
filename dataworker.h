#ifndef H_DATAWORKER
#define H_DATAWORKER

#include "configs/config.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>
#include <algorithm>
#include <cstring>


class DataWorker
{
public:

    DataWorker();
    void init();
    int getFrequence(char letter);
    int getFrequenceByPos(char letter, int pos);
    int getLetterScore(char letter, int pos);
    void updateValidWords(std::vector<std::string> answers);
    std::vector<std::string> getAnswers();

private:

    std::vector<std::string> answers, allAnswers;
    int positionScores[6][27];
    int totalAppereances[27], letterScore[6][27];

    void prelucrateData();
    void readData();
    void calculateInflunce();
};

#endif // H_DATAWORKER
