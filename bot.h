#ifndef H_BOT
#define H_BOT

#include "referee.h"

class Bot
{
    public:
        Bot();
        bool takeAGuess(); 
        void setGuesses(std::vector<std::string> guesses);
        void setRefereeAnswer(std::string answer);
        Referee referee;
        
    private:
        bool validPositions[6][27], wrongPositions[6][27];
        bool bannedLetters[27];
        std::vector<std::string> guesses;

        void eliminateWords();
        void updateRestrinctions(Referee::result rez);
        
       
       
};






#endif ///H_BOT