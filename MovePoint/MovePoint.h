#include "../Player/Player.h"
#include "../Map/map.h"
#include <QObject>
#include <QColor>

using namespace std;

#ifndef MOVEPOINT_H
#define MOVEPOINT_H

class MovePoint: public QObject{
    Q_OBJECT
    Q_PROPERTY(bool isvisable READ isvisable WRITE setIsvisable NOTIFY isvisableChanged FINAL);
    Q_PROPERTY(QColor displayColor READ displayColor WRITE setDisplayColor NOTIFY displayColorChanged FINAL);
    Q_PROPERTY(double changeX READ changeX WRITE setChangeX NOTIFY changeXChanged FINAL);
    Q_PROPERTY(double changeY READ changeY WRITE setChangeY NOTIFY changeYChanged FINAL);
private:
    bool m_isvisable;
    double m_changeX;
    double m_changeY;

    QColor m_displayColor;

public:
    MovePoint();
    void initializeMovePoint(double _posX,double _posY,int turn);
    void movingMovePoint(double _posX,double _posY);
    Q_INVOKABLE void hiddingMovePoint();
    void setColor(int turn);

    bool isvisable() const;
    Q_INVOKABLE void setIsvisable(bool newIsvisable);
    int changeX() const;
    void setChangeX(double newChangeX);
    int changeY() const;
    void setChangeY(double newChangeY);

    QColor displayColor() const;
    void setDisplayColor(const QColor &newDisplayColor);

signals:
    void isvisableChanged();
    void changeXChanged();
    void changeYChanged();
    void displayColorChanged();
};

#endif // MOVEPOINT_H
