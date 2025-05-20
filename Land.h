#ifndef LAND_H
#define LAND_H

#include<string>
#include <QObject>
#include<QColor>

using namespace std;

class Land: public QObject{
    Q_OBJECT

private:
    int type;   // 0:normal 1:event 2:store 3:hospital 4: Start
    int pos;
    int owner; //0:null 1:player1 2:player2 3:player3 4:player4
    int level; //only for house 0:empty 1:one house 2:two houses 3:three houses 4:motel
    int state; //0:normal 1:have roadblocks
    string name;
    int value;
public:
    Land();
    Land(int _type, int _pos, string _name, int _value);
    void setOwner(int _player);
    void setType(int _type);
    void setLevel(int _level);
    void setState(int _state);

    string getName();
    int getType();
    int getPos();
    int getOwner();
    int getLevel();
    int getState();
    int getValue();
};

#endif // LAND_H
