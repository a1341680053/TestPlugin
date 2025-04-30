#include "PluginCreate.h"
#include "ui_PluginCreate.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QDir>
#include <json/json.h>
#include <iostream>
#include <fstream>

PluginCreate::PluginCreate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PluginCreate)
{
    ui->setupUi(this);
    
    init();
}

PluginCreate::~PluginCreate()
{
    delete ui;
}

void PluginCreate::init()
{
    ui->setPath_Let->setText(QApplication::applicationDirPath() + "/../" + "src/Plugins");

    mTempData = QApplication::applicationDirPath() + "/../" + "data/PluginCreate/";
    this->setMaximumWidth(400);

    connect(ui->setPath_Btn,&QPushButton::clicked,this,&PluginCreate::slotSetPluginPath);
    connect(ui->ok_Btn,&QPushButton::clicked,this,&PluginCreate::slotOkClicked);
    connect(ui->cancel_Btn,&QPushButton::clicked,this,&PluginCreate::slotCancelClicked);
}

void PluginCreate::slotSetPluginPath()
{
    QString dirPath = QFileDialog::getExistingDirectory(
    this,
    "选择目录",
    ui->setPath_Let->text());
//QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
    if (!dirPath.isEmpty()) {
        qDebug() << "选中的目录:" << dirPath;
    }

    ui->setPath_Let->setText(dirPath);

}

void PluginCreate::slotOkClicked()
{
    QString pluginName = ui->pluginName_Let->text();
    if (pluginName.isEmpty())
    {
        return;
    }
    QString str = QString("测试带-------------------");
    std::cout << "测试带-------------------";


    QString pluginPath = ui->setPath_Let->text() + "/" + pluginName + "/";

    QDir dir;
    dir.mkdir(pluginPath);

    createPluginFile(pluginPath,pluginName,"TestPlugin.h",pluginName+".h");
    createPluginFile(pluginPath,pluginName,"TestPlugin.cpp",pluginName+".cpp");
    createPluginFile(pluginPath,pluginName,"CMakeLists.txt","CMakeLists.txt");
    createPluginJson(pluginPath);
    this->close();
}

void PluginCreate::slotCancelClicked()
{
    this->close();
}

void PluginCreate::createPluginFile(const QString &path, const QString &name,const QString& tempFile, const QString &fileName)
{
    QFile  file(mTempData + tempFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    QString data = file.readAll();
    file.close();
    data.replace("TestPlugin",name);

    QFile out(path+fileName);
    if (!out.open(QIODevice::WriteOnly))
    {
        return;
    }
    out.write(data.toLocal8Bit());
    out.close();
}

void PluginCreate::createPluginJson(const QString &path)
{
    Json::Value root;

    root["Keys"] = ui->pluginName_Let->text().toLocal8Bit().constData();
    root["version"] = ui->version_Let->text().toLocal8Bit().constData();


    std::string filePath = path.toStdString() + "PluginInformation.json";
    std::ofstream outFile(filePath);
    if (!outFile.is_open())
    {
        return;
    }
    
    // Json::StreamWriterBuilder writer;
    // outFile << Json::writeString(writer,root);
    // outFile.close();

    Json::StyledWriter buff;
    outFile << buff.write(root);
    outFile.close();
}
