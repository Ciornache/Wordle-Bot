#include "bot.h"
#include <chrono>
#include <random>
#include <ctime>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b)
{
    int ans = uniform_int_distribution<int>(a, b)(rng);
    return ans;
}

std::vector<std::string> answers;

ifstream fin("answers.txt");

int main()
{
    

    std::string word;
    while (fin >> word)
        answers.push_back(word);

    double guessRate = 0;
    int totalScore = 0, tries = 3000;
   
    for (int word = 1; word <= tries; ++word)
    {
        Bot wordleBot;
        wordleBot.setGuesses(answers);
        int wordIndex = rand(0, answers.size() - 1);
        wordleBot.setRefereeAnswer(answers[wordIndex]);

        bool ok = 0;
        for (int trial = 1; trial <= 10; ++trial)
        {
            bool validGuess = wordleBot.takeAGuess();
            if (validGuess)
            {
                totalScore += trial;
                ok = 1;
                // std::cout << "Wordle Bot guessed the word in " << trial << ' ' << "attempts!\n";
                break;
            }
        }
        // if (!ok)
        //     std::cout << "Wordle Bot didn't manage to guess the word in 10 attempts\n";
    }
    guessRate = (double)(totalScore) / (double)(tries);
    std::cout << "Guess rate is " << guessRate << '\n';

}