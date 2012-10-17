#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <crodt.h>
//#include <QtNetwork/QHostInfo>


namespace Ui {
    class ChatGui;
}

class ChatGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatGui(QWidget *parent = 0);
    ~ChatGui();

public slots:
    void buttonClicked();
    void buttonClicked2();
    void buttonClicked3();
    void sliderMoved();

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private:
    Ui::ChatGui *ui;
    QVector<crodt::RelevanceData>vektor;
    QMessageBox msg;
    crodt::SenderModuleIF* sender;
};

#endif // CHATWINDOW_H
