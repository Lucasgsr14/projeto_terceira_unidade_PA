#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  

public slots:
  void putData();
  /**
   * @brief tcpConnect método usado para se conectar com o server
   */
  void tcpConnect();
  /**
   * @brief tcpDisconnect método usado para se desconectar com o server
   */
  void tcpDisconnect();
  /**
   * @brief deslocaSlider método usado para movimentar o slider do mínimo caso o slider máximo tente ser menor que o mínimo
   */
  void deslocaSlider();
  /**
   * @brief impedeMaiorMenor método usado para deslocar o slider máximo para ser sempre maior ou igual o mínimo
   */
  void impedeMaiorMenor();
  /**
   * @brief stopData método usado para parar de enviar os dados, ou seja, mata o temporizador.
   */
  void stopData();
  /**
   * @brief timerEvent para enviar os dados de acordo com a quantidade de milissegundos fornecidos pelo usuário
   * @param e
   */
  void timerEvent(QTimerEvent *e);
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  int idTimer;
};

#endif // MAINWINDOW_H
