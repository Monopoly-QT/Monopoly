//
// Created by Kai Huang on 2025/5/3.
//

#ifndef HORSERACING_H
#define HORSERACING_H

#include <QMap>
#include <QObject>
#include <QVector>
#include "../../Player/Player.h"


class HorseRacing : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVector<int> horsesPrecess READ horsesPrecess WRITE setHorsesPrecess NOTIFY horsesPrecessChanged FINAL)
    Q_PROPERTY(int winner READ winnerPrecess WRITE setWinnerPrecess NOTIFY winnerPrecessChanged FINAL)

    Player* player{};
    int _winner = -1;
public:
    [[nodiscard]] QVector<int> horsesPrecess() const;
    [[nodiscard]] int winnerPrecess() const;

    explicit HorseRacing();

    void init(Player *player);

    void setHorsesPrecess(const QVector<int> &newHorsesPrecess);


    void setWinnerPrecess(const int &newWinnerPrecess);

    void gameLogic( int gamblingMoney, int betHorse);

    Q_INVOKABLE void mainGame(int gamblingMoney, int betHorse);

signals:
    void horsesPrecessChanged();
    void winnerPrecessChanged();
    void updateState();

private:
    QVector<int> m_horsesPrecess;
};


inline QVector<int> HorseRacing::horsesPrecess() const {
    return m_horsesPrecess;
}

inline void HorseRacing::setHorsesPrecess(const QVector<int> &newhorsesPrecess) {
    if (m_horsesPrecess == newhorsesPrecess)
        return;
    m_horsesPrecess = newhorsesPrecess;
    emit horsesPrecessChanged();
}

inline int HorseRacing::winnerPrecess() const {
    return _winner;
}

inline void HorseRacing::setWinnerPrecess(const int &newWinnerPrecess) {
    if (_winner == newWinnerPrecess)
        return;
    _winner = newWinnerPrecess;
    emit winnerPrecessChanged();
}
#endif //HORSERACING_H
