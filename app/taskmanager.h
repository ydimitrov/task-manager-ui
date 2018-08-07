#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QStringList>
#include "qafbwebsocketclient.h"

#ifndef TASKMANAGER_H
#define TASKMANAGER_H

class TaskManager : public QObject
{
	Q_OBJECT

public:
    explicit TaskManager(QObject* parent = nullptr);

    Q_INVOKABLE void open(const QUrl& url);

signals:
	void updateProcess(char cmd_[], int tid_, int euid_, double scpu_, double ucpu_, double resident_memory_, char state_);
	void addProcess(char cmd_[], int tid_, int euid_, double scpu_, double ucpu_, double resident_memory_, char state_);
	void removeProcess(int tid_);

private slots:
	void onClientConnected();

private:
	QAfbWebsocketClient m_client;
};

#endif // TASKMANAGER_H
