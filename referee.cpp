#include "referee.h"

Referee::Referee() {};

double Referee::getWordScore(std::string word)
{
    double score = 0;
    int vowels = 1;
    bool freq[LETTERS + 1] = {0};

    double percentage[LETTERS + 1] = {0};
    for(int i = 0; i < LETTERS - 1; ++i)
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
    for(int index = stats.size() - 1; index >= 0; --index)
        fout << stats[index].second << ' ' << stats[index].first << '\n';

}

double Referee::findEntropy(std::string word)
{
    int pattern[6];
    memset(pattern, false, sizeof(pattern));
    double entropy = 0;

    for(int l1 = 0; l1 < 3; ++l1)
    {
        pattern[0] = l1;
        for(int l2 = 0; l2 < 3; ++l2)
        {
            pattern[1] = l2;
            for(int l3 = 0; l3 < 3; ++l3)
            {
                pattern[2] = l3;
                for(int l4 = 0; l4 < 3; ++l4)
                {
                    pattern[3] = l4;
                    for(int l5 = 0; l5 < 3; ++l5)
                    {
                        pattern[4] = l5;
                        entropy += evaluatePattern(pattern, word);
                    }
                }
            }
        }
    }
    entropy /= 243.0;
    return entropy;
}

double Referee::evaluatePattern(int pattern[], std::string word)
{
    result resultList;

    std::map<char, bool> mp;

    for(int let = 0; let < 5; ++let)
    {
        if(pattern[let] == 0)
            resultList.wrongLetters.push_back(word[let]);
        else if(pattern[let] == 1)
            resultList.badLetters.push_back({let, word[let]});
        else
            resultList.goodLetters.push_back({let, word[let]});
    }

    std::vector<std::string> answers = dataWorker.getAnswers();

    int total = answers.size(), good = 0;

    for(auto name : answers)
        good += judgeByResult(resultList, name);

    if(good == 0)
        return 1;

    return -log2((double)(good) / (double)(total));
}

bool Referee::judgeByResult(result rez, std::string word)
{
    int pos = 0;
    for(auto let : word)
    {
        for(int index = 0; index < rez.goodLetters.size(); ++index)
        {
            if(rez.goodLetters[index].first == pos && rez.goodLetters[index].second != let)
                return false;
        }

        for(int index = 0; index < rez.badLetters.size(); ++index)
        {
            if(rez.badLetters[index].first == pos && rez.badLetters[index].second == let)
                return false;
        }

        for(int index = 0; index < rez.wrongLetters.size(); ++index)
        {
            if(rez.wrongLetters[index] == let)
                return false;
        }
        pos++;
    }
    return true;
}
