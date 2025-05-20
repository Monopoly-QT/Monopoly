#include "Land.h"
#include <string>
#include <QQmlComponent>
#include <QObject>
#include <QGuiApplication>
#include <QColor>
#include <QString>
#include <QList>
#include <vector>

using namespace std;

#ifndef MAP_H
#define MAP_H

class Map:public QObject{
    Q_OBJECT
    Q_PROPERTY(bool isDisplay READ isDisplay WRITE setIsDisplay NOTIFY isDisplayChanged FINAL);
    Q_PROPERTY(QString order READ order WRITE setOrder NOTIFY orderChanged FINAL);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL);
    Q_PROPERTY(QColor displayColor READ displayColor WRITE setDisplayColor NOTIFY displayColorChanged FINAL);
    Q_PROPERTY(QList<int> playerStay READ playerStay WRITE setPlayerStay NOTIFY playerStayChanged FINAL);
    Q_PROPERTY(QList<int> isDisplayBuilding READ isDisplayBuilding WRITE setIsDisplayBuilding NOTIFY isDisplayBuildingChanged FINAL);


public:
    Map(bool _isDisplay,string _order,string _name,vector<int> _playerStay,Land* _land);
    Map();
    bool isDisplay() const;
    void setIsDisplay(bool newIsDisplay);
    void byLevelSetBuildingVisibility(int level);
    void byTypeOrOwnerSetColor(int type,int owner);
    void byPlayoerPosSetVisibility(vector<int> playerPos ,int order);


    QString order() const;
    void setOrder(const QString &newOrder);

    QString name() const;
    void setName(const QString &newName);

    bool playerDStay() const;
    void setPlayerDStay(bool newPlayerDStay);

    bool playerBStay() const;
    void setPlayerBStay(bool newPlayerBStay);

    bool playerAStay() const;
    void setPlayerAStay(bool newPlayerAStay);

    bool playerCStay() const;
    void setPlayerCStay(bool newPlayerCStay);

    QColor displayColor() const;
    void setDisplayColor(const QColor &newDisplayColor);

    QList<int> playerStay() const;
    void setPlayerStay(const QList<int> &newPlayerStay);

    QList<int> isDisplayBuilding() const;
    void setIsDisplayBuilding(const QList<int> &newIsDisplayBuilding);

signals:
    void isDisplayChanged();

    void orderChanged();

    void nameChanged();

    void displayColorChanged();

    void playerStayChanged();

    void isDisplayBuildingChanged();

private:
    bool m_isDisplay;
    QString m_order;
    QString m_name;
    QColor m_displayColor;
    QList<int> m_playerStay;
    QList<int> m_isDisplayBuilding;
};


#endif // MAP_H
