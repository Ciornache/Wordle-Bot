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

void DataWorker::readData()
{
    std::ifstream fin ("answers.txt");
    std::string word;

    while(fin >> word)
        answers.push_back(word);

    fin.close();
}

void DataWorker::prelucrateData()
{
    memset(totalAppereances, false, sizeof(totalAppereances));
    memset(letterScore, false, sizeof(letterScore));
    memset(positionScores, false, sizeof(positionScores));
    for(auto word : answers)
    {
        bool freq[27] = {0};

        for(int index = 0;index < word.size(); ++index)
        {
            int asciiCode = word[index] - 'a';
            positionScores[index][asciiCode]++;
            freq[asciiCode] = 1;
        }
        for(int letter = 0; letter < 26; ++letter)
            totalAppereances[letter] += freq[letter];
        
    }
    // for(int letter = 0; letter < 26; ++letter)
    //     std::cout << totalAppereances[letter] << ' ';
    // std::cout << '\n';
    this->calculateInflunce();

}

void DataWorker::calculateInflunce()
{
    std::vector<std::pair<int,char>> scoreBoard;
    for(int letter = 0;letter < 26; ++letter)
        scoreBoard.push_back({totalAppereances[letter], (char)(letter + 'a')});
    std::sort(scoreBoard.begin(), scoreBoard.end());

    for(int index = 0;index < scoreBoard.size(); ++index)
        letterScore[scoreBoard[index].second - 'a'] = index + 1;
}

int DataWorker::getFrequence(char letter)
{
    return totalAppereances[letter - 'a'];
}

int DataWorker::getFrequenceByPos(char letter, int pos)
{
    return positionScores[pos][letter - 'a'];
}

int DataWorker::getLetterScore(char letter)
{
    return letterScore[letter - 'a'];
}

void DataWorker::updateValidWords(std::vector<std::string> answers)
{
    this->answers = answers;
    this->prelucrateData();
}