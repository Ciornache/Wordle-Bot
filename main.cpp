#include "bot.h"
#include "configs/config.h"

using namespace std;

std::vector<std::string> answers;

ifstream fin("configs/answers.txt");
ofstream fout("configs/history.txt");

int main()
{
    std::map<int, int> usedIndex;
    std::string word;

    while (fin >> word)
        answers.push_back(word);
    fin.close();

    double guessRate = 0, attemptsRate = 0;
    int totalScore = 0, wordsGuessed = 0;

    for (int word = 1; word <= NUMBER_OF_WORDS ; ++word)
    {
        Bot wordleBot;
        wordleBot.setGuesses(answers);

        int wordIndex = rand(0, answers.size() - 1);
        while(usedIndex[wordIndex])
            wordIndex = rand(0, answers.size() - 1);
        usedIndex[wordIndex] = 1;

        wordleBot.setRefereeAnswer(answers[wordIndex]);

        fout << "The Wordle Bot must guess the word " << answers[wordIndex] << '\n';

        bool ok = 0;
        for (int trial = 1; trial <= NUMBER_OF_ATTEMPTS; ++trial)
        {
            bool validGuess = wordleBot.takeAGuess(trial, fout);
            if (validGuess)
            {
                if(trial <= 6)
                    wordsGuessed++;
                totalScore += trial;
                ok = 1;

                fout << "\nWordle Bot guessed the word in " << trial << ' ' << "attempts!\n";
                break;
            }
            else
                fout << "-> ";
        }

        if(!ok)
            fout << "\nWordle Bot didn't manage to guess the word in 10 attempts\n";
        fout << '\n';

    }
    attemptsRate = (double)(totalScore) / (double)(NUMBER_OF_WORDS);
    guessRate = ((double)(wordsGuessed) / (double)(NUMBER_OF_WORDS)) * 100.0;

    std::cout << std::setprecision(5) << fixed << "Attempt rate is " << attemptsRate << '\n';
    std::cout << std::setprecision(5) << fixed << "Guess rate is " << guessRate << '\n';

}