#ifndef H_BOT
#define H_BOT

#include "referee.h"

class Bot
{
    public:
        Bot();
        bool takeAGuess(int trial, std::ofstream & fout, std::string & chosenWord);
        void setGuesses(std::vector<std::string> guesses);
        void setRefereeAnswer(std::string answer);
        Referee referee;

    private:
        bool validPositions[POSITIONS][LETTERS], wrongPositions[POSITIONS][LETTERS];
        bool bannedLetters[LETTERS], usedLetters[LETTERS];
        std::vector<std::string> guesses;

        void eliminateWords();
        void updateRestrinctions(Referee::result rez);
        void reset();

        int maximumDistinctLetters(std::vector<std::string> answers);
        int guessedLetters();
        std::string findEmergencyWord();

};



#endif ///H_BOT
