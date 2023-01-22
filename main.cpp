#include "bot.h"
#include "configs/config.h"
#include "timer.h"
#include "table.h"
#include <windows.h>

using namespace std;

std::vector<std::string> answers;

Table table;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b)
{
    int ans = std::uniform_int_distribution<int>(a, b)(rng);
    return ans;
}

ifstream fin("configs/answers.txt");
ofstream fout("configs/history.txt");
ofstream lout("configs/failedWords.txt");

string chosenWord;

void sleep(int s)
{
    Sleep(s * 1000);
}

int main()
{

    Timer timer(fout, "Wordle");

    std::map<int, int> usedIndex;
    std::string word;

    while (fin >> word)
        answers.push_back(word);
    fin.close();

    table.init();
    double guessRate = 0, attemptsRate = 0;
    int totalScore = 0, wordsGuessed = 0;

    for (int word = 1; word <= NUMBER_OF_WORDS; ++word)
    {
        table.refresh();
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
            bool validGuess = wordleBot.takeAGuess(trial, fout, chosenWord);
            if(trial <= 6)
                table.place(trial, chosenWord);

            if(validGuess)
            {
                if(trial <= 6)
                    wordsGuessed++;
                else
                    lout << answers[wordIndex] << '\n';

                totalScore += trial;
                ok = 1;
                sleep(1);
                fout << "\nWordle Bot guessed the word in " << trial << ' ' << "attempts!\n";
                break;
            }
            else
                fout << "-> ";
            sleep(1);
        }

        if(!ok)
            fout << "\nWordle Bot didn't manage to guess the word in 10 attempts\n";
        fout << '\n';
    }

    attemptsRate = (double)(totalScore) / (double)(NUMBER_OF_WORDS);
    guessRate = ((double)(wordsGuessed) / (double)(NUMBER_OF_WORDS)) * 100.0;

    std::cout << std::setprecision(5) << fixed << "Attempt rate is " << attemptsRate << '\n';
    std::cout << std::setprecision(5) << fixed << "Guess rate is " << guessRate << '\n';

    getch();
    closegraph();
    fout.close(), lout.close();

    return 0;
}
