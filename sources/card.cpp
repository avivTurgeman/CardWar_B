#include "card.hpp"
#include <random>

using namespace std;

namespace ariel{

    bool Card::operator==(const Card& other) const{
        return (this->num_ == other.num_ );
    }

    bool Card::operator>(const Card& other) const{
        if(this->num_ == 1){
            if(other.num_ == 1 || other.num_ == 2){
                return false;
            }
            return true;
        }

        if(this->num_ == 2){
            return this->num_ > other.num_;
        }

        if(other.num_ != 1){
            return this->num_ > other.num_;
        }

        return false;
    }

    string Card::toString(){
        switch (this->num_){
        case 2: case 3: case 4: case 5: case 6 :
        case 7: case 8: case 9: case 10:
            return to_string(this->num_) + " of " + this->type_;
        
        case 11:
            return "Jack of " + this->type_;

        case 12:
            return "Queen of " + this->type_;
        
        case 13:
            return "King of " + this->type_;
        
        case 1:
            return "Ace of " + this->type_;
        }

        return "";
    }

    Card::Card(int num, const string& type) : 
    num_(num), type_(type){}

    Card::Card() : num_(7), type_("Hearts"){}
}