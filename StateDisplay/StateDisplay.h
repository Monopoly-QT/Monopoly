#include "Player/Player.h"
#include "Land/Land.h"
#include <QObject>
#include <QString>

#ifndef STATEDISPLAY_H
#define STATEDISPLAY_H

class StateDisplay: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged FINAL);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL);
    Q_PROPERTY(int ownMoney READ ownMoney WRITE setOwnMoney NOTIFY ownMoneyChanged FINAL);
    Q_PROPERTY(int landValue1 READ landValue1 WRITE getlandValue NOTIFY landValueShow FINAL);
    Q_PROPERTY(int landValue2 READ landValue2 WRITE getlandValue NOTIFY landValueShow FINAL);


private:

    QString m_imageSource;

    QString m_name;

    int m_ownMoney;

    int _landValue1 , _landValue2;

public:

    void initialStateDisplay(int _turn, Player* _player);

    QString imageSource() const;
    void setImageSource(const QString &newImageSource);

    QString name() const;
    void setName(const QString &newName);

    int ownMoney() const;
    void setOwnMoney(int newOwnMoney);

    int landValue1() const;
    int landValue2() const;
    void getlandValue1(int landValue);
    void getlandValue2(int landValue);

signals:
    void imageSourceChanged();
    void nameChanged();
    void ownMoneyChanged();
    void landValueShow();
};

#endif // STATEDISPLAY_H
