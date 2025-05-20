#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Dice.h"
#include "eventHandler.h"

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

    return app.exec();
}
