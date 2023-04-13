#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string.h>
#include<vector>
#include "card.hpp"
using namespace std;

namespace ariel{
    class Player
    {
        private:
            const string name_;
            int total_wins_;
            bool playing_;
            int winning_cards_amount;
            vector<Card> pile_;


        public:
            //Constructors:
            Player(string);
            Player();

            //Getters
            string getName() const;
            int stacksize() const;
            int cardesTaken() const;
            bool isPlaying() const;
            int getTotalWins() const;
            
            //Setters
            void add1ToTotalWins();
            void setPlaying(bool);
            void setCardsTaken(int);

            void drawACard(Card&);
            Card layDownACard();
            bool operator==(const Player& other) const;
    };
}

#endif