#include "script.h"
#include "scripthandler.h"
#include "scriptcommand.h"
#include "runcommand.h"
#include "lammpscontroller.h"
#include <QDebug>
#include <cassert>

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

bool ScriptHandler::runCommand(QString command)
{
    if(command.trimmed().startsWith("run") && m_activeRunCommand) {
        return false;
    }

    m_commands.append(command);
    return true;
}

void ScriptHandler::runScript(QString script, QString fileName)
{
    Script *scriptObj = new Script(this);
    scriptObj->setFileName(fileName);
    scriptObj->setScript(script);

    m_scriptStack.push(scriptObj);
    emit newScript();
}

QString ScriptHandler::includePath(const ScriptCommand &command) {
    if(command.command().startsWith("include")) {
        //TODO: Handle this
    }
    return QString(""); // Not an include command
}

bool ScriptHandler::canAddCommandsAfter(const ScriptCommand &command) {
    return false;
}

QList<ScriptCommand> ScriptHandler::singleCommand(LAMMPSController &controller) {

}

QList<ScriptCommand> ScriptHandler::scriptCommands(LAMMPSController &controller) {
    QList<ScriptCommand> commands;
    bool appendMoreCommands = true;
    while(appendMoreCommands && m_scriptStack.size()>0) {
        ScriptCommand command = nextCommand();
        if(!includePath(command).isEmpty()) {
            // TODO: Handle this
            QString path = includePath(command);
            qDebug() << "Error, include statements not supported yet";
            exit(1);
        }

        commands.append(command);
    }
    return commands;
}

QList<ScriptCommand> ScriptHandler::nextCommands(LAMMPSController &controller)
{
    // Step 1) Check for single commands. Parse them as normal commands (i.e. include should work)
    if(m_commands.size() > 0) {
        return singleCommand(controller);
    }

    // Step 2) Continue active run/rerun command
    if(m_activeRunCommand) {
        bool preRunNeeded = true;
        QString nextRunCommand = m_activeRunCommand->nextCommand(controller.currentTimestep, 1, preRunNeeded);

        if(m_activeRunCommand->finished) {
            delete m_activeRunCommand;
            m_activeRunCommand = nullptr;
        }
        QList<ScriptCommand> list;
        ScriptCommand command(nextRunCommand, ScriptCommand::Type::File, 0); // TODO: line numbers
        list.append(command);

        return list;
    }

    // Step 3) Create command queue based on script stack
    if(m_scriptStack.size()>0) {
        return scriptCommands(controller);
    }


}

bool ScriptHandler::hasNextCommand() {
    return m_scriptStack.size()>0 || m_commands.size()>0;
}

void ScriptHandler::didFinishPreviousCommands()
{
    m_runningScript = false;
    if(m_scriptStack.size()>0 && !m_scriptStack.top()->hasNextLine()) {
        m_scriptStack.pop();
    }
}

ScriptCommand ScriptHandler::nextCommand()
{
    if(m_runningScript) {
        qDebug() << "Error, can't ask for more commands while we're still working on the previous commands";
        throw "damn...";
    }
    assert(m_scriptStack.size()>0 && "scriptStack can't be empty when asking for nextCommand()");

    Script *script = m_scriptStack.top();
    int line = script->currentLine();

    QString command;
    bool shouldReadNextLine = true;
    while(shouldReadNextLine) {
        shouldReadNextLine = false;

        QString nextLine = script->getNextLine().trimmed();
        if(nextLine.endsWith("&")) {
            nextLine.remove(nextLine.length() - 1, 1); // Remove the & char
            command.append(" ");
            command.append(nextLine);
            if(script->hasNextLine()) {
                // This is a comment and it continues on the next line
                shouldReadNextLine = true;
                continue;
            }
        }
        command = nextLine;
    }

    bool scriptIsFile = !script->fileName().isEmpty();
    m_runningScript = true;
    return ScriptCommand(command, (scriptIsFile ? ScriptCommand::Type::File : ScriptCommand::Type::Editor), line);
}

int ScriptHandler::simulationSpeed() const
{
    return m_simulationSpeed;
}

void ScriptHandler::setSimulationSpeed(int simulationSpeed)
{
    m_simulationSpeed = simulationSpeed;
}
