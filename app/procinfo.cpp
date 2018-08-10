#include "procinfo.h"
#include <QJsonObject>
#include <QString>

ProcInfo::ProcInfo(QJsonObject obj)
{
	m_cmd = obj["cmd"].toString();
	m_tid = obj["tid"].toInt();
	m_euid = obj["euid"].toInt();
	m_scpu = obj["scpu"].toDouble();
	m_ucpu = obj["ucpu"].toDouble();
	m_resident_memory = obj["resident_memory"].toDouble();
	m_state = obj["state"].toString();
}

QString ProcInfo::cmd(QJsonObject obj) const
{
	return m_cmd;
}

int ProcInfo::tid(QJsonObject obj) const
{
	return m_tid;
}

int ProcInfo::euid(QJsonObject obj) const
{
	return m_euid;
}

double ProcInfo::scpu(QJsonObject obj) const
{
	return m_scpu;
}

double ProcInfo::ucpu(QJsonObject obj) const
{
	return m_ucpu;
}

double ProcInfo::resident_memory(QJsonObject obj) const
{
	return m_resident_memory;
}

QString ProcInfo::state(QJsonObject obj) const
{
	return m_state;
}

bool operator==(const ProcInfo &obj) {
	ProcInfo obj2(jobj); 
	if(this.m_cmd == obj.m_cmd &&
	   this.m_tid == obj.m_tid &&
	   this.m_euid == obj.m_euid &&
	   this.m_scpu == obj.m_scpu &&
	   this.m_ucpu == obj.m_ucpu &&
	   this.m_resident_memory == obj.m_resident_memory &&
	   this.m_state == obj.m_state) {
		return true;
	} else {
		return false;
	}
}