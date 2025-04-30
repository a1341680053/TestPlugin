#include "TestPlugin.h"
#include "comment/PluginsName.hpp"


TestPlugin::TestPlugin(QObject *parent) 
    : PluginBase(parent)
{
    pluginName = plugin_name_test;
}

void TestPlugin::recMsgFromManager(const std::string &sender, const std::string &receiver, const int type, const std::string &msg)
{
    if (sender == plugin_name_setting)
    {
        /* code */
    }
}
