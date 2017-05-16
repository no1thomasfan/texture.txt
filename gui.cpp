#include "terms.h"
#include "gui.h"
#include "ui_gui.h"
#include "settings.h"
#include "about.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QTime>
#include <QColor>
#include <QDesktopServices>


Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
    about = new About(this);

    mySet=new Settings;

    //Get Settings
    initSettings();

    //Check the Terms and Conditions
    if(agreed==false)
    {
        //Instantiate the terms and agreements
        Terms term;
        if(term.exec() == QDialog::Rejected)
        {
            qDebug() << "You pressed CANCEL!";
            exit(EXIT_FAILURE);
        }

        //User Sets initial settings
        on_actionSettings_triggered();
    }

    mySet->setAccepted(true);

    //Setup the gui
    initGui();
}

Gui::~Gui()
{
    delete ui;
}

//Get Basic Settings
void Gui::initSettings()
{
    defaultDirectory=mySet->getDefDir();
    agreed=mySet->isAccepted();
}

//Set basic gui parameters and states
void Gui::initGui()
{
    //Set default states on load
    ui->rdoBtn_File->setChecked(true);
    ui->rdoBtn_Def_Settings->setChecked(true);
    ui->btn_File_Explorer_Normal->setEnabled(false);
    ui->checkBox_Flip_Green->setEnabled(false);
    ui->plainTxt_Normal->setEnabled(false);
    ui->comboBox_Alpha->setEnabled(false);

    //Set File paths
    myDialog.setDirectory(defaultDirectory);
    filepath=QString(QStandardPaths::HomeLocation);
    filepath_normal=QString(QStandardPaths::HomeLocation);
    ui->console->append(QTime::currentTime().toString() + ":  " + "Ready!");
}


/*************************************
 *
 *
 ************** Menu Bar **************
 *
 *
 *************************************/

void Gui::on_actionSettings_triggered()
{
    mySet->exec();
    defaultDirectory=mySet->getDefDir();
}

void Gui::on_actionQuit_triggered()
{
    exit(EXIT_SUCCESS);
}

void Gui::on_actionTerms_Agreements_triggered()
{
    Terms term;
    term.exec();
}


/*************************************
 *
 *
 ******* Radio Button Handling********
 *
 *
 *************************************/

void Gui::on_rdoBtn_File_toggled(bool checked)
{
    if(checked==true)
    {
        ui->rdoBtn_Directory->setChecked(false);
        ui->rdoBtn_Def_Settings->setEnabled(true);
        ui->rdoBtn_Adv_Settings->setEnabled(true);
        if((ui->rdoBtn_Def_Settings->isChecked()))
        {
            ui->groupBox_Settings->setEnabled(false);
        }
        else
        {
            ui->groupBox_Settings->setEnabled(true);
        }
    }

}

void Gui::on_rdoBtn_Directory_toggled(bool checked)
{
    if(checked == true)
    {
        ui->rdoBtn_Directory->setChecked(false);
        ui->rdoBtn_Def_Settings->setEnabled(false);
        ui->rdoBtn_Adv_Settings->setEnabled(false);
        ui->groupBox_Settings->setEnabled(false);
    }
}

void Gui::on_rdoBtn_Def_Settings_toggled(bool checked)
{
    if(checked == true)
    {
        ui->rdoBtn_Adv_Settings->setChecked(false);
        ui->groupBox_Settings->setEnabled(false);
    }
}

void Gui::on_rdoBtn_Adv_Settings_toggled(bool checked)
{
    if(checked == true)
    {
        ui->rdoBtn_Def_Settings->setChecked(false);
        ui->groupBox_Settings->setEnabled(true);
    }
}


/*************************************
 *
 *
 ****** File/Dir Load Handling *******
 *
 *
 *************************************/

void Gui::on_btn_File_Explorer_clicked()
{

    if(ui->rdoBtn_File->isChecked())
    {
        filepath = myDialog.getOpenFileName(this,tr("Open Image"),defaultDirectory,tr("*.bmp *.jpg *.tga"));
        ui->plainTxt_directorypath->setPlainText(filepath);
    }
    else
    {
        filepath = myDialog.getExistingDirectory();
        ui->plainTxt_directorypath->setPlainText(filepath);
    }
}

void Gui::on_btn_File_Explorer_Normal_clicked()
{
    filepath_normal = QFileDialog::getOpenFileName();
    ui->plainTxt_Normal->setPlainText(filepath);
}

/*************************************
 *
 *
 ********* File Generation **********
 *
 *
 *************************************/

void Gui::on_btn_Generate_clicked()
{
    if(ui->rdoBtn_File->isChecked())
    {
        gen_File();
    }
    else
    {
        gen_File_Dir();
    }
}

void Gui::gen_File()
{
    try{
        //Open initial file to get required information
        QFile original(filepath);
        QFileInfo file_Name(original);

        //Get the file name and file path
        QString fileimage(file_Name.fileName());
        QString outPath(file_Name.filePath());

        //Generate file name without its extension
        outfile = fileimage.split(".",QString::SkipEmptyParts).at(0);

        outPath = outPath.split(fileimage,QString::SkipEmptyParts).at(0);

        //add the new extension to the name of the out file
        outfile = outfile.append(".texture.txt");

        //open/create the new file
        QFile file(outPath+outfile);

        //close the original file we opened
        original.close();

        qDebug()<< "\n\n"<<outfile;
        qDebug()<< "\n\n"<<outPath;

        if (file.open(QIODevice::ReadWrite))
        {
            //Create IO stream to write to the file then Write the settings to the file
            QTextStream stream(&file);

            //Image File name:
            stream << "Primary="<< fileimage<< "\r\n" <<endl;

            //Write the tiling settings:
            if(ui->rdoBtn_Def_Settings->isChecked() || ui->rdoBtn_Directory->isChecked())
            {
                stream<< "Tile=st \r\n"<<endl;
            }
            else
            {
                if(ui->comboBox_Tiling->currentIndex()==0)
                {
                    stream<< "Tile=none \r\n"<<endl;
                }

                else if(ui->comboBox_Tiling->currentIndex()==1)
                {
                    stream<< "Tile=s \r\n"<<endl;
                }
                else if(ui->comboBox_Tiling->currentIndex()==2)
                {
                    stream<< "Tile=s \r\n"<<endl;
                }
                else
                {
                    stream<< "Tile=st \r\n"<<endl;
                }
            }

            //Write Alpha Settings:
            if(ui->rdoBtn_Adv_Settings->isChecked() && ui->rdoBtn_File->isChecked())
            {
                if(ui->checkBox_Alpha->isChecked())
                {
                    stream<< "Alpha=" + fileimage +"\r\n"<<endl;

                    if(ui->comboBox_Alpha->currentIndex()==0)
                    {
                        stream<< "AlphaHint=none \r\n"<<endl;
                    }

                    else if(ui->comboBox_Alpha->currentIndex()==1)
                    {
                        stream<< "AlphaHint=Opaque \r\n"<<endl;
                    }
                    else if(ui->comboBox_Alpha->currentIndex()==2)
                    {
                        stream<< "AlphaHint=semitransparent \r\n"<<endl;
                    }
                    else if(ui->comboBox_Alpha->currentIndex()==3)
                    {
                        stream<< "AlphaHint=masked \r\n"<<endl;
                    }
                }
            }

            //Write Normal-Map Settings:
            if(ui->rdoBtn_Adv_Settings->isChecked() && ui->rdoBtn_File->isChecked())
            {
                if(ui->checkBox_Normal_Enabled->isChecked())
                {

                    //Get file name to be written
                    QFile file_normal(filepath_normal);
                    QFileInfo file_Normal_Info(file_normal);
                    QString filename_normal(file_Normal_Info.fileName());
                    file_normal.close();

                    //Write normalmapFileName
                    stream<< "NormalMapHint=" + filename_normal +"\r\n"<<endl;

                    if(ui->checkBox_Flip_Green)
                    {
                        stream<< "ModifyMap=flipgreen \r\n"<<endl;
                    }
                }
            }


            //Close The file
            file.close();


            //Write to the console that the file was created.
            ui->console->append(QTime::currentTime().toString() + ":  " + "Created: " + outfile);
        }
        else
        {
            ui->console->setTextColor(QColor("red"));
            ui->console->append(QTime::currentTime().toString()  + ":  " + "Error creating " + outfile + " ! Make sure you have sufficient privlages!");
            ui->console->setTextColor(QColor("black"));
            file.close();
        }
    }
    catch(...)
    {
        qDebug()<<"Error! Cannot lock file or directory for writing.";
    }
}

void Gui::gen_File_Dir()
{

    QStringList filters;
    QDir dir(filepath);
    filters << "*.png" << "*.jpg" << "*.bmp" << "*.tga";
    QFileInfoList fileInfoList = dir.entryInfoList(filters, QDir::Files|QDir::NoDotAndDotDot);

    for(int i=0;i<fileInfoList.length();i++)
    {
        filepath=fileInfoList.value(i).filePath();
        qDebug() << fileInfoList.value(i).fileName();
        gen_File();
    }

    ui->console->append("");
    ui->console->append(QTime::currentTime().toString()  + ":  " +"Done processing directory!");
    ui->console->append("");
}



void Gui::on_checkBox_Normal_Enabled_toggled(bool checked)
{
    if(checked)
    {
        ui->btn_File_Explorer_Normal->setEnabled(true);
        ui->checkBox_Flip_Green->setEnabled(true);
        ui->plainTxt_Normal->setEnabled(true);
    }
    else
    {
        ui->btn_File_Explorer_Normal->setEnabled(false);
        ui->checkBox_Flip_Green->setEnabled(false);
        ui->plainTxt_Normal->setEnabled(false);
    }
}

void Gui::on_checkBox_Normal_Enabled_stateChanged()
{
    on_checkBox_Normal_Enabled_toggled(ui->checkBox_Normal_Enabled->isChecked());
}

void Gui::on_checkBox_Alpha_toggled(bool checked)
{
    if(checked)
    {
        ui->comboBox_Alpha->setEnabled(true);
    }
    else
    {
        ui->comboBox_Alpha->setEnabled(false);
    }
}





void Gui::on_actionAbout_triggered()
{
    about->show();
}

void Gui::on_actionHelp_triggered()
{
    QString link = "http://si3d.proboards.com/post/121466/thread";
    QDesktopServices::openUrl(QUrl(link));
}
