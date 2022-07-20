#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->mondelbrotView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  ui->mondelbrotView->setSceneRect(0, 0, ui->tab_5->width(), ui->tab_5->height());
  ui->mondelbrotView->preset();
  ui->mondelbrotView->draw(MyGraphicsView::Mondelbroth, ComplexNumber(0, 0));
  ui->juliaView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  ui->juliaView->setSceneRect(0, 0, ui->tab_5->width(), ui->tab_5->height());
  ui->juliaView->preset();
  ui->juliaView->draw(MyGraphicsView::Julia, ComplexNumber(-0.8, 0.156));
  ui->stohasticView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  ui->stohasticView->setSceneRect(0, 0, ui->tab_5->width(), ui->tab_5->height());
  ui->stohasticView->preset();
  ui->stohasticView->draw(MyGraphicsView::Stohastic, ComplexNumber(0, 0));
  int range = 10000;
  ui->rationalSlider->setMaximum(range);
  ui->rationalSlider->setMinimum(-range);
  ui->rationalSlider->setValue(-8000);
  ui->complexSlider->setMaximum(range);
  ui->complexSlider->setMinimum(-range);
  ui->complexSlider->setValue(1560);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_rationalSlider_sliderChanged()
{
  ui->juliaView->draw(MyGraphicsView::Julia, ComplexNumber(ui->rationalSlider->value() / 1e4, ui->complexSlider->value() / 1e4));
}

void MainWindow::on_complexSlider_sliderReleased()
{
  ui->juliaView->draw(MyGraphicsView::Julia, ComplexNumber(ui->rationalSlider->value() / 1e4, ui->complexSlider->value() / 1e4));
}
/*
void MainWindow::on_rationalSlider_valueChanged(int value)
{
  ui->juliaView->draw(MyGraphicsView::Julia, ComplexNumber(ui->rationalSlider->value() / 1e4, ui->complexSlider->value() / 1e4));

}

void MainWindow::on_complexSlider_valueChanged(int value)
{
  ui->juliaView->draw(MyGraphicsView::Julia, ComplexNumber(ui->rationalSlider->value() / 1e4, ui->complexSlider->value() / 1e4));

}
*/
