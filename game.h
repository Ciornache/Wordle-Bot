#ifndef H_GAME
#define H_GAME

#include "game.h"
#include "table.h"
#include "timer.h"
#include "bot.h"

#include <windows.h>
#include <future>
#include <bits/stdc++.h>
#include <thread>

class Game
{
public:
    Game();
    void start();

private:

    void sleep(double s);
    void addLetter(char currentWord[PATH_SIZE], char a);
    void findWord(std::string word);
    void runAll();

    bool checkWord(std::string word);
};




#endif // H_GAME
