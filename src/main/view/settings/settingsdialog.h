#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "settingsitem.h"
#include "settingsdialogdelegate.h"
#include <QDialog>
#include <QAbstractButton>
#include <map>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    void setSettingsItem(SettingsItem* settingsItem);
    void setDelegate(SettingsDialogDelegate* delegate);

private:
    Ui::SettingsDialog *ui;
    SettingsItem* settingsItem;
    SettingsDialogDelegate* delegate;

public slots:
    void onAccepted(QAbstractButton* button);
private slots:
    void onListWidgetClicked(const QModelIndex &index);
};

#endif // SETTINGSDIALOG_H