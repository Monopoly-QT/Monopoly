#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Dice/Dice.h"
#include "Handler/EventHandler/eventHandler.h"
#include "MiniGames/DragonGate/DragonGate.h"
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
    Dice diceA,diceB;
    eventHandler event(&engine);
    engine.rootContext()->setContextProperty("diceA", &diceA);
    engine.rootContext()->setContextProperty("diceB", &diceB);
    engine.rootContext()->setContextProperty("event", &event);
    engine.loadFromModule("monopoly", "Main");

    // auto a = Player();
    // HorseRacing horse_racing;
    // horse_racing.init(&a);
    // DragonGate inBetween;
    // inBetween.init(&a);
    // engine.rootContext()->setContextProperty("gameClass", &inBetween);
    // engine.rootContext()->setContextProperty("playerClass", &a);
    // engine.loadFromModule("Monopoly", "DragonGate");

    return app.exec();
}
