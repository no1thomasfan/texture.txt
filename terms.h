#ifndef TERMS_H
#define TERMS_H

#include "gui.h"
#include "settings.h"
#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class Terms;
}

class Terms : public QDialog
{
    Q_OBJECT

public:
    explicit Terms(QWidget *parent = 0);
    ~Terms();

private slots:
    void on_checkBox_toggled();

private:
    Ui::Terms *ui;
    Settings *mySet;
    void loadLicenseFile();
};

#endif // TERMS_H
