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
    Q_PROPERTY(int money READ getMoney WRITE setMoney NOTIFY moneyChanged)
    Q_PROPERTY(int playerID READ getID NOTIFY playerIDChanged)
    Q_PROPERTY(string playerName READ getPlayerName WRITE setPlayerName NOTIFY playerNameChanged)
    Q_PROPERTY(string playerLastName READ getPlayerLastName NOTIFY playerLastNameChanged)
    Q_PROPERTY(int pos READ getPos WRITE setPos NOTIFY posChanged)
    Q_PROPERTY(int state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(int stayInHospitalTurn READ GetstayInHospitalTurn WRITE setStayInHospitalTurn NOTIFY stayInHospitalTurnChanged)
    Q_PROPERTY(int nextRollDicePoint READ getNextRollDicePoint WRITE setNextRollDicePoint NOTIFY nextRollDicePointChanged)

private:
    int money;
    int playerID;
    string playerName;
    string playerLastName;
    vector<int> ownHousesPos;
    vector<int> ownCard;
    int pos;
    int state; //0:not in hospital 1:in hospital
    int stayInHospitalTurn;
    int nextRollDicePoint;

signals:
    void moneyChanged();
    void playerIDChanged();
    void playerNameChanged();
    void playerLastNameChanged();
    void posChanged();
    void stateChanged();
    void stayInHospitalTurnChanged();
    void nextRollDicePointChanged();

public:
    Player(); //initialize
    Player(int _money, int _playerID, string _playerName, string _playerLastName, vector<int> _ownCard, int _pos, int _state, int _stayInHospitalTurn,int _nextRollDicePoint);
    void addMoney(int _addition);
    void subMoney(int _subtraction);
    void addPos(int _deltaPos);
    void addOwnImmovables(int _pos);
    void addOwnCards(int _addCard);
    void disOwnCards(int _disCards);
    void addHouse(int _pos);

    void subPos(int _deltaPos);

    void setMoney(int _money);
    void setPos(int _pos);
    void setPlayerName(string _playerName);
    void setState(int _state);
    void setStayInHospitalTurn(int _turn);

    int getID();
    int getMoney();
    int getPos();
    string getPlayerName();
    string getPlayerLastName();

    vector<int> getOwnImmovables();
    vector<int> getOwnCards();
    int getState();
    int GetstayInHospitalTurn();

    int getNextRollDicePoint() const;
    void setNextRollDicePoint(int _nextRollDicePoint);

    void removeOwnImmovables(int _pos);

    bool operator<(const Player rhs) const;
};


#endif // PLAYER_H

