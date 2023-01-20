#include "bot.h"


Bot::Bot()
{
    memset(validPositions, false, sizeof(validPositions));
    memset(wrongPositions, false, sizeof(wrongPositions));
    memset(bannedLetters, false, sizeof(bannedLetters));
}

void Bot::setGuesses(std::vector<std::string> guesses)
{
    this->guesses = guesses;
}

bool Bot::takeAGuess()
{

    double bestScore = 0;
    std::string bestGuess; 

    for(int index = 0;index < guesses.size(); ++index)
    {
        double wordScore = referee.getWordScore(guesses[index]);
        if(wordScore > bestScore)
            bestScore = wordScore, bestGuess = guesses[index];
    }

    // std::cout << bestGuess << ' ' << bestScore << ' ' << referee.answer << '\n';

    Referee::result rez = referee.evaluateWord(bestGuess);

    this->updateRestrinctions(rez);
    this->eliminateWords();

    return rez.verdict;
   
}

void Bot::updateRestrinctions(Referee::result rez)
{
    for(int index = 0;index < rez.goodLetters.size(); ++index)
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

    for(int index = 0; index < rez.wrongLetters.size(); ++index)
    {
        char letter = rez.wrongLetters[index];
        bannedLetters[letter - 'a'] = 1;
    }

}

void Bot::eliminateWords()
{
    std::vector<std::string> newGuesses;
    
    for(auto word : guesses)
    {
        bool isValid = true;
        int pos = 0;
        for(auto letter : word)
        {
            for(int j = 0;j < 26; ++j){
                if(validPositions[pos][j] && (char)(j + 'a') != letter)
                    isValid = false;
            }
            isValid &= (!wrongPositions[pos][letter - 'a']);
            isValid &= (!bannedLetters[letter - 'a']);
            pos++;
        }   

        if(isValid)
            newGuesses.push_back(word);

    }
    guesses = newGuesses;

    referee.dataWorker.updateValidWords(guesses);
}

void Bot::setRefereeAnswer(std::string answer)
{
    referee.answer = answer;
}