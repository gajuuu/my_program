#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void calculateBMI();
    void closeWindow();
    void on_weightLineEdit_editingFinished();
    void on_heightLineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HH
