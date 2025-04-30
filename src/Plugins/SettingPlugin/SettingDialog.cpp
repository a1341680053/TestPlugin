#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "PluginBase.h"
#include "comment/PluginsName.hpp"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&SettingDialog::slot_test);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::slot_test()
{
    EventDispatcher::GetInstance()->sendMsgToManager(plugin_name_setting,plugin_name_test,5,"Test_10086");
}
