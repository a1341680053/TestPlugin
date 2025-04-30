#ifndef PLUGINSMANAGE_H
#define PLUGINSMANAGE_H

#include <QDialog>

namespace Ui {
class PluginsManage;
}

class PluginsManage : public QDialog
{
    Q_OBJECT

public:
    explicit PluginsManage(QWidget *parent = nullptr);
    ~PluginsManage();

private:
    void init();
private:
    Ui::PluginsManage *ui;
};

#endif // PLUGINSMANAGE_H
