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
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

Terms::~Terms()
{
    delete ui;
}


void Terms::on_checkBox_toggled()
{
    if(ui->checkBox->isChecked())
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}
