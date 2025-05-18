#include "SystemConfig.h"
#include <QCoreApplication>
#include <QDebug>

SystemConfig* SystemConfig::mInstance = nullptr;

SystemConfig::SystemConfig()
{
    mDataPath = QCoreApplication::applicationDirPath() + "/../data/";
}

SystemConfig::~SystemConfig()
{
}

SystemConfig* SystemConfig::GetInstance()
{
    if (mInstance == nullptr)
    {
        mInstance = new SystemConfig();
    }
    return mInstance;
}

QString SystemConfig::getDataPath()
{
    return mDataPath;
}

void SystemConfig::setSystemConfig(const QString &key, const QVariant &value)
{
    mSystemConfig[key] = value;
}

QVariant SystemConfig::getSystemConfig(const QString &key)
{
    if (mSystemConfig.contains(key))
    {
        return mSystemConfig[key];
    }
    else
    {
        qDebug() << "Key not found:" << key;
    }
    return QVariant();
}
