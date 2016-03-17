#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
// ...

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentOp = nop;

    connect(ui->pushButtonClear,    SIGNAL(clicked(bool)), this,  SLOT(Clear()));
    connect(ui->pushButtonSign,     SIGNAL(clicked(bool)), this,  SLOT(SignChanged()));
    connect(ui->pushButtonAdd,      SIGNAL(clicked(bool)), this,  SLOT(OpChanged()));
    connect(ui->pushButtonSub,      SIGNAL(clicked(bool)), this,  SLOT(OpChanged()));
    connect(ui->pushButtonMul,      SIGNAL(clicked(bool)), this,  SLOT(OpChanged()));
    connect(ui->pushButtonDiv,      SIGNAL(clicked(bool)), this,  SLOT(OpChanged()));
    connect(ui->pushButtonPer,      SIGNAL(clicked(bool)), this,  SLOT(PercentageOnClick()));
    connect(ui->pushButtonEqual,    SIGNAL(clicked(bool)), this,  SLOT(Result()));
    connect(ui->pushButtonDot,      SIGNAL(clicked(bool)), this,  SLOT(DotOnClick()));

    connect(ui->num0,   SIGNAL(clicked(bool)),    this,   SLOT(Input()));
    connect(ui->num1,   SIGNAL(clicked(bool)),    this,   SLOT(Input()));
    connect(ui->num2,   SIGNAL(clicked(bool)),    this,   SLOT(Input()));
    connect(ui->num3,   SIGNAL(clicked(bool)),    this,   SLOT(Input()));
    connect(ui->num4,   SIGNAL(clicked(bool)),    this,   SLOT(Input()));
    connect(ui->num5,   SIGNAL(clicked(bool)),    this,   SLOT(Input()));
    connect(ui->num6,   SIGNAL(clicked(bool)),    this,   SLOT(Input()));
    connect(ui->num7,   SIGNAL(clicked(bool)),    this,   SLOT(Input()));
    connect(ui->num8,   SIGNAL(clicked(bool)),    this,   SLOT(Input()));
    connect(ui->num9,   SIGNAL(clicked(bool)),    this,   SLOT(Input()));

    connect(ui->actionAbout,            SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));
    connect(ui->actionAbout_Calculate,  SIGNAL(triggered(bool)),this,SLOT(AboutApp()));
}

void MainWindow::Display() {
    ui->label->setText(currentNumber);
}

void MainWindow::Clear() {
    currentNumber = "0";
    lastNumber.clear();
    currentOp = nop;
    isEmpty = true;
    Display();
}

void MainWindow::SignChanged() {
    if (currentNumber.at(0) == '-') {
        currentNumber.remove(0, 1);
    } else {
        currentNumber.push_front('-');
    }
    isEmpty = true;
    Display();
}

void MainWindow::OpChanged() {
    QPushButton *button = qobject_cast<QPushButton *>(this->sender());
    if (button) {
        isEmpty = true;
        if (currentOp == nop) {
            lastNumber = currentNumber;
            currentNumber = "0";
        }
        if (button == ui->pushButtonAdd) {
            currentOp = addOp;
        } else if (button == ui->pushButtonSub) {
            currentOp = subOp;
        } else if (button == ui->pushButtonMul) {
            currentOp = mulOp;
        } else if (button == ui->pushButtonDiv) {
            currentOp = divOp;
        }
        Display();
    }
}

void MainWindow::Input() {
    if (isEmpty == false) {
        this->Clear();
    }
    QPushButton *button = qobject_cast<QPushButton *>(this->sender());
    if (button) {
        if (currentNumber == "0") {
            currentNumber.clear();
        }

        if (button == ui->num0) {
            currentNumber.push_back('0');
        } else if (button == ui->num1) {
            currentNumber.push_back('1');
        } else if (button == ui->num2) {
            currentNumber.push_back('2');
        } else if (button == ui->num3) {
            currentNumber.push_back('3');
        } else if (button == ui->num4) {
            currentNumber.push_back('4');
        } else if (button == ui->num5) {
            currentNumber.push_back('5');
        } else if (button == ui->num6) {
            currentNumber.push_back('6');
        } else if (button == ui->num7) {
            currentNumber.push_back('7');
        } else if (button == ui->num8) {
            currentNumber.push_back('8');
        } else if (button == ui->num9) {
            currentNumber.push_back('9');
        }
        Display();
    }
}

void MainWindow::DotOnClick() {
    if (isEmpty == false) {
        this->Clear();
    }
    if (currentNumber.indexOf('.') == -1) {
        currentNumber.push_back('.');
    }
    Display();
}

void MainWindow::PercentageOnClick() {
    double temp = currentNumber.toDouble() / 100.0;
    currentNumber = QString::number(temp);
    isEmpty = true;
    Display();
}

void MainWindow::Result() {
    if (currentOp == nop) return;

    if (currentOp == addOp) {
        currentNumber = QString::number(lastNumber.toDouble() + currentNumber.toDouble());
    } else if (currentOp == subOp) {
        currentNumber = QString::number(lastNumber.toDouble() - currentNumber.toDouble());
    } else if (currentOp == mulOp) {
        currentNumber = QString::number(lastNumber.toDouble() * currentNumber.toDouble());
    } else if (currentOp == divOp) {
        currentNumber = QString::number(lastNumber.toDouble() / currentNumber.toDouble());
    }
    statusBar()->showMessage("计算成功", 5000);
    currentOp = nop;
    isEmpty = false;
    Display();
}

void MainWindow::AboutApp() {
    QMessageBox::about(this,"关于计算器","了解qt所用");
}

MainWindow::~MainWindow()
{
    delete ui;
}
