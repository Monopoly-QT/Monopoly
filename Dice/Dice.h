#include<QQmlComponent>
#include <QObject>
#include <QGuiApplication>
#include<QColor>
#include<vector>

using namespace std;

#ifndef DICE_H
#define DICE_H

class Dice:public QObject{
    Q_OBJECT
    Q_PROPERTY(bool DiceAShow READ DiceAShow NOTIFY DiceAShowChanged FINAL);
    Q_PROPERTY(bool DiceBShow READ DiceBShow NOTIFY DiceBShowChanged FINAL);
    Q_PROPERTY(bool DiceCShow READ DiceCShow NOTIFY DiceCShowChanged FINAL);
    Q_PROPERTY(bool DiceDShow READ DiceDShow NOTIFY DiceDShowChanged FINAL);
    Q_PROPERTY(bool DiceEShow READ DiceEShow NOTIFY DiceEShowChanged FINAL);
    Q_PROPERTY(bool DiceFShow READ DiceFShow NOTIFY DiceFShowChanged FINAL);
    Q_PROPERTY(bool DiceGShow READ DiceGShow NOTIFY DiceGShowChanged FINAL);
    Q_PROPERTY(QColor pointColor READ pointColor WRITE setPointColor NOTIFY pointColorChanged FINAL);
    Q_PROPERTY(int dicePoint READ dicePoint NOTIFY dicePointChanged FINAL);
public:
    Dice();

    Q_INVOKABLE void rollDice(int seed);

    bool DiceAShow() const;
    void setDiceAShow();

    bool DiceBShow() const;
    void setDiceBShow();

    bool DiceCShow() const;
    void setDiceCShow();

    bool DiceDShow() const;
    void setDiceDShow();

    bool DiceEShow() const;
    void setDiceEShow();

    bool DiceFShow() const;
    void setDiceFShow();

    bool DiceGShow() const;
    void setDiceGShow();

    QColor pointColor() const;
    void setPointColor(const QColor &_color);

    int dicePoint() const;

    // Q_INVOKABLE void test(Dice *dice);

    // void new_thread(int times);

signals:
    void DiceAShowChanged();
    void DiceBShowChanged();
    void DiceCShowChanged();
    void DiceDShowChanged();
    void DiceEShowChanged();
    void DiceFShowChanged();
    void DiceGShowChanged();
    void pointColorChanged();
    void dicePointChanged();
    // void test_signal();

private:
    vector<vector<int>> diceGraph;
    int point;
    vector<int> generatedPoint;
    int index;
    bool m_diceAShow;
    bool m_diceBShow;
    bool m_diceCShow;
    bool m_diceDShow;
    bool m_diceEShow;
    bool m_diceFShow;
    bool m_diceGShow;
    QColor color;
};

#endif // DICE_H
