#include "ChatGui.h"
#include "../ui_ChatGui.h"
#include <QApplication>
#include <QKeyEvent>
#include "qhostinfo.h"
#include <QDir>
#include <QErrorMessage>
//#include <QxtConfirmationMessage>


ChatGui::ChatGui(QWidget *parent):QMainWindow(parent),ui(new Ui::ChatGui)
, sender(new crodt::SenderModule)
{
    ui->setupUi(this);
    ui->textEdit->setFocusPolicy(Qt::NoFocus);
    ui->pushButton->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_2->setFocusPolicy(Qt::NoFocus);

    connect( ui->pushButton, SIGNAL( clicked() ), this, SLOT( buttonClicked() ) );
    connect( ui->pushButton_2, SIGNAL( clicked() ), this, SLOT( buttonClicked2() ) );
    connect( ui->pushButton_3, SIGNAL( clicked() ), this, SLOT( buttonClicked3() ) );
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),ui->lcdNumber, SLOT(display(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),this, SLOT(sliderMoved()));
    ui->label->setText("low prio");
    QPalette* palette = new QPalette();
    palette->setColor(QPalette::WindowText,Qt::black);
    ui->label->setPalette(*palette);

    sender->initialize();
}

void ChatGui::sliderMoved(){
    if(ui->horizontalSlider->value()<30){
        ui->label->setText("low prio");
        QPalette* palette = new QPalette();
        palette->setColor(QPalette::WindowText,Qt::black);
        ui->label->setPalette(*palette);
    }
    if((ui->horizontalSlider->value()>30)&&(ui->horizontalSlider->value()<60)){
        ui->label->setText("mid prio");
        QPalette* palette = new QPalette();
        palette->setColor(QPalette::WindowText,Qt::darkYellow);
        ui->label->setPalette(*palette);
    }
    if((ui->horizontalSlider->value()>60)&&(ui->horizontalSlider->value()<101)){
        ui->label->setText("high prio");
        QPalette* palette = new QPalette();
        palette->setColor(QPalette::WindowText,Qt::red);
        ui->label->setPalette(*palette);
    }
}



void ChatGui::buttonClicked(){
    crodt::RelevanceData tmp;

    tmp.relevanceValue = ui->horizontalSlider->value();
    tmp.pos.x = ui->textEdit_2->textCursor().selectionStart();
    tmp.pos.y = 0;
    tmp.pos.len_x = ui->textEdit_2->textCursor().selectedText().size();

    vektor.push_back(tmp);

    if(ui->textEdit_2->textCursor().selectedText().isEmpty())
        return;
    else{
        QString var_text = ui->textEdit_2->textCursor().selectedText();
        int var_int = ui->horizontalSlider->value();
        QString var_zahl;
        var_zahl.setNum(var_int);
        QString var_ges = var_zahl + " " + var_text;
        ui->listWidget->addItem(var_ges);

        QString bam = ui->textEdit_2->textCursor().selectedText();
        ui->textEdit_2->setTextColor(QColor("red"));
        ui->textEdit_2->textCursor().insertText(bam);
        ui->textEdit_2->setTextColor(QColor("black"));
        ui->horizontalSlider->setValue(0);
    }

    for(QVector<crodt::RelevanceData>::iterator it = vektor.begin(); it != vektor.end(); it++)
    {
      std::cout << *it << "\n";
      std::cout.flush();
    }
}

void ChatGui::buttonClicked2(){
    if(ui->listWidget->selectedItems().isEmpty()){
        QMessageBox msg;
        msg.setText("Bitte erst das zu loeschende Element in der Liste (oben rechts) markieren.");
        msg.exec();
    }
    else{
        delete ui->listWidget->currentItem();
    }
}

void ChatGui::buttonClicked3(){

    QString text = ui->textEdit_2->toPlainText();
    if(text.isEmpty())
        return;

    QString user;
    user = QDir::homePath();
    QString user_fin = user.mid(6,30);
    user_fin = user_fin + ":";

    QString text_ges = user_fin + " " + text;

    int ret;

    if(ui->listWidget->count()==0){
        QMessageBox msgBox;
        //QErrorMessage msgBox;
        msgBox.setText("Achtung!");
        msgBox.setInformativeText("Wollen sie wirklich senden ohne zuvor eine Prioritaet festzulegen?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
        msgBox.setDefaultButton(QMessageBox::No);
        ret = msgBox.exec();
    }
    else
        ret=QMessageBox::Yes;

    if(ret==QMessageBox::Yes){

        ui->textEdit->setTextColor(QColor("red"));
        ui->textEdit->append(user_fin);
        ui->textEdit->setTextColor(QColor("black"));
        ui->textEdit->append(text);

        crodt::CrodtInput out;
        out.content =  ui->textEdit_2->toPlainText().toStdString();
        out.is_timestamp = ui->checkBox->isChecked();
        out.relevanceVector = vektor.toStdVector();
        vektor.clear();

        sender->sendText(out);
        ui->textEdit_2->clear();
        ui->listWidget->clear();
    }
}

void ChatGui::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Return){

    }
}

void ChatGui::keyReleaseEvent(QKeyEvent *){

}

ChatGui::~ChatGui(){
    delete ui;
}
