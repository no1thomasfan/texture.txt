#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QString>
#include <QStandardPaths>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QTime>
#include <QColor>
#include <QFileInfo>
#include <QIcon>
#include <QSettings>
#include "settings.h"
#include "about.h"


namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = 0);
    QString defaultDirectory;

    ~Gui();

private slots:
    void on_rdoBtn_File_toggled(bool checked);

    void on_rdoBtn_Directory_toggled(bool checked);

    void on_rdoBtn_Def_Settings_toggled(bool checked);

    void on_rdoBtn_Adv_Settings_toggled(bool checked);

    void on_btn_File_Explorer_clicked();

    void on_btn_Generate_clicked();

    void on_btn_File_Explorer_Normal_clicked();

    void on_checkBox_Normal_Enabled_toggled(bool checked);

    void on_checkBox_Normal_Enabled_stateChanged();

    void on_checkBox_Alpha_toggled(bool checked);

    void on_actionSettings_triggered();

    void on_actionTerms_Agreements_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionHelp_triggered();

private:
    void initGui();
    void initSettings();
    About *about;

    Settings *mySet;

    QFileDialog myDialog;

    Ui::Gui *ui;
    QString filepath;
    QString filepath_normal;
    QString outfile;
    bool agreed;

    //Get file name to be written
    QFile file_image;
    QFileInfo file_image_Info;
    QString fileimage;

    //Get file name to be written
    QFile file_normal;
    QFileInfo file_normal_Info;
    QString filename_normal;

    void gen_File();
    void gen_File_Dir();


    //Settings
    QString settingsFile;
    void getSettings();
    void setSettings();
};

#endif // GUI_H
