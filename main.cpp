#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "calculator.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<Calculator>("Calculator", 1, 0, "Calculator", &Calculator::qmlInstance);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Calculator/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
