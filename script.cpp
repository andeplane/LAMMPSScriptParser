#include "script.h"

Script::Script(QObject *parent) : QObject(parent),
  m_finished(false), m_currentLine(-1), m_crashed(false)
{

}

QString Script::fileName() const
{
    return m_fileName;
}

bool Script::finished() const
{
    return m_finished;
}

int Script::currentLine() const
{
    return m_currentLine;
}

bool Script::crashed() const
{
    return m_crashed;
}

QString Script::script() const
{
    return m_script;
}

void Script::setFileName(QString fileName)
{
    if (m_fileName == fileName)
        return;

    m_fileName = fileName;
    emit fileNameChanged(fileName);
}

void Script::setFinished(bool finished)
{
    if (m_finished == finished)
        return;

    m_finished = finished;
    emit finishedChanged(finished);
}

void Script::setCurrentLine(int currentLine)
{
    if (m_currentLine == currentLine)
        return;

    m_currentLine = currentLine;
    emit currentLineChanged(currentLine);
}

void Script::setCrashed(bool crashed)
{
    if (m_crashed == crashed)
        return;

    m_crashed = crashed;
    emit crashedChanged(crashed);
}

void Script::setScript(QString script)
{
    if (m_script == script)
        return;

    m_script = script;
    emit scriptChanged(script);
}
