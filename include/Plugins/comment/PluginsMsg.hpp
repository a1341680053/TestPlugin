#ifndef _PLUGINSMESSAGE_H_
#define _PLUGINSMESSAGE_H_

#include <QDataStream>
#include <QByteArray>
#include <iostream>

template <typename T>   
std::string PackageMsg(const T& data,QDataStream::ByteOrder order = QDataStream::LittleEndian){
    QByteArray buff;
    QDataStream stream(&buff,QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_7);
    stream.setByteOrder(order);
    stream<< data;

    return buff.toStdString();
}

template <typename T>
void UnPackageMsg(const std::string& str,T& data,QDataStream::ByteOrder order = QDataStream::LittleEndian)
{
    QByteArray buff = QByteArray::fromStdString(str);
     QDataStream stream(&buff,QIODevice::ReadOnly);
    stream.setVersion(QDataStream::Qt_5_7);
    stream.setByteOrder(order);

    stream >> data;
}

#endif