#pragma once

#include <QObject>
#include <QString>

class ProcInfo
    : public QObject
{
    Q_OBJECT

public:
    QString cmd() const;
    int tid() const;
    int euid() const;
    double scpu() const;
    double ucpu() const;
    double resident_memory() const;
    QString state() const;

    QDataStream& operator>>(QDataStream& s, ProcInfo& p)
    QDataStream& operator<<(QDataStream& s, ProcInfo& p)
    {
        
    }

private:
	QString m_cmd;
	int m_tid;
	int m_euid;
	double m_scpu;
	double m_ucpu;
	double m_resident_memory;
	QString m_state;
};