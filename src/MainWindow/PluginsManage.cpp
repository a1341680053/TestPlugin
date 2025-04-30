#include "PluginsManage.h"
#include "ui_PluginsManage.h"
#include "PluginBase.h"

#include <QFile>
#include <QDebug>
#include <iostream>
#include <QDomComment>
#include <QApplication>
#include <QMessageBox>


PluginsManage::PluginsManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginsManage)
{
    ui->setupUi(this);
    init();
}

PluginsManage::~PluginsManage()
{
    EventDispatcher::GetInstance()->clearPlugins();
    delete ui;
}

void PluginsManage::init()
{
    ui->treeWidget->setColumnCount(2);
    QStringList strL = QStringList() << QString::fromLocal8Bit("插件名")
                                        << QString::fromLocal8Bit("版本");
    ui->treeWidget->setHeaderLabels(strL);

    QMap<QString,pluginStruct> plugins = EventDispatcher::GetInstance()->getPlugins();
    
    for (const auto& key : plugins.keys())
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0,key);
        if (plugins[key].enabled)
        {
            item->setCheckState(0,Qt::Checked);
        }
        else
        {
            item->setCheckState(0,Qt::Unchecked);
        }
        item->setText(1,plugins[key].version);
    }
    ui->treeWidget->expandAll();
    
}
