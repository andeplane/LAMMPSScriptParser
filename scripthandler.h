#ifndef SCRIPTHANDLER_H
#define SCRIPTHANDLER_H

#include <QObject>
#include <QStack>

class ScriptHandler : public QObject
{
    Q_OBJECT

public:
    explicit ScriptHandler(QObject *parent = 0);
    Q_INVOKABLE void reset();
    Q_INVOKABLE void runCommand(QString command);
    Q_INVOKABLE void runScript(QString script, QString fileName);

signals:
    void newScript();
    void newCommand();

public slots:

private:
    QStack<class Script*> m_scriptStack;
    QVector<QString> m_commands;
};

#endif // SCRIPTHANDLER_H
