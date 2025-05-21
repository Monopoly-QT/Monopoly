#include "MovePoint.h"

MovePoint::MovePoint(){
    m_isvisable = false;
    m_changeX = 0;
    m_changeY  = 0;
    m_displayColor = "transparent";
}

void MovePoint::setColor(int _turn){
    if(_turn == 0){
        setDisplayColor("#ff1700");
    }
    else if(_turn == 1){
        setDisplayColor("#009aff");
    }
    else if(_turn == 2){
        setDisplayColor("#0fff00");
    }
    else{
        setDisplayColor("#ffcb00");
    }
}

void MovePoint::initializeMovePoint(double _posX,double _posY,int _turn){
    setChangeX(_posX);
    setChangeY(_posY);
    setColor(_turn);
}

void MovePoint::movingMovePoint(double _posX,double _posY){
    setChangeX(_posX);
    setChangeY(_posY);
}

void MovePoint::hiddingMovePoint(){
    setIsvisable(false);
}



bool MovePoint::isvisable() const
{
    return m_isvisable;
}

void MovePoint::setIsvisable(bool newIsvisable)
{
    if (m_isvisable == newIsvisable)
        return;
    m_isvisable = newIsvisable;
    emit isvisableChanged();
}

int MovePoint::changeX() const
{
    return m_changeX;
}

void MovePoint::setChangeX(double newChangeX)
{
    if (m_changeX == newChangeX)
        return;
    m_changeX = newChangeX;
    emit changeXChanged();
}

int MovePoint::changeY() const
{
    return m_changeY;
}

void MovePoint::setChangeY(double newChangeY)
{
    if (m_changeY == newChangeY)
        return;
    m_changeY = newChangeY;
    emit changeYChanged();
}

QColor MovePoint::displayColor() const
{
    return m_displayColor;
}

void MovePoint::setDisplayColor(const QColor &newDisplayColor)
{
    if (m_displayColor == newDisplayColor)
        return;
    m_displayColor = newDisplayColor;
    emit displayColorChanged();
}
