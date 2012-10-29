#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QErrorMessage>
#include <crodt.h>
#include "UniversalDecoder.h"

namespace Ui {
    class ChatGui;
}

class ChatGui : public QMainWindow
{
  Q_OBJECT

  typedef UniversalDecoder<std::string> TextDecoder;

public:
  explicit ChatGui(QWidget *parent = 0);
  virtual ~ChatGui();

public slots:
  void buttonClicked();
  void buttonClicked2();
  void buttonClicked3();
  void sliderMoved();
  void refresh();
  void incoming(const crodt::CrodtOutput<std::string>& out);

signals:
  void received();

protected:
  void keyPressEvent(QKeyEvent *);
  void keyReleaseEvent(QKeyEvent *);

private:
  Ui::ChatGui *ui;

  crodt::SenderModuleIF* sender;
  crodt::ReceiverModuleIF* receiver;

  int ret;

  QVector<crodt::RelevanceData>vektor;
  QMessageBox msg;
  QErrorMessage errorMessage;

  TextDecoder decoder;
};

#endif // CHATWINDOW_H
