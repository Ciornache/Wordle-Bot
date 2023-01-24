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
    int getTotalWords();
    void updateValidWords(std::vector<std::string> answers);
    std::vector<std::string> getAnswers();
    std::vector<std::string> getAllAnswers();

    friend class Referee;

private:
    std::vector<std::string> answers, allAnswers;
    int positionScores[POSITIONS][LETTERS];
    int totalAppereances[LETTERS], letterScore[POSITIONS][LETTERS];

    void prelucrateData(std::ofstream & fout);
    void readData();
    void calculateInflunce(std::ofstream & fout);
    void reset();

    void printAppearancesRanking(std::ofstream &fout);
    void printPositionRanking(std::vector<std::pair<int, char>> scoreBoard, int position, std::ofstream &fout);

};

#endif // H_DATAWORKER
