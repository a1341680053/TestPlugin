#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

#include "SystemConfig/SystemConfig_global.h"
#include <QVariant>

class SYSTEMCONFIG_EXPORT SystemConfig
{
    SystemConfig();
    ~SystemConfig();

    static SystemConfig *mInstance;
public:
    static SystemConfig *GetInstance();

    /// @brief 获取数据文件路径
    /// @return path = 路径
    QString getDataPath();

    /// @brief 设置系统参数
    /// @param key 键
    /// @param value 值
    void setSystemConfig(const QString &key, const  QVariant& value);
    /// @brief 获取系统参数
    /// @param key 键
    /// @return value = 值
    QVariant getSystemConfig(const QString &key);
private:
    /// @brief 系统参数
    QMap<QString, QVariant> mSystemConfig;
    /// @brief 数据文件路径
    QString mDataPath;
};

#endif // SYSTEMCONFIG_H