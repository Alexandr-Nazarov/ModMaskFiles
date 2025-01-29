#include "modmaskfile.h"

#include <QApplication>
//#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ModMaskFile w;
    w.show();
    return a.exec();
}
