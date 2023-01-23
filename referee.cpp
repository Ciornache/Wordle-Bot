#include "referee.h"

Referee::Referee(){};

double Referee::getWordScore(std::string word)
{
    double score = 0;
    int vowels = 1;
    bool freq[LETTERS + 1] = {0};

    double percentage[LETTERS + 1] = {0};
    for(int i = 0;i < LETTERS - 1; ++i)
        percentage[i] = 1;

    for (int let = 0; let < word.size(); ++let)
    {
        int total = dataWorker.getTotalWords();
        int positionFreq = dataWorker.getFrequenceByPos(word[let], let);
        int letterScore = dataWorker.getLetterScore(word[let], let);

        double positionScore = (double)(letterScore) * ((double)(positionFreq) / (double)(total)) * percentage[word[let] - 'a'];
        if(!strchr("aeiouy", word[let]) && let == 0)
            positionScore *= 1.5;

        score += positionScore;

        if (strchr("aieoy", word[let]) && !freq[word[let] - 'a'])
        {
            vowels++;
            freq[word[let] - 'a'] = 1;
        }

        percentage[word[let] - 'a'] -= 0.2;
    }

    score *= vowels;

    return score;
}

Referee::result Referee::evaluateWord(std::string word)
{
    result rez;
    int matchedLetters = 0;

    for (int let = 0; let < word.size(); ++let)
    {
        if (word[let] == answer[let])
        {
            matchedLetters++;
            rez.goodLetters.push_back({let, word[let]});
        }
        else
        {
            bool isBack = false;
            bool presentInWord = false;
            for (int j = 0; j < word.size(); ++j)
                presentInWord |= (answer[j] == word[let]);

            if (presentInWord)
                rez.badLetters.push_back({let, word[let]});
            else
                rez.wrongLetters.push_back(word[let]);
        }
    }

    if (matchedLetters == 5)
        rez.verdict = true;
    else
        rez.verdict = false;

    return rez;
}

void Referee::printStats()
{
    std::ofstream fout ("statistics/wordsRanking.txt");

    std::vector<std::string> answers = dataWorker.getAnswers();
    stats.clear();

    for(auto word : answers)
    {
        double score = this->getWordScore(word);
        stats.push_back({score, word});
    }
    sort(stats.begin(), stats.end());
    for(int index = stats.size() - 1;index >= 0; --index)
        fout << stats[index].second << ' ' << stats[index].first << '\n';

}
