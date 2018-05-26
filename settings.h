#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    void loadSettings();
    void saveSettings();
    QString getDefDir();
    bool isAccepted();
    void setAccepted(bool);

    explicit Settings(QWidget *parent = 0 );
    QString settingsFile;
    ~Settings();

private slots:
    void on_buttonBox_accepted();

    void on_btnFileBrowser_clicked();

private:
    Ui::Settings *ui;
    QString defaultDirectory;

    bool terms;

};

#endif // SETTINGS_H
