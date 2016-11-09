#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "script.h"
#include "scripthandler.h"
#include "scriptcommand.h"
#include "lammpscontroller.h"
#include <QtQml>

int main(int argc, char *argv[])
{
    QString fileName("/projects/LAMMPSScriptParser/LAMMPSScriptParser/lj.in");

    // if(argc > 1) fileName = QString(argv[1]);
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error, could not open file " << fileName;
        exit(1);
    }


    QString contents = file.readAll();

//    qmlRegisterType<Script>("Atomify", 1, 0, "Script");
//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    LAMMPSController controller;
    ScriptHandler handler;

    handler.runScript(contents, fileName);
    while(handler.hasNextCommand()) {
        qDebug() << "New list of commands:";
        QList<ScriptCommand> commands = handler.nextCommands(controller);
        for(const ScriptCommand& command : commands) {
            qDebug() << "   " << command.command();
        }
        qDebug() << "";
        handler.didFinishPreviousCommands();
    }

    return 0;
}
