#include <QObject>
#include <QList>
#include <QString>
#include <land.h>

#ifndef USECARDSETTING_H
#define USECARDSETTING_H

class UseCardSetting: public QObject{
    Q_OBJECT
    Q_PROPERTY(QList<int> displayTargetPlayer READ displayTargetPlayer WRITE setDisplayTargetPlayer NOTIFY displayTargetPlayerChanged FINAL);
    Q_PROPERTY(QList<QString> displayTargetLand READ displayTargetLand WRITE setDisplayTargetLand NOTIFY displayTargetLandChanged FINAL);
    Q_PROPERTY(QList<int> cardUseAvailable READ cardUseAvailable WRITE setCardUseAvailable NOTIFY cardUseAvailableChanged FINAL);
    Q_PROPERTY(QList<int> ownCardCount READ ownCardCount WRITE setOwnCardCount NOTIFY ownCardCountChanged FINAL);
private:
    QList<int> m_displayTargetPlayer;
    QList<QString> m_displayTargetLand;

    QList<int> m_cardUseAvailable;

    QList<int> m_ownCardCount;

public:
    // UseCardSetting();

    // void initialUseCardPopUp(int _turn,vector<Land> _land);

    QList<int> displayTargetPlayer() const;
    void setDisplayTargetPlayer(const QList<int> &newDisplayTargetPlayer);

    QList<QString> displayTargetLand() const;
    void setDisplayTargetLand(const QList<QString> &newDisplayTargetLand);

    QList<int> cardUseAvailable() const;
    void setCardUseAvailable(const QList<int> &newCardUseAvailable);

    QList<int> ownCardCount() const;
    void setOwnCardCount(const QList<int> &newOwnCardCount);

signals:
    void displayTargetPlayerChanged();
    void displayTargetLandChanged();
    void cardUseAvailableChanged();
    void ownCardCountChanged();
};

#endif // USECARDSETTING_H
