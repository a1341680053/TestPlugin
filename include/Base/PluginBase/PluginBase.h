#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <QMainWindow>
#include <QThread>
#include <QMutex>
#include <map>

#include <QMap>
#include <QtPlugin>
#include <QList>
#include <iostream>
#include "PluginBase_global.h"

class PluginBase;
class QPluginLoader;
//插件结构参数数量
#define PLUGIN_STRUCT_NUM 4
struct  pluginStruct{
    
    QString name;
    QString dllName;
    QString version;
    std::string pluginName;
    bool enabled;
    QPluginLoader* pluginPtr;
    pluginStruct()
    {
        enabled = false;
        pluginPtr = nullptr;
    }
};
struct  MsgStruct
{
    int type;
    std::string sender;
    std::string receiver;
    std::string msg;
};

class PLUGINBASE_EXPORT  PluginBase : public QObject
{
    Q_OBJECT
public:
     explicit PluginBase(QObject* parent);
    ~PluginBase();

    virtual void sendMsgToManager(const std::string& sender,const std::string& receiver,const int type,const std::string& msg);

    virtual void recMsgFromManager(const std::string& sender,const std::string& receiver,const int type,const std::string& msg) = 0;

    std::string getPluginName();
    std::string getVersion();
protected:
    std::string pluginName;
    std::string version;
};
Q_DECLARE_INTERFACE(PluginBase, "com.example.PluginBase")

class PLUGINBASE_EXPORT  EventDispatcher : public QThread
{
    Q_OBJECT
public:
    static EventDispatcher* GetInstance(); 

    void setMainWindow(QMainWindow* w);
    QMainWindow* getMainWindow();

    void sendMsgToManager(const std::string &sender, const std::string &receiver, const int type, const std::string &msg);

    QMap<QString,pluginStruct> getPlugins()const;
    //关闭一个插件
    bool removePlugin(const QString& pluginName);
    //关闭全部插件
    void clearPlugins();
private:
    EventDispatcher(QObject *parent = nullptr);
    void init();
    void loadPlugin();
    PluginBase* loadDLL(const QString& dllName,QPluginLoader*& pluginPtr);
    void run();

    void sendMsg();
private:
    static EventDispatcher* mpInstance;
    QMainWindow* mpParent;
    std::map<std::string,PluginBase*> mPluginsMap;
    QMap<QString,pluginStruct>  mLoadMap;

    MsgStruct s_Msg;

    QMutex mMutex;
};

#endif // PLUGINBASE_H