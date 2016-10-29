#include "script.h"
#include "scripthandler.h"

ScriptHandler::ScriptHandler(QObject *parent) : QObject(parent)
{

}

void ScriptHandler::reset() {
    for(Script *script : m_scriptStack) {
        delete script;
    }
    m_scriptStack.clear();
    m_commands.clear();
}

void ScriptHandler::runCommand(QString command)
{
    m_commands.append(command);
}

void ScriptHandler::runScript(QString script, QString fileName)
{
    Script *script = new Script(this);
    script->setFileName(fileName);
    script->setScript(script);

    m_scriptStack.push(script);
    emit newScript();
}
