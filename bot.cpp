#include "bot.h"

Bot::Bot()
{
    this->reset();
}

void Bot::setGuesses(std::vector<std::string> guesses)
{
    this->guesses = guesses;
}

bool Bot::takeAGuess(int trial, std::ofstream &fout)
{
    double bestScore = 0;
    std::string bestGuess;

    for (int index = 0; index < guesses.size(); ++index)
    {
        double wordScore = referee.getWordScore(guesses[index]);
        if (wordScore > bestScore)
            bestScore = wordScore, bestGuess = guesses[index];
    }

    // std::cout << bestGuess << ' ' << bestScore << ' ' << referee.answer << '\n';

    int remainingLetters = 5 - this->guessedLetters();
  
    if(trial >= 1 && trial <= 3)
        bestGuess = this->findEmergencyWord();
    
    // std::cout << remainingLetters << ' ' << trial << ' ' << bestGuess << '\n';

    for (auto ch : bestGuess)
        usedLetters[ch - 'a'] = 1;

    Referee::result rez = referee.evaluateWord(bestGuess);
    fout << bestGuess << ' ';

    this->updateRestrinctions(rez);
    this->eliminateWords();

    return rez.verdict;
}

void Bot::updateRestrinctions(Referee::result rez)
{
    for (int index = 0; index < rez.goodLetters.size(); ++index)
    {
        char letter = rez.goodLetters[index].second;
        int position = rez.goodLetters[index].first;
        validPositions[position][letter - 'a'] = 1;
    }

    for (int index = 0; index < rez.badLetters.size(); ++index)
    {
        char letter = rez.badLetters[index].second;
        int position = rez.badLetters[index].first;
        wrongPositions[position][letter - 'a'] = 1;
    }

    for (int index = 0; index < rez.wrongLetters.size(); ++index)
    {
        char letter = rez.wrongLetters[index];
        bannedLetters[letter - 'a'] = 1;
    }
}

void Bot::eliminateWords()
{
    std::vector<std::string> newGuesses;

    for (auto word : guesses)
    {
        bool isValid = true;
        int pos = 0;
        for (auto letter : word)
        {
            for (int j = 0; j < 26; ++j)
            {
                if (validPositions[pos][j] && (char)(j + 'a') != letter)
                    isValid = false;
            }
            isValid &= (!wrongPositions[pos][letter - 'a']);
            isValid &= (!bannedLetters[letter - 'a']);
            pos++;
        }

        if (isValid)
            newGuesses.push_back(word);
    }
    guesses = newGuesses;

    referee.dataWorker.updateValidWords(guesses);
}

void Bot::setRefereeAnswer(std::string answer)
{
    referee.answer = answer;
}

int Bot::guessedLetters()
{
    int count = 0;
    for (int pos = 0; pos < 6; ++pos)
    {
        for (int letter = 0; letter < 26; ++letter)
            count += validPositions[pos][letter];
    }

    return count;
}

std::string Bot::findEmergencyWord()
{
    std::vector<std::string> answers = referee.dataWorker.getAnswers();
    referee.dataWorker.updateValidWords(answers);

    int distLetters = 0;
    
    for (auto word : answers)
    {
        int count = 0;
        for (auto ch : word)
            if (!usedLetters[ch - 'a'])
                count++;

        if (count > distLetters)
            distLetters = count;
    }

    std::string bestGuess;
    double bestScore = 0;

    for (auto word : answers)
    {
        int count = 0;
        bool freq[27] = {0};
        for (auto ch : word)
            if (!usedLetters[ch - 'a'] && !freq[ch - 'a'])
                count++, freq[ch - 'a'] = 1;
        
        if (count == distLetters)
        {
            double wordScore = referee.getWordScore(word);
            // std::cout << word << ' ' << wordScore << '\n';
            if (wordScore > bestScore)
            {
                bestScore = wordScore;
                bestGuess = word;
            }
        }
    }
    
    return bestGuess;
}

void Bot::reset()
{
    memset(validPositions, false, sizeof(validPositions));
    memset(wrongPositions, false, sizeof(wrongPositions));
    memset(bannedLetters, false, sizeof(bannedLetters));
    memset(usedLetters, false, sizeof(usedLetters));
}