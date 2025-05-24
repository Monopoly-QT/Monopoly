//
// Created by Kai Huang on 2025/5/3.
//

#ifndef INBETWEEN_H
#define INBETWEEN_H
#include <cstdlib>
#include <ctime>
#include <QObject>

#include "../../Player/Player.h"

class DragonGate : public QObject {
    Q_OBJECT
    Q_PROPERTY(int firstNumber READ firstNumber WRITE setFirstNumber NOTIFY firstNumberChanged FINAL)
    Q_PROPERTY(int secondNumber READ secondNumber WRITE setSecondNumber NOTIFY secondNumberChanged FINAL)
    Q_PROPERTY(int thirdNumber READ thirdNumber WRITE setThirdNumber NOTIFY thirdNumberChanged FINAL)
    Q_PROPERTY(int gamblingMoney READ gamblingMoney WRITE setGamblingMoney NOTIFY gamblingMoneyChanged FINAL)
    Q_PROPERTY(bool isGameStarted READ isGameStarted NOTIFY gameStartedChanged FINAL)
    Q_PROPERTY(int gameResult READ gameResult NOTIFY gameResultChanged FINAL)

private:
    int m_firstNumber = -1; // 第一張牌
    int m_secondNumber = -1; // 第二張牌
    int m_thirdNumber = -1; // 玩家猜的牌
    int m_gamblingMoney = 0;
    bool m_isGameStarted = false;
    int m_gameResult = -1; // -1: 未開始, 0: 猜錯, 1: 猜對, 2: 撞柱
    Player *m_player{};

public:
    explicit DragonGate();

    // 初始化
    void init(Player *player) {
        srand(time(nullptr));
        m_player = player;
        m_firstNumber = -1; // 第一張牌
        m_secondNumber = -1; // 第二張牌
        m_thirdNumber = -1; // 玩家猜的牌
        m_gamblingMoney = 0;
        m_isGameStarted = false;
        m_gameResult = -1; // -1: 未開始, 0: 猜錯, 1: 猜對, 2: 撞柱
        emit gameStartedChanged();
        emit gameResultChanged();
        emit firstNumberChanged();
        emit secondNumberChanged();
        emit thirdNumberChanged();
        emit gamblingMoneyChanged();
    };

    Q_INVOKABLE bool startGame(int gamblingMoney);

    Q_INVOKABLE int makeGuess(bool selection);

    [[nodiscard]] int firstNumber() const;

    void setFirstNumber(int newFirstNumber);

    [[nodiscard]] int secondNumber() const;

    void setSecondNumber(int newSecondNumber);

    [[nodiscard]] int thirdNumber() const;

    void setThirdNumber(int newThirdNumber);

    [[nodiscard]] int gamblingMoney() const;

    void setGamblingMoney(int newGamblingMoney);

    [[nodiscard]] bool isGameStarted() const;

    [[nodiscard]] int gameResult() const;

signals:
    void firstNumberChanged();

    void secondNumberChanged();

    void thirdNumberChanged();

    void gamblingMoneyChanged();

    void gameStartedChanged();

    void gameResultChanged();

    void gameEnded(int result);

    void updateState();
};
#endif //INBETWEEN_H
