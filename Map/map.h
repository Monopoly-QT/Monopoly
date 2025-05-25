#include "../Land/Land.h"
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
    Q_PROPERTY(bool showTranslation READ showTranslation WRITE setShowTranslation NOTIFY showTranslationChanged FINAL);
    Q_PROPERTY(QString order READ order WRITE setOrder NOTIFY orderChanged FINAL);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL);
    Q_PROPERTY(QString translation READ translation WRITE setTranslation NOTIFY translationChanged FINAL);
    Q_PROPERTY(QColor displayColor READ displayColor WRITE setDisplayColor NOTIFY displayColorChanged FINAL);
    Q_PROPERTY(QList<int> playerStay READ playerStay WRITE setPlayerStay NOTIFY playerStayChanged FINAL);
    Q_PROPERTY(QList<int> isDisplayBuilding READ isDisplayBuilding WRITE setIsDisplayBuilding NOTIFY isDisplayBuildingChanged FINAL);
    Q_PROPERTY(bool isRoadBlock READ isRoadBlock WRITE setIsRoadBlock NOTIFY isRoadBlockChanged FINAL);


public:
    Map(bool _isDisplay,string _order,string _name,string _translation,vector<int> _playerStay,Land* _land);
    Map();
    bool isDisplay() const;
    void setIsDisplay(bool newIsDisplay);
    bool showTranslation() const;
    void setShowTranslation(bool newShowTranslation);
    void byLevelSetBuildingVisibility(int level);
    void byTypeOrOwnerSetColor(int type,int owner);
    void byPlayoerPosSetVisibility(vector<int> playerPos ,int order);


    QString order() const;
    void setOrder(const QString &newOrder);

    QString name() const;
    void setName(const QString &newName);

    QString translation() const;
    void setTranslation(const QString &newTranslation);

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

    bool isRoadBlock() const;
    void setIsRoadBlock(bool newIsRoadBlock);

signals:
    void isDisplayChanged();

    void showTranslationChanged();

    void orderChanged();

    void nameChanged();

    void translationChanged();

    void displayColorChanged();

    void playerStayChanged();

    void isDisplayBuildingChanged();

    void isRoadBlockChanged();

private:
    bool m_isDisplay;
    bool m_showTranslation = false;
    QString m_order;
    QString m_name;
    QString m_translation;
    QColor m_displayColor;
    QList<int> m_playerStay;
    QList<int> m_isDisplayBuilding;
    bool m_isRoadBlock;
};


#endif // MAP_H
