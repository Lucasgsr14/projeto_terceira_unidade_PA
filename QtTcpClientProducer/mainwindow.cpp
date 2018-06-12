#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
//#include <cstring>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  tcpConnect();

  //connect(ui->pushButtonPut,
  //        SIGNAL(clicked(bool)),
  //        this,
  //        SLOT(putData()));
  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpConnect()));
  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpDisconnect()));
  connect(ui->horizontalSliderMin,
          SIGNAL(sliderMoved(int)),
          this,
          SLOT(deslocaSlider()));
  connect(ui->horizontalSliderMax,
          SIGNAL(sliderMoved(int)),
          this,
          SLOT(impedeMaiorMenor()));
  connect(ui->pushButtonStart,
          SIGNAL(toggled(bool)),
          this,
          SLOT(putData()));
  connect(ui->pushButtonStop,
          SIGNAL(toggled(bool)),
          this,
          SLOT(mudaStatus()));
}

void MainWindow::tcpConnect(){
  QString ip = ui->lineEditIP->text();
  socket->connectToHost(ip, 1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
    ui->labelToChange->setText("Connected");
  }
  else{
    qDebug() << "Disconnected";
    ui->labelToChange->setText("Disconnected");
  }
}

void MainWindow::tcpDisconnect(){
    socket->disconnectFromHost();
    ui->labelToChange->setText("Disconnected");
}

void MainWindow::deslocaSlider(){
    if(ui->horizontalSliderMin->sliderPosition()>=ui->horizontalSliderMax->sliderPosition()){
        ui->horizontalSliderMax->setSliderPosition(ui->horizontalSliderMin->sliderPosition());
    }
}

void MainWindow::impedeMaiorMenor(){
    if(ui->horizontalSliderMax->sliderPosition()<ui->horizontalSliderMin->sliderPosition()){
        ui->horizontalSliderMin->setSliderPosition(ui->horizontalSliderMax->sliderPosition());
    }
}

void MainWindow::mudaStatus(){
   ui->pushButtonStart->setChecked(false);
}

void MainWindow::putData(){
  QDateTime datetime;
  QString str;
  qint64 msecdate;
  qDebug() << ui->pushButtonStart->isChecked();
      if(socket->state()== QAbstractSocket::ConnectedState&&!ui->pushButtonStop->isChecked()){

        msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
        str = "set "+ QString::number(msecdate) + " " + QString::number(qrand()%35)+"\r\n";

          qDebug() << str;
          qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
          if(socket->waitForBytesWritten(3000)){
            qDebug() << "wrote";
          }

  }
}

MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
