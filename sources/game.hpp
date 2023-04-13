#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include "player.hpp"
#include "card.hpp"
using namespace std;

namespace ariel{
    class Game
    {
        private:
            Player *player1_;
            Player *player2_;
            vector<Card> pile_;
            vector<string> log_;
            int draws_;
            int  turns_;
            void shuffle();
            void deal();
            void generateGame();
            string toDocument(string, Card, string, Card, int);
           int play(string*, int*, int*);

        public:
            //Constructors
            Game(Player&, Player&);

            void playTurn();
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog();
            void printStats();
    };
}

#endif