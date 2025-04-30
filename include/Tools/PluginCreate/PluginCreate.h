#ifndef PLUGINCREATE_H
#define PLUGINCREATE_H

#include <QWidget>
#include "PluginCreate/PluginCreate_global.h"

namespace Ui {
class PluginCreate;
}

class PLUGINCREATE_EXPORT PluginCreate : public QWidget
{
    Q_OBJECT

public:
    explicit PluginCreate(QWidget *parent = nullptr);
    ~PluginCreate();

    void init();

private:
    void slotSetPluginPath();

    void slotOkClicked();

    void slotCancelClicked();

    void createPluginFile(const QString& path,const QString& name,const QString& tempFile,const QString& fileName);
    
    void createPluginJson(const QString &path);
private:
    Ui::PluginCreate *ui;
    //用于替换的文件路径
    QString mTempData;
};

#endif // PLUGINCREATE_H
