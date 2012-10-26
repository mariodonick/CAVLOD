#include "ChatGui.h"
#include "../ui_ChatGui.h"
#include <QApplication>
#include <QKeyEvent>
#include "qhostinfo.h"
#include <QDir>
#include <QErrorMessage>
#include <QKeySequence>
#include <QShortcut>


ChatGui::ChatGui(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::ChatGui)
, sender(new crodt::SenderModule())
, receiver(new crodt::ReceiverModule)
, ret(0)
{
    qRegisterMetaType<Pack>("Pack");
    ui->setupUi(this);
    ui->textEdit->setFocusPolicy(Qt::NoFocus);
    ui->pushButton->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_2->setFocusPolicy(Qt::NoFocus);

    connect( ui->pushButton, SIGNAL( clicked() ), this, SLOT( buttonClicked() ) );
    connect( ui->pushButton_2, SIGNAL( clicked() ), this, SLOT( buttonClicked2() ) );
    connect( ui->pushButton_3, SIGNAL( clicked() ), this, SLOT( buttonClicked3() ) );
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),ui->lcdNumber, SLOT(display(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),this, SLOT(sliderMoved()));

    connect( this, SIGNAL( receive(Pack) ), this, SLOT( refresh(Pack) ) );

    ui->pushButton_3->setShortcut(QKeySequence("Alt+S"));
    ui->pushButton_2->setShortcut(QKeySequence("Alt+D"));
    ui->pushButton->setShortcut(QKeySequence("Alt+A"));

    ui->label->setText("niedrig");
    QPalette* palette = new QPalette();
    palette->setColor(QPalette::WindowText,Qt::black);
    ui->label->setPalette(*palette);

    ui->textEdit_2->setFocus();

    // register callback
    using namespace std::placeholders;
    crodt::TextCallback func = std::bind(&ChatGui::incoming, this, _1);
    receiver->registerCallback( func );
    receiver->start();
}

// double signal slot method because multi-threading
void ChatGui::incoming(const crodt::CrodtOutput<std::string>& out)
{
  Pack p;
  p.text = QString::fromStdString(out.sortedContent.content);
  p.x = out.sortedContent.pos.x;
  p.y = out.sortedContent.pos.y;
  p.len_x = out.sortedContent.pos.len_x;
  p.doid = out.sortedContent.doid;
  p.sequenceNumber = out.sortedContent.sequenceNumber;

  qDebug() << "text: " << p.text;
  qDebug() << "x: " << p.x;
  qDebug() << "y: " << p.y;
  qDebug() << "len: " << p.len_x;
  qDebug() << "doid: " << p.doid;
  qDebug() << "sequnr: " << p.sequenceNumber;

  decoder.decode(out.sortedContent.doid,
                 out.sortedContent.sequenceNumber,
                 out.sortedContent.content);
  emit receive(p);
}


void ChatGui::refresh(Pack)
{
  ui->textEdit_3->clear();
//  textVec.push_back(p);

  QString tmp;
//  std::vector<std:.string>::iterator prev = textVec.begin();
  for(std::vector<std::string>::const_iterator it = decoder.getSortedContent().begin();
      it != decoder.getSortedContent().end(); ++it)
  {
    tmp.append( QString::fromStdString( *it ) );

  }

  ui->textEdit_3->append(tmp);
}

void ChatGui::sliderMoved(){
    if(ui->horizontalSlider->value()<30){
        ui->label->setText("niedrig");
        QPalette* palette = new QPalette();
        palette->setColor(QPalette::WindowText,Qt::black);
        ui->label->setPalette(*palette);
    }
    if((ui->horizontalSlider->value()>30)&&(ui->horizontalSlider->value()<60)){
        ui->label->setText("mittel");
        QPalette* palette = new QPalette();
        palette->setColor(QPalette::WindowText,Qt::darkYellow);
        ui->label->setPalette(*palette);
    }
    if((ui->horizontalSlider->value()>60)&&(ui->horizontalSlider->value()<101)){
        ui->label->setText("hoch");
        QPalette* palette = new QPalette();
        palette->setColor(QPalette::WindowText,Qt::red);
        ui->label->setPalette(*palette);
    }
}


void ChatGui::buttonClicked(){
    if(ui->textEdit_2->textCursor().selectedText().isEmpty()){
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Bitte zuvor die zu priorisierende Textpassage markieren.");
        msg.exec();

    }
    ret = 1;

    crodt::RelevanceData tmp;

    tmp.relevanceValue = ui->horizontalSlider->value();
    tmp.pos.x = ui->textEdit_2->textCursor().selectionStart();
    tmp.pos.y = 0; //bei neuer Nachricht counter hochzählen !!!
    tmp.pos.len_x = ui->textEdit_2->textCursor().selectedText().size();

    vektor.push_back(tmp);

    if(ui->textEdit_2->textCursor().selectedText().isEmpty())
        return;
    else{
        QString var_text = ui->textEdit_2->textCursor().selectedText();
        int var_int = ui->horizontalSlider->value();
        QString var_zahl;
        var_zahl.setNum(var_int);

        int laenge = var_zahl.length();
        if(laenge == 1)
            var_zahl = "00"+var_zahl;
        if(laenge == 2)
            var_zahl = "0"+var_zahl;
        if(laenge == 3)
            var_zahl = ""+var_zahl;

        QString var_ges = var_zahl + " " + var_text;
        ui->listWidget->addItem(var_ges);

        QString bam = ui->textEdit_2->textCursor().selectedText();
        ui->textEdit_2->setTextColor(QColor("red"));
        ui->textEdit_2->textCursor().insertText(bam);
        ui->textEdit_2->setTextColor(QColor("black"));
        ui->horizontalSlider->setValue(0);
        ui->listWidget->sortItems(Qt::AscendingOrder);
    }

}

void ChatGui::buttonClicked2()
{
    if(ui->listWidget->selectedItems().isEmpty()){
        QMessageBox msg;
        msg.setIcon(QMessageBox::Information);
        msg.setText("Bitte erst das zu l"+trUtf8("ö")+"schende Element in der Liste (oben rechts) markieren.");
        msg.exec();
    }
    else{
        delete ui->listWidget->currentItem();
    }

}



void ChatGui::buttonClicked3(){
    if(ui->textEdit_2->toPlainText().isEmpty())
    {
//        QMessageBox msg;
//        msg.setIcon(QMessageBox::Information);
//        msg.setText("Eingabefeld ist leer!");
//        msg.exec();
        return;
    }

    QString text = ui->textEdit_2->toPlainText();
    qDebug()<<ui->textEdit_2->toPlainText();
    if(text.isEmpty())
        return;

    int var_n;
    QString user;
    user = QDir::homePath();

    QString path_users = user.mid(0,6);
    QString path_home = user.mid(0,5);

    if(path_home == "/home")
         var_n = 6;
    if(path_users == "/Users")
         var_n = 7;

    QString user_fin = user.mid(var_n,30);

    user_fin = user_fin + ":";

    QString text_ges = user_fin + " " + text;

    if(ui->listWidget->count()==0){

        errorMessage.showMessage("Fortfahren ohne eine Priorit"+trUtf8("ä")+"t zuzuweisen ?");

        if(errorMessage.isVisible()==true){
            QEventLoop loop;
            connect(&errorMessage, SIGNAL(accepted()), &loop, SLOT(quit()));
            connect(&errorMessage, SIGNAL(rejected()), &loop, SLOT(quit()));
            errorMessage.isActiveWindow()==true;
            loop.quit();
            loop.exec();
        }

        if(errorMessage.result()==1)
            ret=1;
        if(errorMessage.result()==0)
            ret=0;

    }

    if(ret==1){

        ui->textEdit->setTextColor(QColor("red"));
        ui->textEdit->append(user_fin);
        ui->textEdit->setTextColor(QColor("black"));
        ui->textEdit->append(text);

        for(int i = 0; i<vektor.size();i++)
            std::cout<<vektor[i]<<"\n";

        crodt::CrodtInput out;
        out.content =  ui->textEdit_2->toPlainText().toStdString();
        out.is_timestamp = ui->checkBox->isChecked();
        out.relevanceVector = vektor.toStdVector();
        vektor.clear();

        sender->sendText(out);
        ui->textEdit_2->clear();
        ui->listWidget->clear();
        ret = 0;
    }
    else
        return;
}

void ChatGui::receive(){
    QString data_string;
    uint data_start = 0;
    uint data_size = 0;
//    int64_t timestamp = 0;

    QTextCursor c = ui->textEdit->textCursor();
    c.setPosition(data_start);
    c.setPosition(data_start+data_size, QTextCursor::KeepAnchor);
    ui->textEdit->setTextCursor(c);
    ui->textEdit->textCursor().insertText(data_string);
}


void ChatGui::keyPressEvent(QKeyEvent *){

}


void ChatGui::keyReleaseEvent(QKeyEvent *){

}

ChatGui::~ChatGui(){
    delete ui;
}
