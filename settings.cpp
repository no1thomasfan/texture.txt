#include "settings.h"
#include "ui_settings.h"
#include <QSettings>
#include <QStandardPaths>
#include <QFileDialog>
//#include <QDebug>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    settingsFile = QApplication::applicationDirPath() + "/settings.ini";
    loadSettings();
    ui->setupUi(this);
    ui->textEdit_DefDir->setText(getDefDir());
}

Settings::~Settings()
{
    delete ui;
}


void Settings::loadSettings()
{
    QSettings settings(settingsFile, QSettings::IniFormat);
    defaultDirectory = settings.value("Trainz-Editing-Directory", "").toString();
    terms = settings.value("Terms-Accepted", "false").toBool();
    settings.sync();
}

void Settings::saveSettings()
{
    QSettings settings(settingsFile, QSettings::IniFormat);
    defaultDirectory = ui->textEdit_DefDir->toPlainText();
    settings.setValue("Trainz-Editing-Directory", defaultDirectory);
    settings.setValue("Terms-Accepted",terms);
    settings.sync();
}

QString Settings::getDefDir()
{
    loadSettings();
    return defaultDirectory;
}

bool Settings::isAccepted()
{
    loadSettings();
    return terms;
}

void Settings::setAccepted(bool temp)
{
    terms=temp;
    saveSettings();
}

void Settings::on_buttonBox_accepted()
{
}

void Settings::on_pushButton_clicked()
{
    saveSettings();
}

void Settings::on_pushButton_2_clicked()
{


    ui->textEdit_DefDir->setText(QFileDialog::getExistingDirectory());
}
