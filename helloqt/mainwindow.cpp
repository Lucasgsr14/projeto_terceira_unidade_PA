#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    //conecta um objeto que envia um sinal, um sinal, o ponteiro pro objeto que recebe o sinal e o nome da função que vai tratar o sinal
    connect(ui->pushButtonQuit,
            SIGNAL(clicked(bool)),
            this,//ponteiro para o objeto que vai receber a comunicação de sinal (no casa o objeto main window)
            SLOT(mataTudo()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mataTudo(){
    exit(0);
}

void MainWindow::copiaTexto(){
    ui->textBrowser->setText(ui->textEdit->toPlainText());
}
