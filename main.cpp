#include "gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("no1tfm");
    a.setApplicationName("textureTxtGenerator");
        Gui w;
        w.show();


    return a.exec();
}
