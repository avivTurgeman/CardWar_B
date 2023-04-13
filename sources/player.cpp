#include "player.hpp"

using namespace std;

namespace ariel{
        
    //Getters
    string Player::getName() const{
        return this->name_;
    }

    int Player::cardesTaken() const{
        return this->winning_cards_amount;
    }

    int Player::stacksize() const{
        return this->pile_.size();
    }

    bool Player::isPlaying() const{
        return this->playing_;
    }

    int Player::getTotalWins() const{
        return this->total_wins_;
    }

    //Setters
    void Player::add1ToTotalWins(){
        this->total_wins_ += 1;
    }

    void Player::setPlaying(bool isPlaying){
        this->playing_ = isPlaying;
    }

    void Player::setCardsTaken(int num){
        this->winning_cards_amount += num;
    }


    void Player::drawACard(Card& card){
        this->pile_.push_back(card);
    }

    Card Player::layDownACard(){
        Card card =  this->pile_.back();
        this->pile_.pop_back();
        return card;
    }

    bool Player::operator==(const Player& other) const{
        if(this->name_ == other.getName()){
            return true;;
        }
        return false;
    }

    Player::Player(string name) : name_(name){
        this->total_wins_ = 0;
        this->playing_ = false;
        this->pile_ = {};
        this->winning_cards_amount = 0;
    }

    Player::Player() : name_("default_player"){
        this->total_wins_ = 0;
        this->playing_ = false;
        this->pile_ = {};
        this->winning_cards_amount = 0;
    }
}