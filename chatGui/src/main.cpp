#include <QtGui/QApplication>
#include "ChatGui.h"

#include <string>
#include <iostream>
#include "UniversalDecoder.h"
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChatGui w;
    w.setMinimumSize(1061,428);
    w.setMaximumSize(1061,428);
    w.setFixedSize(1061,428);

    w.show();
    return a.exec();

//    UniversalDecoder<std::string> decoder;
//    decoder.decode(0,0,"a");
//    decoder.decode(0,1,"b");
//    decoder.decode(0,2,"c");
//    decoder.decode(0,3,"d");
//    decoder.decode(0,4,"e");
//    decoder.decode(0,5,"f");
//    decoder.decode(0,6,"g");
//    decoder.decode(0,7,"h");
//
//    decoder.decode(1,0,"i");
//    decoder.decode(1,1,"j");
//    decoder.decode(1,2,"k");
//    decoder.decode(1,3,"l");
//    decoder.decode(1,4,"m");
//    decoder.decode(1,5,"n");
//    decoder.decode(1,6,"o");
//    decoder.decode(1,7,"p");
//
//    decoder.dump(std::cout);
//
//    std::string tmp;
//    UniversalDecoder<std::string>::StdVec2D::const_iterator outer = decoder.getSortedContent().begin();
//    for(; outer != decoder.getSortedContent().end(); ++outer)
//    {
//      UniversalDecoder<std::string>::StdVec1D::const_iterator inner = outer->begin();
//      for(;inner != outer->end(); ++inner)
//      {
//        tmp.append(*inner);
////        tmp.append( QString::fromStdString( *inner ) );
//      }
//      tmp.append("\n");
//    }
//
//    QString t;
//    t = QString::fromStdString(tmp);
//    qDebug() << t;
}
