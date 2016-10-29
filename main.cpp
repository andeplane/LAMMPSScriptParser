#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "script.h"
#include <QtQml>

int main(int argc, char *argv[])
{
    qmlRegisterType<Script>("Atomify", 1, 0, "Script");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
