#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->calculatePushButton, &QPushButton::clicked, this, &MainWindow::calculateGrade);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::calculateGrade()
{
    // get different points
    int n = ui->spinBoxN->value();
    int g = ui->spinBoxG->value();
    int p = ui->spinBoxP->value();
    int e = ui->spinBoxE->value();

    // calculate grade
    int totalGrade = calculate_total_grade(n, g, p, e);
    int W = score_from_weekly_exercises(n, g);
    int P = score_from_projects(p);

    // show the grade
    QString grade = QString::fromStdString(std::to_string(totalGrade));
    QString wScore = QString::fromStdString(std::to_string(W));
    QString pScore = QString::fromStdString(std::to_string(P));
    ui->textBrowser->setText("W-Score: " + wScore +
                             "\nP-Score: " + pScore +
                             "\nTotal grade: " + grade);
}

