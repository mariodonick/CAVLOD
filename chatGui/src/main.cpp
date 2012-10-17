#include "ChatGui.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatGui w;
    w.show();
    return a.exec();
}
