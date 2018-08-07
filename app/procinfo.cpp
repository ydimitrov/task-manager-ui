#include "procinfo.h"

QString ProcInfo::cmd() const
{
    return m_cmd;
}

int ProcInfo::tid() const
{
    return m_tid;
}

int ProcInfo::euid() const
{
    return m_euid;
}

double ProcInfo::scpu() const
{
    return m_scpu;
}

double ProcInfo::ucpu() const
{
    return m_ucpu;
}

double ProcInfo::resident_memory() const
{
    return m_resident_memory;
}

QString ProcInfo::state() const
{
    return m_state;
}
