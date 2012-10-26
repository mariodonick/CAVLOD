#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QErrorMessage>
#include <crodt.h>

namespace Ui {
    class ChatGui;
}

struct Pack
{
  Pack(){}
  virtual ~Pack(){}

  QString text;
  uint x; // column
  uint y; // line
  uint len_x;
  uint doid;
};

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
    void receive();
    void refresh(Pack p);
    void incoming(const crodt::CrodtOutput<std::string>& out);

signals:
  void receive(Pack p);

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

private:
    Ui::ChatGui *ui;
    QVector<crodt::RelevanceData>vektor;
    QMessageBox msg;
    QErrorMessage errorMessage;
    crodt::SenderModuleIF* sender;
    crodt::ReceiverModuleIF* receiver;
    int ret;
    int zeilenschub;
    std::vector<Pack> textVec;
};

#endif // CHATWINDOW_H
