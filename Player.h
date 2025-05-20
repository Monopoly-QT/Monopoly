#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <QObject>

using namespace std;

class Player: public QObject {
    Q_OBJECT
private:
    int money;
    int playerID;
    string playerName;
    vector<int> ownHousesPos;
    vector<string> ownCard;
    int pos;
    int state; //0:not in hospital 1:in hospital
    int stayInHospitalTurn;
    int nextRollDicePoint;
public:
    Player(); //initialize
    Player(int _playerID);
    void addMoney(int _addition);
    void subMoney(int _subtraction);
    void addPos(int _deltaPos);
    void addOwnImmovables(int _pos);
    void addOwnCards(string _addCard);
    void disOwnCards(string _disCards);

    void setMoney(int _money);
    void setPos(int _pos);
    void setPlayerName(string _playerName);
    void setState(int _state);
    void setStayInHospitalTurn(int _turn);

    int getID();
    int getMoney();
    int getPos();
    string getPlayerName();

    vector<int> getOwnImmovables();
    vector<string> getOwnCards();
    int getState();
    int GetstayInHospitalTurn();

    int getNextRollDicePoint() const;
    void setNextRollDicePoint(int _nextRollDicePoint);

    void removeOwnImmovables(int _pos);

    bool operator<(const Player rhs) const;
};


#endif // PLAYER_H

