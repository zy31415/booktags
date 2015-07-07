#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();


private:
    Ui::SettingsDialog *ui;

private slots:
    void on_pushButtonChooseDirectory_clicked();
};

#endif // SETTINGSDIALOG_H
