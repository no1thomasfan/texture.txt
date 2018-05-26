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
    //Set the path to our settings.ini file
    settingsFile = QApplication::applicationDirPath() + "/settings.ini";

    //Load up our new settings prior to the gui
    loadSettings();

    ui->setupUi(this);

    //Once the gui is created set the path text to be the user's saved path
    ui->textEdit_DefDir->setText(getDefDir());
}

Settings::~Settings()
{
    delete ui;
}


void Settings::loadSettings()
{
    //Create qsettings object to handle our settings. Format is set to INI
    QSettings settings(settingsFile, QSettings::IniFormat);

    //Read in respective settings
    defaultDirectory = settings.value("Trainz-Editing-Directory", "").toString();
    terms = settings.value("Terms-Accepted", "false").toBool();

    //Sync the changes
    settings.sync();
}

void Settings::saveSettings()
{
    //Create qsettings object to handle our settings. Format is set to INI
    QSettings settings(settingsFile, QSettings::IniFormat);

    //Write the respective settings
    defaultDirectory = ui->textEdit_DefDir->toPlainText();
    settings.setValue("Trainz-Editing-Directory", defaultDirectory);

    //Sync the changes to formally write them.
    settings.sync();
}

//Return the editing directory
QString Settings::getDefDir()
{
    loadSettings();
    return defaultDirectory;
}

//Returns true false if terms accepted
bool Settings::isAccepted()
{
    loadSettings();
    return terms;
}

//Marks terms accepted
void Settings::setAccepted(bool temp)
{
    terms=temp;
    saveSettings();
}


void Settings::on_buttonBox_accepted()
{
    saveSettings();
}

//if user clicks browse, then show them a bfile browser
void Settings::on_btnFileBrowser_clicked()
{
    ui->textEdit_DefDir->setText(QFileDialog::getExistingDirectory());
}
