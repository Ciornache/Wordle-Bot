#include "dataworker.h"

DataWorker::DataWorker()
{
    this->init();
}

void DataWorker::init()
{
    this->readData();
    this->prelucrateData();
}

int DataWorker::getFrequence(char letter)
{
    return totalAppereances[letter - 'a'];
}

int DataWorker::getFrequenceByPos(char letter, int pos)
{
    return positionScores[pos][letter - 'a'];
}

int DataWorker::getLetterScore(char letter, int pos)
{
    return letterScore[pos][letter - 'a'];
}

void DataWorker::updateValidWords(std::vector<std::string> answers)
{
    this->answers = answers;
    this->prelucrateData();
}

std::vector<std::string> DataWorker::getAnswers()
{
    return allAnswers;
}

void DataWorker::readData()
{
    std::ifstream fin("configs/answers.txt");
    std::string word;

    while (fin >> word)
        answers.push_back(word);
    allAnswers = answers;

    fin.close();
}

void DataWorker::prelucrateData()
{
    memset(totalAppereances, false, sizeof(totalAppereances));
    memset(letterScore, false, sizeof(letterScore));
    memset(positionScores, false, sizeof(positionScores));
    for (auto word : answers)
    {
        int freq[27] = {0};

        for (int index = 0; index < word.size(); ++index)
        {
            int asciiCode = word[index] - 'a';
            positionScores[index][asciiCode]++;
            freq[asciiCode]++;
        }
        for (int letter = 0; letter < 26; ++letter)
            totalAppereances[letter] += freq[letter];
    }
    this->calculateInflunce();
}

void DataWorker::calculateInflunce()
{
    std::vector<std::pair<int, char>> scoreBoard;
    for (int pos = 0; pos < 6; ++pos)
    {
        for (int letter = 0; letter < 26; ++letter)
            scoreBoard.push_back({positionScores[pos][letter], (char)(letter + 'a')});
        std::sort(scoreBoard.begin(), scoreBoard.end());

        for (int index = 0; index < scoreBoard.size(); ++index)
            letterScore[pos][scoreBoard[index].second - 'a'] = index + 1;
        scoreBoard.clear();
    }
}