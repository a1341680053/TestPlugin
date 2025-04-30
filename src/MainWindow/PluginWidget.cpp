#include "PluginWidget.h"
#include "ui_PluginWidget.h"
#include "PluginsManage.h"
#include "PluginBase.h"
#include "PluginCreate/PluginCreate.h"
#include "comment/PluginsName.hpp"
#include "PluginCreate/PluginCreate.h"

PluginWidget::PluginWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PluginWidget),
    mpPluginsManage(nullptr)
{
    ui->setupUi(this);
    EventDispatcher::GetInstance()->setMainWindow(this);


    mpPluginsManage = new PluginsManage(nullptr);
    mpPluginCreate = new PluginCreate(nullptr);
    
    connect(ui->actionPlugins,&QAction::triggered,this,&PluginWidget::slotActionPlugins);
    connect(ui->actionCreatePlugin,&QAction::triggered,this,&PluginWidget::slotActiionCreatePlugin);
}

PluginWidget::~PluginWidget()
{
    delete mpPluginsManage;
    delete ui;
}

void PluginWidget::slotActionPlugins(bool b)
{
    // EventDispatcher::GetInstance()->sendMsgToManager("",plugin_name_setting,5,"Test_10086");
    mpPluginsManage->show();
}

void PluginWidget::slotActiionCreatePlugin(bool b)
{
    mpPluginCreate->show();
}
