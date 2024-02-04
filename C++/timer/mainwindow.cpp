#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startTimer);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopTimer);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetTimer);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::closeTimer);

    // change lcd color
    ui->lcdNumberMin->setStyleSheet("background : blue");
    ui->lcdNumberSec->setStyleSheet("background : green");

    timer = new QTimer();
    // connect timer interval to mainWindow
    connect(timer, &QTimer::timeout, this, &MainWindow::secondPassed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTimer()
{
    timer->start(1000);

}

void MainWindow::stopTimer()
{
    timer->stop();
}

void MainWindow::resetTimer()
{
    timePassed = 0;
    updateLCD();
}

void MainWindow::closeTimer()
{
    this->close();
}


void MainWindow::secondPassed()
{
    timePassed++;
    updateLCD();
}

void MainWindow::updateLCD()
{
    // calc time values
    int minutes = timePassed / 60;
    int seconds = timePassed % 60;

    ui->lcdNumberMin->display(minutes);
    ui->lcdNumberSec->display(seconds);
}
