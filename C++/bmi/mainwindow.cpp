#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->weightLineEdit, &QLineEdit::editingFinished,
            this, &MainWindow::on_weightLineEdit_editingFinished);
    connect(ui->heightLineEdit, &QLineEdit::editingFinished,
            this, &MainWindow::on_heightLineEdit_editingFinished);
    connect(ui->countButton, &QPushButton::clicked,
            this, &MainWindow::calculateBMI);
    connect(ui->closeButton, &QPushButton::clicked,
            this, &MainWindow::closeWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculateBMI()
{
    double weight = ui->weightLineEdit->text().toDouble();
    double height = ui->heightLineEdit->text().toDouble() / 100;

    if(height == 0){
        ui->resultLabel->setText("Cannot count.");
        ui->infoTextBrowser->setText("");
        return;
    }

    double BMI = weight / (height * height);
    QString stringBMI = QString::number(BMI, 'f', 4);
    ui->resultLabel->setText(stringBMI);

    if(BMI < 18.5){
        ui->infoTextBrowser->setText("You are underweight.");
    }else if(BMI > 25){
        ui->infoTextBrowser->setText("You are overweight.");
    }else{
        ui->infoTextBrowser->setText("Your weight is normal.");
    }
}

void MainWindow::closeWindow()
{
    this->MainWindow::close();
}


void MainWindow::on_weightLineEdit_editingFinished()
{
    ui->weightLineEdit->text();
}


void MainWindow::on_heightLineEdit_editingFinished()
{
    ui->heightLineEdit->text();
}

