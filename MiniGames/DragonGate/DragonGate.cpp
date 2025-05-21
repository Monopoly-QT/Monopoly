//
// Created by Kai Huang on 2025/5/3.
//

#include "DragonGate.h"
#include <algorithm>
#include <QDebug>

DragonGate::DragonGate(){
    srand(time(nullptr));
}

bool DragonGate::startGame(int gamblingMoney) {
    if (!m_player) {
        qWarning() << "Player not set!";
        return false;
    }

    setGamblingMoney(gamblingMoney);
    int rand1 = rand() % 13 + 1;
    int rand2 = rand() % 13 + 1;
    setFirstNumber(std::min(rand1, rand2));
    setSecondNumber(std::max(rand1, rand2));
    m_isGameStarted = true;
    emit gameStartedChanged();
    m_gameResult = -1;
    emit gameResultChanged();
    
    return m_firstNumber == m_secondNumber;
}

int DragonGate::makeGuess(bool selection) {
    if (!m_isGameStarted || !m_player) {
        qWarning() << "Game not started or player not set!";
        return -1;
    }

    setThirdNumber(rand() % 13 + 1);
    int result = -1;

    if (m_firstNumber == m_secondNumber) {
        if (!selection && m_thirdNumber < m_firstNumber) {
            m_player->addMoney(m_gamblingMoney);
            result = 1;
        } else if (selection && m_thirdNumber > m_firstNumber) {
            m_player->addMoney(m_gamblingMoney);
            result = 1;
        } else if (m_thirdNumber == m_firstNumber) {
            m_player->subMoney(m_gamblingMoney * 3);
            result = 2;
        } else {
            m_player->subMoney(m_gamblingMoney);
            result = 0;
        }
    } else {
        if (!selection && m_thirdNumber < m_secondNumber && m_thirdNumber > m_firstNumber) {
            m_player->addMoney(m_gamblingMoney);
            result = 1;
        } else if (selection && (m_thirdNumber > m_secondNumber || m_thirdNumber < m_firstNumber)) {
            m_player->addMoney(m_gamblingMoney);
            result = 1;
        } else if (m_thirdNumber == m_firstNumber || m_thirdNumber == m_secondNumber) {
            m_player->subMoney(m_gamblingMoney * 2);
            result = 2;
        } else {
            m_player->subMoney(m_gamblingMoney);
            result = 0;
        }
    }

    m_gameResult = result;
    emit gameResultChanged();
    emit gameEnded(result);
    m_isGameStarted = false;
    emit gameStartedChanged();
    
    return result;
}

int DragonGate::firstNumber() const {
    return m_firstNumber;
}

void DragonGate::setFirstNumber(int newFirstNumber) {
    if (m_firstNumber == newFirstNumber)
        return;
    m_firstNumber = newFirstNumber;
    emit firstNumberChanged();
}

int DragonGate::secondNumber() const {
    return m_secondNumber;
}

void DragonGate::setSecondNumber(int newSecondNumber) {
    if (m_secondNumber == newSecondNumber)
        return;
    m_secondNumber = newSecondNumber;
    emit secondNumberChanged();
}

int DragonGate::thirdNumber() const {
    return m_thirdNumber;
}

void DragonGate::setThirdNumber(int newThirdNumber) {
    if (m_thirdNumber == newThirdNumber)
        return;
    m_thirdNumber = newThirdNumber;
    emit thirdNumberChanged();
}

int DragonGate::gamblingMoney() const {
    return m_gamblingMoney;
}

void DragonGate::setGamblingMoney(int newGamblingMoney) {
    if (m_gamblingMoney == newGamblingMoney)
        return;
    m_gamblingMoney = newGamblingMoney;
    emit gamblingMoneyChanged();
}

bool DragonGate::isGameStarted() const {
    return m_isGameStarted;
}

int DragonGate::gameResult() const {
    return m_gameResult;
}
