//
//  main.cpp
//  Smart_Ptr_Lab
//

#include <iostream>
#include "Class_FootballRoaster.h"


void FootBallRoster::addPlayer(FootBallPlayer player){
    std::shared_ptr<Node> newNode(new Node());
     newNode->value = player;
    newNode->next = std::move(head);
    head = std::move(newNode);
}



bool FootBallRoster::deletePlayer(string name){
    if (head == nullptr)
        return false;
    if (head->value.name == name) {
        if (favorite.lock() == head){
            head = head->next;
        }
        return true;
    }
    std::shared_ptr<Node> prev = head;
    std::shared_ptr<Node> current = head->next;
    
    while (current != nullptr) {
        if (current->value.name == name) {
            if (favorite.lock() == current){
                favorite.reset();
            }
            prev->next = current->next;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}



bool FootBallRoster::setFavorite(string name){
    std::shared_ptr<Node> current = head;
    while(current != nullptr){
        if(current->value.name == name){
            favorite = current;
            return true;
        }
       current = current->next;
    }
    return false;
}



std::optional<FootBallPlayer> FootBallRoster::getFavorite() const{
    std::shared_ptr<Node> favPtr = favorite.lock();
    if(!favPtr) {
        return std::nullopt;
    }
    return favPtr->value;
}


void FootBallRoster::printPlayers() const{
    std::shared_ptr<Node> current = head;
    while (current) {
        cout << current->value.name << " #" << current->value.num <<endl;
        current = current->next;
    }
}




void favoritePlayer(const FootBallRoster& roster){
    std::optional<FootBallPlayer> fav = roster.getFavorite();
    if(fav) {
        cout << "Your Favorite Player is: " << fav->name << endl;
    }
    else {
        cout << "You dont have a favorite player" << endl;
    }
}


int main() {
  
    FootBallPlayer fb1{ "Matthew Stafford", 9 };
    FootBallPlayer fb2{ "Aaron Donald", 99 };
    FootBallPlayer fb3{ "Jalen Ramsey", 5 };

    FootBallRoster roster;

    roster.addPlayer(fb1);
    roster.addPlayer(fb2);
    roster.addPlayer(fb3);

    roster.printPlayers();
    roster.setFavorite("Aaron Donald");

    favoritePlayer(roster);

    roster.deletePlayer("Aaron Donald");
    favoritePlayer(roster);
}
