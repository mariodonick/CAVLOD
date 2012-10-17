TEMPLATE = app
TARGET = chatGui
QT += core \
    gui
HEADERS += src/ChatGui.h \
    src/qhostaddress.h \
    src/qhostinfo.h \
    src/qhostaddress.h \
    src/qhostinfo.h
SOURCES += src/ChatGui.cpp \
    src/main.cpp
FORMS += gui/ChatGui.ui
RESOURCES += 
INCLUDEPATH += "extLib/Crodt/include"
LIBS += -LextLib/Crodt/lib/
LIBS += -lcrodt
LIBS += -lboost_program_options
LIBS += -lboost_system
LIBS += -lboost_filesystem
QMAKE_CXXFLAGS += -std=c++0x
