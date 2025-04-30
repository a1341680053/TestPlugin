#include "SettingPlugin.h"
#include "comment/PluginsName.hpp"
#include "comment/PluginsMsg.hpp"
#include "SettingDialog.h"


SettingPlugin::SettingPlugin(QObject *parent) 
    : PluginBase(parent)
    , mpSettingDialog(nullptr)
{
    pluginName = plugin_name_setting;

    connect(this,&SettingPlugin::signalShowSettingWidget,this,&SettingPlugin::slotShowSettingWidget);
}

void SettingPlugin::recMsgFromManager(const std::string &sender, const std::string &receiver, const int type, const std::string &msg)
{
    if (type == 5)
    {
        emit signalShowSettingWidget();
    }
    
}

void SettingPlugin::slotShowSettingWidget()
{
    if (nullptr == mpSettingDialog)
    {
        mpSettingDialog = new SettingDialog;
    }
    mpSettingDialog->show();
}
