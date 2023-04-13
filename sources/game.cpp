#include<algorithm>
#include<ctime>
#include <random>
#include "game.hpp"

using namespace std;

namespace ariel{

    void Game::shuffle(){
        random_device rd;
        mt19937 g(rd());
        std::shuffle(this->pile_.begin(), this->pile_.end(), g);
    }

    void Game::deal(){
        for(uint i = 0; i < this->pile_.size(); i++){
            this->player1_->drawACard(this->pile_.at(i++));
            this->player2_->drawACard(this->pile_.at(i));
        }
        this->pile_.clear();
        this->pile_.shrink_to_fit();
    }

    void Game::generateGame(){
        int num[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
        string type[4] = {"Clabs", "Hearts", "Diamonds", "Spades"};
        
        for(int i = 0; i < 13; i++){
            for(int j = 0; j < 4; j++){
                this->pile_.push_back(Card(num[i], type[j]));
            }
        }
        this->player1_->setPlaying(true);
        this->player2_->setPlaying(true);
        shuffle();
        deal();
    }

    string Game::toDocument(string name1, Card card1, string name2, Card card2, int flag){
        if(flag == 0){
            return name1 + " played " + card1.toString() + " " + name2 + " played " + card2.toString() +  ".Draw. ";
        }

        if(flag == 1){
            return name1 + " played " + card1.toString() + " " + name2 + " played " + card2.toString() + ". " + name1 + " wins.";
        }

        return name1 + " played " + card1.toString() + " " + name2 + " played " + card2.toString() + ". " + name2 + " wins.";
    }

    int Game::play(string* turn_document, int* cards_won, int* turn_winner){
        if(this->player1_->stacksize() == 0 || this->player2_->stacksize() == 0){
            this->player1_->setPlaying(false);
            this->player2_->setPlaying(false);
            return 0;
        }

        Card p1_card = this->player1_->layDownACard();
        Card p2_card = this->player2_->layDownACard();
        string p1_name = this->player1_->getName();
        string p2_name = this->player2_->getName();
        *(cards_won) += 2;

        if(p1_card == p2_card){
            *(turn_document) += toDocument(p1_name,p1_card,p2_name,p2_card, 0);
            this->draws_++;

            if(this->player1_->stacksize() != 0 && this->player2_->stacksize() != 0){
                this->player1_->layDownACard();
                this->player2_->layDownACard();
                *(cards_won) += 2;
            }
            return 1;
        }

        if(p1_card > p2_card){
            *(turn_document) += toDocument(p1_name,p1_card,p2_name,p2_card, 1);
            this->player1_->setCardsTaken(*cards_won);
            this->player1_->add1ToTotalWins();
            *(turn_winner) = 1;
            return 0;
        }

        if(p2_card > p1_card){
            *(turn_document) += toDocument(p1_name,p1_card,p2_name,p2_card, 2);
            this->player2_->setCardsTaken(*cards_won);
            this->player2_->add1ToTotalWins();
            *(turn_winner) = 2;
            return 0;
        }
        return 1;
    }

    Game::Game(Player& pl1, Player& pl2){
        if(pl1.isPlaying()){
            throw new invalid_argument("player 1 is in a middle of a game!!");
        }

        if(pl2.isPlaying()){
            throw new invalid_argument("player 2 is in a middle of a game!!");
        }

        this->player1_ = &pl1;
        this->player2_ = &pl2;
        this->pile_ = {};
        this->log_ = {};
        this->draws_ = 0;
        this->turns_ = 0;
        this->generateGame();
    }

    void Game::playTurn(){
        if(this->player1_ == this->player2_){
            throw new invalid_argument("A player must not play against himself");
        }

        int turn_winner = 0;
        string turn_document = "";
        int cards_won = 0;

        if(this->turns_ >=26){
            throw new invalid_argument("Game ended");
        }

        int x = 1;
        while(x){
            this->turns_++;
            x = play(&turn_document, &cards_won, &turn_winner);
        }


        this->log_.push_back(turn_document);

        if(!turn_winner){
            this->player1_->setCardsTaken(cards_won / 2);
            this->player2_->setCardsTaken(cards_won / 2);
        }
    }

    void Game::printLastTurn(){
        if(this->log_.size() == 0){
            throw new logic_error("No plays have made!");
        }
        cout << this->log_.back() << endl;
    }

    void Game::playAll(){
        while(this->player1_->isPlaying() || this->player2_->isPlaying()){
            if(this->turns_ < 26){
                this->playTurn();
            }
            else{
                break;
            }
        }

        if(this->turns_ != 26){
            this->turns_ = 26;
        }
    }

    void Game::printWiner(){
        if(this->player1_->getTotalWins() > this->player2_->getTotalWins()){
            cout << this->player1_->getName() << " won the game!" <<endl;
            return;
        }

        if(this->player1_->getTotalWins() < this->player2_->getTotalWins()){
            cout << this->player2_->getName() << " won the game!" <<endl;
            return;
        }

        cout << "Game ended with a Draw!\n";
    }

    void Game::printLog(){
        if(this->log_.size() == 0){
            throw new logic_error("No plays have made!");
        }

        for(uint i = 0; i < this->log_.size(); i++){
            cout << this->log_.at(i) << endl;
        }
    }

    void Game::printStats(){
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;
        cout << "PLAYER NAME: " << this->player1_->getName() << endl;
        cout << "CARDS WON: " << this->player1_->cardesTaken() << endl;
        cout << "CARDS LEFT IN PILE: " << this->player1_->stacksize() << endl;
        cout << "TOTAL WINS: " << this->player1_->getTotalWins() << endl;
        cout << "TURNS: " << this->turns_ << endl;
        cout << "WIN RATE: " <<  float(this->player1_->getTotalWins()) / float(this->turns_) << "%" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "PLAYER NAME: " << this->player2_->getName() << endl;
        cout << "CARDS WON: " << this->player2_->cardesTaken() << endl;
        cout << "CARDS LEFT IN PILE: " << this->player2_->stacksize() << endl;
        cout << "TOTAL WINS: " << this->player2_->getTotalWins() << endl;
        cout << "TURNS: " << this->turns_ << endl;
        cout << "WIN RATE: " << float(this->player2_->getTotalWins()) / float(this->turns_) << "%" << endl;

        cout << "-----------------------------------------------------------------------------------------------------------" << endl;

        cout << "TOTAL TURNS PLAYED: " << this->turns_ << endl;
        cout << "TOTAL DRAWS MADE: " << this->draws_ << endl;
        cout << "DRAWS RATE: " << float(this->draws_) / float(this->turns_) << "%" << endl << endl;
    }
}