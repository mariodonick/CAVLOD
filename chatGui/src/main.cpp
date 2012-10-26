#include <QtGui/QApplication>
#include "ChatGui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChatGui w;
    w.setMinimumSize(1061,428);
    w.setMaximumSize(1061,428);
    w.setFixedSize(1061,428);
    w.show();
    return a.exec();
}
