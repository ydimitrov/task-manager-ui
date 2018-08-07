#include <QJsonArray>
#include <QJsonObject>
#include <QtDebug>
#include <QString>
#include <unistd.h>
#include <iostream>
#include "taskmanager.h"

struct ProcessObj{
	QString cmd;
	int tid;
	int euid;
	double scpu;
	double ucpu;
	double resident_memory;
	QString state;
}currentProc, lastProc;

TaskManager::TaskManager(QObject* parent) : QObject(parent) {

	qDebug() << "Inside contructor";
	connect(&m_client, SIGNAL(connected()), this, SLOT(onClientConnected()));
}

void TaskManager::open(const QUrl &url) {
    qDebug() << "Entered open";
    m_client.open(url);
}

void TaskManager::onClientConnected() {
	qDebug() << "Entered onClientConnected";

	// struct ProcessObj currentProc;
	// struct ProcessObj lastProc;
	// ProcessObj lastProc = {
	// 	"", // cmd
	// 	NULL, // tid
	// 	NULL, // euid
	// 	NULL, // scpu
	// 	NULL, // ucpu
	// 	NULL, // resident_memory
	// 	""  // state
	// };

	ProcessObj currentSet[65535] = {}; // array to hold latest process data 
	ProcessObj prevSet[65535] = {}; // array to hold previous process data

	while(true){

		m_client.call("taskmanager", "get_process_list", QJsonValue(), [this, &currentSet, &prevSet](bool r, const QJsonValue& val) {
			QJsonArray processes;
			if (r) {

				QJsonObject ret_val = val.toObject();
				QJsonObject response = ret_val["response"].toObject();
				processes = response["processes"].toArray();

				std::vector<ProcInfo> procs;
				for(auto it = processes.constBegin(); it != processes.constEnd(); ++it)
				{
					procs.push_back(it->toObject());
				}

				QJsonObject element = processes.at(0).toObject();
				qDebug() << element["cmd"].toString();
				qDebug() << element["resident_mem"].toDouble();
			}
			int processId[processes.size()]; // array to hold process IDs
			int i = 0;

			//for(const QJsonObject& process : processes) {
			for(auto it = processes.constBegin(); it != processes.constEnd(); ++it) {
				currentProc = procces;
				// QJsonObject process = it->toObject();
				// currentProc.cmd = process["cmd"].toString();
				// currentProc.tid = process["tid"].toInt();
				// currentProc.euid = process["euid"].toInt();
				// currentProc.scpu = process["scpu"].toDouble();
				// currentProc.ucpu = process["ucpu"].toDouble();
				// currentProc.resident_memory = process["resident_memory"].toDouble();
				// currentProc.state = process["state"].toString();
				// currentSet[currentProc.tid] = currentProc;
				processId[i] = currentProc.tid;
				i++;
			}
			for(i = 0; i < processes.size(); i++ ) {

				if (prevSet[processId[i]] != NULL && currentSet[processId[i]] == NULL) {

					emit removeProcess(prevSet[processId[i]].tid);
				} else if (prevSet[processId[i]] == NULL && currentSet[processId[i]] != NULL) {

					emit addProcess(prevSet[processId[i]].cmd, prevSet[processId[i]].tid, prevSet[processId[i]].euid, prevSet[processId[i]].scpu, 
									prevSet[processId[i]].ucpu, prevSet[processId[i]].resident_memory, prevSet[processId[i]].state);
				} else if (prevSet[processId[i]] != NULL && currentSet[processId[i]] != NULL) {
					if (prevSet[processId[i]].euid != currentSet[processId[i]].euid or 
						prevSet[processId[i]].scpu != currentSet[processId[i]].scpu or
						prevSet[processId[i]].ucpu != currentSet[processId[i]].ucpu or
						prevSet[processId[i]].resident_memory != currentSet[processId[i]].resident_memory or
						prevSet[processId[i]].state != currentSet[processId[i]].state){

						emit updateProcess(prevSet[processId[i]].cmd, prevSet[processId[i]].tid, prevSet[processId[i]].euid, prevSet[processId[i]].scpu, 
									   	   prevSet[processId[i]].ucpu, prevSet[processId[i]].resident_memory, prevSet[processId[i]].state);
					}
				}
			}
			m_procinfos = procs;
		});
		sleep(3);
	}
}