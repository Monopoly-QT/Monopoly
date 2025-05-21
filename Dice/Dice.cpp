#include "Dice.h"
#include<iostream>
#include<random>
#include<ctime>
#include<vector>
#include <thread>
#include <chrono>

using namespace std;

Dice::Dice(){
    diceGraph.push_back({0,0,0,1,0,0,0});
    diceGraph.push_back({0,0,1,0,1,0,0});
    diceGraph.push_back({0,0,1,1,1,0,0});
    diceGraph.push_back({1,0,1,0,1,0,1});
    diceGraph.push_back({1,0,1,1,1,0,1});
    diceGraph.push_back({1,1,1,0,1,1,1});
    point = 0;
    index = 0;
    color = "red";
    setDiceAShow();
    setDiceBShow();
    setDiceCShow();
    setDiceDShow();
    setDiceEShow();
    setDiceFShow();
    setDiceGShow();
}



Q_INVOKABLE void Dice::rollDice(int seed){
    srand(time(NULL) + seed);
    if(generatedPoint.size() < 3){
        generatedPoint.push_back(point);
        point = rand() % 6;
        index++;
    }else{
        while(point == generatedPoint[0] || point == generatedPoint[1] || point == generatedPoint[2]){
            point = rand() % 6;
        }
        generatedPoint[index]=point;
        index = (index + 1) % 3;
        emit dicePointChanged();
    }
    if(point == 0 || point == 3)
        setPointColor("red");
    else
        setPointColor("black");
    setDiceAShow();
    setDiceBShow();
    setDiceCShow();
    setDiceDShow();
    setDiceEShow();
    setDiceFShow();
    setDiceGShow();
}

int Dice::dicePoint() const
{
    return point;
}

// Dice A
bool Dice::DiceAShow() const {
    return m_diceAShow;
}

void Dice::setDiceAShow() {
    m_diceAShow = diceGraph[point][0];
    emit DiceAShowChanged();
}

// Dice B
bool Dice::DiceBShow() const {
    return m_diceBShow;
}

void Dice::setDiceBShow() {
    m_diceBShow = diceGraph[point][1];
    emit DiceBShowChanged();
}

// Dice C
bool Dice::DiceCShow() const {
    return m_diceCShow;
}

void Dice::setDiceCShow() {
    m_diceCShow = diceGraph[point][2];
    emit DiceCShowChanged();
}

// Dice D
bool Dice::DiceDShow() const {
    return m_diceDShow;
}

void Dice::setDiceDShow() {
    m_diceDShow = diceGraph[point][3];
    emit DiceDShowChanged();
}

// Dice E
bool Dice::DiceEShow() const {
    return m_diceEShow;
}

void Dice::setDiceEShow() {
    m_diceEShow = diceGraph[point][4];
    emit DiceEShowChanged();
}

// Dice F
bool Dice::DiceFShow() const {
    return m_diceFShow;
}

void Dice::setDiceFShow() {
    m_diceFShow = diceGraph[point][5];
    emit DiceFShowChanged();
}

// Dice G
bool Dice::DiceGShow() const {
    return m_diceGShow;
}

void Dice::setDiceGShow() {
    m_diceGShow = diceGraph[point][6];
    emit DiceGShowChanged();
}


QColor Dice::pointColor() const {
    return color;
}

void Dice::setPointColor(const QColor &_color) {
    color = _color;
    emit pointColorChanged();
}

// void Dice::new_thread(int times){
//     for(int i=0;i<times;i++){
//         if(i!=0)
//             this_thread::sleep_for(chrono::milliseconds(500));
//         QMetaObject::invokeMethod(this, "test_signal", Qt::QueuedConnection);
//     }
// }

// void Dice::test(Dice *dice){
//     int times=10;
//     std::thread t(&Dice::new_thread ,dice, 20);
//     t.detach();
// }
