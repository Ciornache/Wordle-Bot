#include "dataworker.h"

DataWorker::DataWorker()
{
    this->init();
}

void DataWorker::init()
{
    std::ofstream fout ("statistics/letterRanking.txt");
    this->readData();
    this->prelucrateData(fout);
}

int DataWorker::getTotalWords()
{
    return answers.size();
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

std::vector<std::string> DataWorker::getAnswers()
{
    return allAnswers;
}

std::vector<std::string> DataWorker::getAllAnswers()
{
    std::ifstream fin("configs/validWords.txt");
    std::string word;
    std::vector<std::string> ans;

    while(fin >> word)
        ans.push_back(word);
    fin.close();

    return ans;
}

void DataWorker::updateValidWords(std::vector<std::string> answers)
{
    std::ofstream tout ("random.txt");
    this->answers = answers;
    this->prelucrateData(tout);
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

void DataWorker::prelucrateData(std::ofstream & fout)
{
    this->reset();
    for (auto word : answers)
    {
        int freq[LETTERS + 1] = {0};

        for (int index = 0; index < word.size(); ++index)
        {
            int asciiCode = word[index] - 'a';
            positionScores[index][asciiCode]++;
            freq[asciiCode]++;
        }
        for (int letter = 0; letter < LETTERS - 1; ++letter)
            totalAppereances[letter] += freq[letter];
    }
    this->calculateInflunce(fout);
}

void DataWorker::calculateInflunce(std::ofstream & fout)
{
    std::vector<std::pair<int, char>> scoreBoard;
    for (int pos = 0; pos < POSITIONS - 1; ++pos)
    {
        for (int letter = 0; letter < LETTERS - 1; ++letter)
            scoreBoard.push_back({positionScores[pos][letter], (char)(letter + 'a')});

        std::sort(scoreBoard.begin(), scoreBoard.end());
        this->printPositionRanking(scoreBoard, pos, fout);

        for (int index = 0; index < scoreBoard.size(); ++index)
            letterScore[pos][scoreBoard[index].second - 'a'] = index + 1;
        scoreBoard.clear();
    }
    this->printAppearancesRanking(fout);
}

void DataWorker::printPositionRanking(std::vector<std::pair<int, char>> scoreBoard, int position, std::ofstream &fout)
{
    fout << "Ranking for frequency on position " << position + 1 << "\n\n";
    for(int index = 0;index < scoreBoard.size(); ++index)
        fout << 26 - index << ". " << scoreBoard[index].second << ' ' << scoreBoard[index].first << '\n';
    fout << '\n';
}

void DataWorker::printAppearancesRanking(std::ofstream &fout)
{
    fout << "Ranking for frequency overall in words\n\n";
    std::vector<std::pair<int, char>> scoreBoard;

    for (int letter = 0; letter < LETTERS - 1; ++letter)
            scoreBoard.push_back({totalAppereances[letter], (char)(letter + 'a')});

    std::sort(scoreBoard.begin(), scoreBoard.end());

    for(int index = 0;index < scoreBoard.size(); ++index)
        fout << 26 - index << ". " << scoreBoard[index].second << ' ' << scoreBoard[index].first << '\n';
    fout << '\n';

}

void DataWorker::reset()
{
    memset(totalAppereances, false, sizeof(totalAppereances));
    memset(letterScore, false, sizeof(letterScore));
    memset(positionScores, false, sizeof(positionScores));
}
