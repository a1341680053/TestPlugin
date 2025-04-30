#ifndef _PLUGINWIDGET_H
#define _PLUGINWIDGET_H

#include <QMainWindow>

namespace Ui {
class PluginWidget;
}

class PluginsManage;
class PluginCreate;

class PluginWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit PluginWidget(QWidget *parent = nullptr);
    ~PluginWidget();

    void slotActionPlugins(bool b);
    void slotActiionCreatePlugin(bool b);
private:
    Ui::PluginWidget *ui;

    PluginsManage* mpPluginsManage;
    PluginCreate* mpPluginCreate;
};

#endif // PLUGINWIDGET_H
