#include "referee.h"

Referee::Referee(){};

double Referee::getWordScore(std::string word)
{
    double score = 0;
    int vowels = 1;
    bool freq[27] = {0};

    double percentage[27] = {0};
    for(int i = 0;i < 26; ++i)
        percentage[i] = 1;

    for (int let = 0; let < word.size(); ++let)
    {
        int total = dataWorker.getFrequence(word[let]);
        int positionFreq = dataWorker.getFrequenceByPos(word[let], let);
        int letterScore = dataWorker.getLetterScore(word[let], let);

        double positionScore = (double)(letterScore) * ((double)(positionFreq) / (double)(total)) * percentage[word[let] - 'a'];
        score += positionScore;

        if (strchr("aioy", word[let]) && !freq[word[let] - 'a'])
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
