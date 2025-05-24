//
// Created by Kai Huang on 2025/5/2.
//
#include <iostream>

#include "../../Player/Player.h"
#include "HorseRacing.h"
#include <map>
#include <ostream>
#include <vector>
#include <QMetaObject>
#include <QObject>
#include <thread>
#include <chrono>
#include <thread>

using namespace std;


HorseRacing::HorseRacing() {
}

void HorseRacing::init(Player *player) {
    srand(time(nullptr));
    this->player = player;
    m_horsesPrecess.clear();
    _winner = -1;
    emit horsesPrecessChanged();
    emit winnerPrecessChanged();
}

void HorseRacing::gameLogic( int gamblingMoney, int betHorse) {
    int finalLine = 100;

    m_horsesPrecess.clear();
    m_horsesPrecess.resize(4, 0); // Initialize array with 4 zeros

    int winner = -1;
    while (true) {

        int min = 100;
        for (int i = 0; i < 4; i++) {
            m_horsesPrecess[i] += rand() % 5 + 8;
            // 回到主執行緒更新資料
            QMetaObject::invokeMethod(this, [this]() {
                emit horsesPrecessChanged(); // 發送 signal
            }, Qt::QueuedConnection);

            int max = 0;
            int maxIndex = 0;
            for (int j = 0; j < m_horsesPrecess.size(); j++) {
                if (m_horsesPrecess[j] > max) {
                    max = m_horsesPrecess[j];
                    maxIndex = j;
                }
                if (m_horsesPrecess[j] < min) {
                    min = m_horsesPrecess[j];
                }
            }
            if (max >= finalLine) {
                if (winner == -1) {
                    winner = maxIndex;
                }
                for (int &m_horsesPreces: m_horsesPrecess) {
                    if (m_horsesPreces > 100) {
                        m_horsesPreces = 100;
                    }
                }
            }

            cout << m_horsesPrecess[i] << " ";
        }
        cout << endl;
        if (min >= finalLine) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    if (winner == betHorse) {
        player->addMoney(gamblingMoney);
    }else {
        player->subMoney(gamblingMoney);
    }
    cout<<player->getMoney()<<endl;
    // 回到主執行緒更新資料
    QMetaObject::invokeMethod(this, [this,winner]() {
        setWinnerPrecess(winner);
        emit updateState();
    }, Qt::QueuedConnection);
}

/**
 * 賭馬
 */
void HorseRacing::mainGame( int gamblingMoney, int betHorse) {
    std::thread t1([this, gamblingMoney, betHorse]() {
        this->gameLogic(gamblingMoney, betHorse);
    });
    t1.detach();
}


