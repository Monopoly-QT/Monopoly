#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Dice/Dice.h"
#include "Handler/EventHandler/eventHandler.h"
#include "MiniGames/InBetween/InBetween.h"
#include "MiniGames/HorseRacing/HorseRacing.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("monopoly", "Main");
    Dice diceA,diceB;
    eventHandler event;
    engine.rootContext()->setContextProperty("diceA", &diceA);
    engine.rootContext()->setContextProperty("diceB", &diceB);
    engine.rootContext()->setContextProperty("event", &event);

    // auto a = Player(1,"Player1");
    // a.setMoney(50);
    // HorseRacing horse_racing;
    // horse_racing.init(&a);
    // InBetween inBetween;
    // inBetween.init(&a);
    // engine.rootContext()->setContextProperty("gameClass", &horse_racing);
    // engine.rootContext()->setContextProperty("playerClass", &a);
    // engine.loadFromModule("Monopoly", "HorseRacing");

    return app.exec();
}
