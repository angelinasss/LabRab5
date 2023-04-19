#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "queue.cpp"
#include <QMessageBox>

queue<int> myQueue;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myQueue.push(9);
    ui->listWidget->addItem(QString::number(myQueue.back()));
    ui->listWidget_2->addItem(QString::number(myQueue.back()));
    myQueue.push(3);
    ui->listWidget->addItem(QString::number(myQueue.back()));
    ui->listWidget_2->addItem(QString::number(myQueue.back()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_push_clicked()
{
    myQueue.push(2);
    ui->listWidget_2->addItem(QString::number(myQueue.back()));
    myQueue.push(8);
    ui->listWidget_2->addItem(QString::number(myQueue.back()));
    myQueue.push(5);
    ui->listWidget_2->addItem(QString::number(myQueue.back()));
}


void MainWindow::on_pushButton_pop_clicked()
{
    try {
    delete ui->listWidget_2->takeItem(0);
    myQueue.pop();
    }
    catch(...) {
        QMessageBox::critical(this, "WARNING!", "You are trying to remove an element from an empty queue!");
    }
}


void MainWindow::on_pushButton_size_clicked()
{
    QMessageBox::information(this, "INFORMATION!", "Queue's size is " + QString::number(myQueue.size()));
}


void MainWindow::on_pushButton_front_clicked()
{
    QMessageBox::information(this, "INFORMATION!", "Front's element is " + QString::number(myQueue.front()));
}


void MainWindow::on_pushButton_back_clicked()
{
    QMessageBox::information(this, "INFORMATION!", "Back's element is " + QString::number(myQueue.back()));
}


void MainWindow::on_pushButton_empty_clicked()
{
    if(myQueue.empty()) {
    QMessageBox::information(this, "INFORMATION!", "Queue is empty");
    }
    else QMessageBox::information(this, "INFORMATION!", "Queue is not empty");
}


void MainWindow::on_pushButton_emplace_clicked()
{
    myQueue.emplace(9);
    ui->listWidget_2->addItem(QString::number(myQueue.back()));
    myQueue.emplace(11);
    ui->listWidget_2->addItem(QString::number(myQueue.back()));
}


void MainWindow::on_pushButton_swap_clicked()
{
    queue<int> myQueue1;
    ui->listWidget_2->clear();
    myQueue1.push(1);
    ui->listWidget_2->addItem(QString::number(myQueue1.back()));
    myQueue1.push(2);
    ui->listWidget_2->addItem(QString::number(myQueue1.back()));
    myQueue1.push(3);
    ui->listWidget_2->addItem(QString::number(myQueue1.back()));
    myQueue1.push(4);
    ui->listWidget_2->addItem(QString::number(myQueue1.back()));
    myQueue1.push(5);
    ui->listWidget_2->addItem(QString::number(myQueue1.back()));
    myQueue.swap(myQueue1);
}

void MainWindow::CreateRamdomQueue() {
    myQueue.clear();
    for (int i = 0; i < 25; i++) {
        int a = rand() % 25;
        myQueue.push(a);
        ui->listWidget->addItem(QString::number(myQueue.back()));
    }
}

void MainWindow::sort()
{
    for (size_t j = 1; j < myQueue.size() - 1; j++) {
        int temp = myQueue.front();
        myQueue.pop();
        size_t steps = 0;

        while (steps < myQueue.size()) {


            if (temp < myQueue.front()) {
                myQueue.push(temp);
                temp = myQueue.front();
                myQueue.pop();
                steps = 0;
            }
            else {
                myQueue.push(myQueue.front());
                myQueue.pop();
                steps += 1;
            }

        }
        myQueue.push(temp);

    }
}

void MainWindow::on_pushButton_mySolve_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    CreateRamdomQueue();
    sort();
    while(!myQueue.empty()) {
    ui->listWidget_2->addItem(QString::number(myQueue.front()));
    myQueue.pop();
    }
}
