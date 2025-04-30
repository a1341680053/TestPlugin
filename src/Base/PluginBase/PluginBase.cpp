#include "PluginBase.h"
#include <QFile>
#include <QDebug>
#include <iostream>
#include <QDomComment>
#include <QApplication>
#include <QMessageBox>
#include <QPluginLoader>

EventDispatcher* EventDispatcher::mpInstance = nullptr;

PluginBase::PluginBase(QObject *parent)
    : QObject(parent)
{
    
}

PluginBase::~PluginBase()
{
}

void PluginBase::sendMsgToManager(const std::string &sender, const std::string &receiver, const int type, const std::string &msg){
    EventDispatcher::GetInstance()->sendMsgToManager(sender,receiver,type,msg);
}

std::string PluginBase::getPluginName(){
    return pluginName;
}

std::string PluginBase::getVersion(){
    return version;
}






EventDispatcher *EventDispatcher::GetInstance()
{
    if (nullptr == mpInstance)
    {
        mpInstance = new EventDispatcher();
    }
    
    return mpInstance;
}

void EventDispatcher::setMainWindow(QMainWindow *w)
{
    mpParent = w;
}

QMainWindow *EventDispatcher::getMainWindow()
{
    return mpParent;
}

EventDispatcher::EventDispatcher(QObject *parent)
    : QThread(parent)
    , mpParent(nullptr)
{
    init();
}

void EventDispatcher::init()
{
    loadPlugin();
    this->start();
}

void EventDispatcher::sendMsgToManager(const std::string &sender, const std::string &receiver, const int type, const std::string &msg)
{
    this->wait();
    s_Msg.sender    = sender;
    s_Msg.receiver  = receiver;
    s_Msg.type      = type;
    s_Msg.msg       = msg;
    this->start();
}

QMap<QString, pluginStruct> EventDispatcher::getPlugins() const
{
    return mLoadMap;
}

bool EventDispatcher::removePlugin(const QString &pluginName)
{
    if (mLoadMap.find(pluginName) != mLoadMap.end())
    {
        if (mLoadMap[pluginName].pluginPtr)
        {
            if (mLoadMap[pluginName].pluginPtr->unload())
            {
                mPluginsMap.erase(mLoadMap[pluginName].pluginName);
                mLoadMap.remove(pluginName);
                qDebug() << QString::fromLocal8Bit("插件卸载:") << pluginName;
                return true;
            }
            qDebug() << QString::fromLocal8Bit("插件卸载失败:") << pluginName;
            qDebug() << QString::fromLocal8Bit("错误信息:") << mLoadMap[pluginName].pluginPtr->errorString();
            return false;
        }
        else
        {
            return false;
        }
    }
    return  false;
}

void EventDispatcher::clearPlugins()
{
    QStringList strL = mLoadMap.keys();
    for (auto  i : strL)
    {
        removePlugin(i);
    }
}

void EventDispatcher::loadPlugin()
{
#if 1
    QString path = QApplication::applicationDirPath() + "/plugins/Plugins.xml";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        int ret = QMessageBox::warning(nullptr,"警告","插件配置文件打开失败");
        return;
    }
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        int ret = QMessageBox::warning(nullptr,"警告","插件XML文件解析失败");
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();


    QDomNodeList nodeList = root.childNodes();
    for (int i = 0; i < nodeList.size(); i++)
    {
        QDomNode node = nodeList.at(i);
        if (node.isElement())
        {
            QDomElement element = node.toElement();

            QDomNodeList pluginNodeList = element.childNodes();
            if (PLUGIN_STRUCT_NUM == pluginNodeList.size())
            {
                QString name;
                QString dllName;
                QString version;
                bool enabled = false;
                QDomNode nameNode = pluginNodeList.at(0);
                if (nameNode.isElement())
                {
                    QDomElement nameEle = nameNode.toElement();
                    name = nameEle.text();
                }
                QDomNode dllNode = pluginNodeList.at(1);
                if (dllNode.isElement())
                {
                    QDomElement dllEle = dllNode.toElement();
                    dllName = dllEle.text();
                }
                QDomNode versionNode = pluginNodeList.at(2);
                if (versionNode.isElement())
                {
                    QDomElement versionEle = versionNode.toElement();
                    version = versionEle.text();
                }
                QDomNode enabledNode = pluginNodeList.at(3);
                if (enabledNode.isElement())
                {
                    QDomElement enabledEle = enabledNode.toElement();
                    QString enabledStr = enabledEle.text();
                    if (enabledStr == "true")
                    {
                        enabled = true;
                    }
                }
                pluginStruct pS;
                if (enabled)
                {
                    PluginBase* dllPlugin = loadDLL(dllName,pS.pluginPtr);
                    if (dllPlugin && dllPlugin->getPluginName() != "")
                    {
                        mPluginsMap.insert(std::pair<std::string,PluginBase*>(dllPlugin->getPluginName(),dllPlugin));
                        pS.pluginName = dllPlugin->getPluginName();
                    }
                }
                pS.name = name;
                pS.dllName = dllName;
                pS.version = version;
                pS.enabled = enabled;
                mLoadMap.insert(name,pS);
            }
        }
    }
#else  
#endif
}

PluginBase *EventDispatcher::loadDLL(const QString &dllName,QPluginLoader*& pluginPtr)
{
    QString dllPath = QApplication::applicationDirPath() + "/"+ dllName +".dll";
    pluginPtr = new QPluginLoader(dllPath);
    bool ret = pluginPtr->load();
    QObject* pluginInstance = pluginPtr->instance();
    if (pluginInstance)
    {
        PluginBase* ret = qobject_cast<PluginBase*>(pluginInstance);

        return ret;
    }
    delete  pluginPtr;
    pluginPtr = nullptr;
    return nullptr;
}

void EventDispatcher::run()
{
    if (s_Msg.receiver == "all_plugin")
    {
        for (const auto& pair:mPluginsMap)
        {
            pair.second->recMsgFromManager(s_Msg.sender,s_Msg.receiver,s_Msg.type,s_Msg.msg);
        }
    }
    else
    {
        if (mPluginsMap.find(s_Msg.receiver) != mPluginsMap.end())
        {
            mPluginsMap[s_Msg.receiver]->recMsgFromManager(s_Msg.sender,s_Msg.receiver,s_Msg.type,s_Msg.msg);
        }
    }
    // while (true)
    // {
        
    // }
}

void EventDispatcher::sendMsg()
{
    // QMutexLocker locker(&mMutex);
    
    // for (auto ite=s_MsgList.begin();ite != s_MsgList.end();++ite)
    // {
    //     const MsgStruct& temp = *ite;
    //     if (temp.receiver == "all_plugin")
    //     {
    //         for (const auto& pair:mPluginsMap)
    //         {
    //             pair.second->recMsgFromManager(temp.sender,temp.receiver,temp.type,temp.msg);
    //         }
    //     }
    //     else
    //     {
    //         if (mPluginsMap.find(temp.receiver) != mPluginsMap.end())
    //         {
    //             mPluginsMap[temp.receiver]->recMsgFromManager(temp.sender,temp.receiver,temp.type,temp.msg);
    //         }
    //     }
    //     ite = s_MsgList.erase(ite);
    // }
}
