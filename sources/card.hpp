#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <string>
using namespace std;

namespace ariel{
    class Card
    {
        private:
            int num_;
            string type_;
            
        public:
            //Constructors
            Card(int num, const string& type);
            Card();
            
            bool operator==(const Card&) const;
            bool operator>(const Card&) const;
            string toString();
    };
    
} 

#endif