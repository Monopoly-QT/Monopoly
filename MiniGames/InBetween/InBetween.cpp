//
// Created by Kai Huang on 2025/5/3.
//

#include "InBetween.h"
#include <algorithm>
#include <QDebug>

InBetween::InBetween(){
    srand(time(nullptr));
}

bool InBetween::startGame(int gamblingMoney) {
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

int InBetween::makeGuess(bool selection) {
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

int InBetween::firstNumber() const {
    return m_firstNumber;
}

void InBetween::setFirstNumber(int newFirstNumber) {
    if (m_firstNumber == newFirstNumber)
        return;
    m_firstNumber = newFirstNumber;
    emit firstNumberChanged();
}

int InBetween::secondNumber() const {
    return m_secondNumber;
}

void InBetween::setSecondNumber(int newSecondNumber) {
    if (m_secondNumber == newSecondNumber)
        return;
    m_secondNumber = newSecondNumber;
    emit secondNumberChanged();
}

int InBetween::thirdNumber() const {
    return m_thirdNumber;
}

void InBetween::setThirdNumber(int newThirdNumber) {
    if (m_thirdNumber == newThirdNumber)
        return;
    m_thirdNumber = newThirdNumber;
    emit thirdNumberChanged();
}

int InBetween::gamblingMoney() const {
    return m_gamblingMoney;
}

void InBetween::setGamblingMoney(int newGamblingMoney) {
    if (m_gamblingMoney == newGamblingMoney)
        return;
    m_gamblingMoney = newGamblingMoney;
    emit gamblingMoneyChanged();
}

bool InBetween::isGameStarted() const {
    return m_isGameStarted;
}

int InBetween::gameResult() const {
    return m_gameResult;
}
