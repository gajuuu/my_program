#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->horizontalSliderRed->setMinimum(0);
    ui->horizontalSliderRed->setMaximum(RGB_VALUE_MAX);
    ui->spinBoxRed->setMinimum(0);
    ui->spinBoxRed->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderGreen->setMinimum(0);
    ui->horizontalSliderGreen->setMaximum(RGB_VALUE_MAX);
    ui->spinBoxGreen->setMinimum(0);
    ui->spinBoxGreen->setMaximum(RGB_VALUE_MAX);

    ui->horizontalSliderBlue->setMinimum(0);
    ui->horizontalSliderBlue->setMaximum(RGB_VALUE_MAX);
    ui->spinBoxBlue->setMinimum(0);
    ui->spinBoxBlue->setMaximum(RGB_VALUE_MAX);

    connect(ui->horizontalSliderRed, &QSlider::valueChanged, ui->spinBoxRed, &QSpinBox::setValue);
    connect(ui->horizontalSliderGreen, &QSlider::valueChanged, ui->spinBoxGreen, &QSpinBox::setValue);
    connect(ui->horizontalSliderBlue, &QSlider::valueChanged, ui->spinBoxBlue, &QSpinBox::setValue);

    // connect spinBoxes
    connect(ui->spinBoxRed, &QSpinBox::valueChanged, ui->horizontalSliderRed, &QSlider::setValue);
    connect(ui->spinBoxGreen, &QSpinBox::valueChanged, ui->horizontalSliderGreen, &QSlider::setValue);
    connect(ui->spinBoxBlue, &QSpinBox::valueChanged, ui->horizontalSliderBlue, &QSlider::setValue);

    connect(ui->spinBoxRed, &QSpinBox::valueChanged, this, &MainWindow::onColorChanged);
    connect(ui->spinBoxGreen, &QSpinBox::valueChanged, this, &MainWindow::onColorChanged);
    connect(ui->spinBoxBlue, &QSpinBox::valueChanged, this, &MainWindow::onColorChanged);

    onColorChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onColorChanged()
{
    //qDebug() << "onColorChanged";
    QColor selectedColor(ui->horizontalSliderRed->value(),
                         ui->horizontalSliderGreen->value(),
                         ui->horizontalSliderBlue->value());

    QPixmap colorMap(64, 64);
    colorMap.fill(selectedColor);
    ui->colorLabel->setPixmap(colorMap);
}
