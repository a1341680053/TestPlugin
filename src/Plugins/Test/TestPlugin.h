#pragma once

#include "PluginBase.h"

class TestPlugin : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.PluginBase" FILE "TestPlugin.json")
    Q_INTERFACES(PluginBase)
public:
    explicit TestPlugin(QObject *parent = nullptr);

    void recMsgFromManager(const std::string& sender,const std::string& receiver,const int type,const std::string& msg);

};
