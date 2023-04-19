#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_pushButton_push_clicked();

    void on_pushButton_pop_clicked();

    void on_pushButton_size_clicked();

    void on_pushButton_front_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_empty_clicked();

    void on_pushButton_emplace_clicked();

    void on_pushButton_swap_clicked();

    void on_pushButton_mySolve_clicked();

    void CreateRamdomQueue();

    void sort();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
