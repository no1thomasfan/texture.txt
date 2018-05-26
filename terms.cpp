#include "terms.h"
#include "gui.h"
#include "ui_terms.h"
#include <QButtonGroup>
#include <QPushButton>


Terms::Terms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Terms)
{
    ui->setupUi(this);

    //Load the license
    loadLicenseFile();

    //Make sure the okay button is greyed out. Will enable once the license is agreed.
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    //Load up our settings module.
    mySet  =new Settings;

    //If the user has accepted the terms then they can't unaccept unless they uninstall.
    //Disable the check box and enable the okay button
    if(mySet->isAccepted())
    {
        ui->checkBox->setChecked(true);
        ui->checkBox->setEnabled(false);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }


}

Terms::~Terms()
{
    delete ui;
}


void Terms::on_checkBox_toggled()
{
    //If the agreement check box is indeed checked, enable the okay button.
    //Otherwice the okay button stays disabled.
    if(ui->checkBox->isChecked())
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void Terms::loadLicenseFile()
{
    QFile licenseFile(":/documents/license/gpl3.txt");

    //Resources are READ ONLY.
    licenseFile.open(QIODevice::ReadOnly);

    if(!licenseFile.isOpen())
    {
        qDebug()<<"Internal resource malfunction. Diganosis: Unrecoverable.";
        QCoreApplication::exit(EXIT_FAILURE);
    }
    else
    {
        ui->textBoxLicense->setText(licenseFile.readAll());
    }
}
