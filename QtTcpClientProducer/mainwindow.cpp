#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
//#include <cstring>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  tcpConnect();
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
          SIGNAL(clicked(bool)),
          this,
          SLOT(putData()));
  connect(ui->pushButtonStop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(stopData()));


}

void MainWindow::tcpConnect(){
  QString ip = ui->lineEditIP->text();
  socket->connectToHost(ip, 1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
    qDebug() << ui->labelToChange->textFormat();
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
    if(ui->horizontalSliderMin->sliderPosition() >= ui->horizontalSliderMax->sliderPosition()){
        ui->horizontalSliderMax->setSliderPosition(ui->horizontalSliderMin->sliderPosition());
    }
}

void MainWindow::impedeMaiorMenor(){
    if(ui->horizontalSliderMax->sliderPosition() < ui->horizontalSliderMin->sliderPosition()){
        ui->horizontalSliderMin->setSliderPosition(ui->horizontalSliderMax->sliderPosition());
    }
}

void MainWindow::stopData(){
    killTimer(idTimer);
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
    ui->horizontalSliderTimming->setEnabled(true);
}

void MainWindow::putData(){
        QString timeStr;
        idTimer = startTimer((ui->lcdNumberTimming->intValue())*1000);
        ui->pushButtonStart->setEnabled(false);
        ui->pushButtonStop->setEnabled(true);
        ui->horizontalSliderTimming->setEnabled(false);
}

void MainWindow::timerEvent(QTimerEvent *e){
    QString str;
    int max,min;
    qint64 msecdate;

    min=ui->horizontalSliderMin->sliderPosition();
    max=ui->horizontalSliderMax->sliderPosition();
    if(socket->state()== QAbstractSocket::ConnectedState){
        msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
        qsrand(msecdate);
        str = "set "+ QString::number(msecdate) + " " + QString::number(qrand()%(max - min) + min)+"\r\n";
        ui->textBrowser->append(str);

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
