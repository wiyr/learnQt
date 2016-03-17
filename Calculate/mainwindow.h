#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

enum OP {
    addOp,
    subOp,
    mulOp,
    divOp,
    nop
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    OP currentOp;
    QString lastNumber, currentNumber;
    bool isEmpty;

public slots:
    void Clear();
    void Input();
    void OpChanged();
    void Display();
    void Result();
    void SignChanged();
    void PercentageOnClick();
    void DotOnClick();

    void AboutApp();

};

#endif // MAINWINDOW_H
