#include "settings.h"
#include "ui_settings.h"
#include <QSettings>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDebug>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    //Path to our writable settings directory
    QDir path=QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    //Check that path exists
    if(!path.exists())
    {
        //If not, make it.
        path.mkpath(path.absolutePath());
    }

    //Settings path
    QString temp = QDir::toNativeSeparators(path.absolutePath().append("/settings.ini"));
    qDebug().noquote()<<"Settings Location:\t" + temp;

    //Update the global with the path we made.
    settingsFile = temp;

    //Load up our new settings prior to the gui
    loadSettings();

    //Setup the gui
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
    settings.setValue("Terms-Accepted", terms);

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
