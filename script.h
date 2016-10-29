#ifndef SCRIPT_H
#define SCRIPT_H
#include <QString>
#include <QObject>
#include <QVector>
#include <QMap>

class Script : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString script READ script WRITE setScript NOTIFY scriptChanged)
    Q_PROPERTY(bool finished READ finished WRITE setFinished NOTIFY finishedChanged)
    Q_PROPERTY(bool crashed READ crashed WRITE setCrashed NOTIFY crashedChanged)
    Q_PROPERTY(int currentLine READ currentLine WRITE setCurrentLine NOTIFY currentLineChanged)
public:
    explicit Script(QObject *parent = 0);
    QString fileName() const;
    QString script() const;
    bool finished() const;
    int currentLine() const;
    bool crashed() const;

signals:
    void fileNameChanged(QString fileName);
    void scriptChanged(QString script);
    void finishedChanged(bool finished);
    void currentLineChanged(int currentLine);
    void crashedChanged(bool crashed);

public slots:
    void setFileName(QString fileName);
    void setScript(QString script);
    void setFinished(bool finished);
    void setCurrentLine(int currentLine);
    void setCrashed(bool crashed);

private:
    bool m_finished;
    int m_currentLine;
    bool m_crashed;
    QString m_fileName;
    QString m_script;
    QMap<QString, int> m_labels; // Maps labels to line numbers
};

#endif // SCRIPT_H
