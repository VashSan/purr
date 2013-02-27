#include "purrwindow.hpp"
#include "ui_purrwindow.h"

PurrWindow::PurrWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PurrWindow)
{
    ui->setupUi(this);
}

PurrWindow::~PurrWindow()
{
    delete ui;
}

void PurrWindow::on_openButton_clicked()
{

}

void PurrWindow::on_playButton_clicked()
{

}

void PurrWindow::on_pauseButton_clicked()
{

}

void PurrWindow::on_stopButton_clicked()
{

}
