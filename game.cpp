#include "game.h"


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b)
{
    int ans = std::uniform_int_distribution<int>(a, b)(rng);
    return ans;
}


Game::Game() {};

void Game::sleep(double s)
{
    Sleep(s * 1000);
}

void Game::addLetter(char source[], char a)
{
    char let[2] = {0};
    let[0] = a - 'a' + 'A', let[1] = '\0';
    strcat(source, let);
}

void Game::start()
{
    while(true)
    {
        std::cout << "Welcome to the Wordle Bot\n\n";
        std::cout << "Press 1 to run through all the words\n";
        std::cout << "Press 2 to type a valid 5 letter word and try to find it\n";

        char digit;
        std::cin >> digit;

        if(digit != '1' && digit != '2')
        {
            std::cout << "Unauthorised character\n";
            sleep(1);
            system("cls");
            continue;
        }
        else
        {
            if(digit == '1')
                runAll();
            else
            {
                std::cout << "Introduce your word\n";

                std::string word;
                std::cin >> word;
                for(int let = 0; let < word.size(); ++let)
                {
                    if(word[let] >= 'A' && word[let] <= 'Z')
                        word[let] = word[let] - 'A' + 'a';
                }

                bool ok = checkWord(word);
                if(!ok)
                {
                    std::cout << "Invalid word\n";
                    sleep(1);
                }
                else
                    findWord(word);
            }
        }
        system("cls");
    }
}

void Game::runAll()
{
    std::ifstream fin("configs/answers.txt");
    std::ofstream fout("configs/history.txt");
    std::ofstream lout("configs/failedWords.txt");

    Timer timer(fout, "Wordle");

    std::vector<std::string> answers;
    std::map<int, int> usedIndex;
    std::string word;

    Table table;

    while (fin >> word)
        answers.push_back(word);
    fin.close();

    double guessRate = 0, attemptsRate = 0;
    int totalScore = 0, wordsGuessed = 0;
    char message[] = "The Wordle Bot has to guess the word";

    std::string chosenWord;

    Bot copyBot;
    copyBot.referee.printStats();

    table.init();

    for (int word = 1; word <= NUMBER_OF_WORDS; ++word)
    {
        int wordIndex = rand(0, answers.size() - 1);
        table.refresh();
        Bot wordleBot;

        wordleBot.setGuesses(answers);
        table.message(message, TEXT_HEIGHT - 5, TEXT_WIDTH - 5, "Arial", X_TEXT + 20, Y_TEXT, TEXT_SIZE);

        char currentWord[PATH_SIZE] = {0};
        for(auto letter : answers[wordIndex])
            addLetter(currentWord, letter);

        table.message(currentWord, TEXT_HEIGHT + 5, TEXT_WIDTH, "Arial", X_TEXT + 220, Y_TEXT + 80, TEXT_SIZE + 2);

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
                sleep(0.4);
                fout << "\nWordle Bot guessed the word in " << trial << ' ' << "attempts!\n";
                break;
            }
            else
                fout << "-> ";
            sleep(0.4);
        }

        if(!ok)
            fout << "\nWordle Bot didn't manage to guess the word in 10 attempts\n";
        fout << '\n';
    }

    attemptsRate = (double)(totalScore) / (double)(NUMBER_OF_WORDS);
    guessRate = ((double)(wordsGuessed) / (double)(NUMBER_OF_WORDS)) * 100.0;

    std::cout << std::setprecision(5) << std::fixed << "Attempt rate is " << attemptsRate << '\n';
    std::cout << std::setprecision(5) << std::fixed << "Guess rate is " << guessRate << '\n';

    getch();
    closegraph();
    fout.close(), lout.close();
}


bool Game::checkWord(std::string word)
{
    DataWorker dataWorker;
    std::vector<std::string> answers = dataWorker.getAllAnswers();

    for(auto currWord : answers)
        if(currWord == word) return true;

    return false;
}

void Game::findWord(std::string word)
{
    std::ofstream fout("configs/history.txt");
    std::ifstream fin("configs/answers.txt");

    std::string chosenWord, currWord;
    std::vector<std::string> answers;

    while (fin >> currWord)
        answers.push_back(currWord);
    fin.close();

    Table table;
    table.init();

    Bot wordleBot;
    wordleBot.setRefereeAnswer(word);

    bool ok = false;

    for(auto currWord : answers)
    {
        if(currWord == word)
        {
            ok = true;
            break;
        }
    }

    if(!ok)
        answers.push_back(word);
    wordleBot.setGuesses(answers);

    for(int trial = 1; trial <= NUMBER_OF_ATTEMPTS; ++trial)
    {
        bool validGuess = wordleBot.takeAGuess(trial, fout, chosenWord);

        if(trial <= 6)
            table.place(trial, chosenWord);

        if(validGuess)
            break;

        sleep(0.4);
    }

    sleep(1.5);

    closegraph();
    fout.close();
}
