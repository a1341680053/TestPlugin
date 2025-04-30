#ifndef SETTINGPLUGIN_H
#define SETTINGPLUGIN_H

#include "PluginBase.h"

class SettingDialog;

class SettingPlugin : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.PluginBase" FILE "SettingPlugin.json")
    Q_INTERFACES(PluginBase)
public:
    explicit SettingPlugin(QObject *parent = nullptr);

    void recMsgFromManager(const std::string& sender,const std::string& receiver,const int type,const std::string& msg);

signals:
    void signalShowSettingWidget();
public slots:
    void slotShowSettingWidget();
private:
    SettingDialog* mpSettingDialog;
};

#endif // SETTINGPLUGIN_H