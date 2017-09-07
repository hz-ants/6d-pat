#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QtAwesome/QtAwesome.h>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    QtAwesome* awesome = new QtAwesome( qApp );
    awesome->initFontAwesome();
    ui->listWidget->addItem(new QListWidgetItem(awesome->icon(fa::wrench), "General"));
    ui->listWidget->addItem(new QListWidgetItem(awesome->icon(fa::code), "Codes"));
    ui->listWidget->setCurrentItem(ui->listWidget->item(0));

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setSettingsItem(SettingsItem* settingsItem) {
    //! copy settings item, we don't want the settings item to be modified if we cancel the settings dialog
    this->settingsItem = new SettingsItem(*settingsItem);
    ui->pageGeneral->setSettingsItem(this->settingsItem);
}

void SettingsDialog::setDelegate(SettingsDialogDelegate* delegate) {
    this->delegate = delegate;
}

//! The weird connection in the UI file of the dialog's method clicked(QAbstractButton)
//! comes from that the dialog somehow doesn't fire its accepted() method...
void SettingsDialog::onAccepted(QAbstractButton* button) {
    if (ui->buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole) {
        this->delegate->applySettings(this->settingsItem);
        close();
    }
}

void SettingsDialog::onListWidgetClicked(const QModelIndex &index)
{
    ui->stackedWidget->setCurrentIndex(index.row());
}
