#include "Player/Player.h"
#include <QObject>
#include <QString>

#ifndef STATEDISPLAY_H
#define STATEDISPLAY_H

class StateDisplay: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged FINAL);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL);
    Q_PROPERTY(int ownMoney READ ownMoney WRITE setOwnMoney NOTIFY ownMoneyChanged FINAL);

private:

    QString m_imageSource;

    QString m_name;

    int m_ownMoney;

public:

    void initialStateDisplay(int _turn, Player* _player);

    QString imageSource() const;
    void setImageSource(const QString &newImageSource);

    QString name() const;
    void setName(const QString &newName);

    int ownMoney() const;
    void setOwnMoney(int newOwnMoney);

signals:
    void imageSourceChanged();
    void nameChanged();
    void ownMoneyChanged();
};

#endif // STATEDISPLAY_H
