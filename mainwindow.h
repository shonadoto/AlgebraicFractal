#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include "mygraphicsview.h"

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
  void on_rationalSlider_sliderChanged();

  void on_complexSlider_sliderReleased();

  //void on_rationalSlider_valueChanged(int value);

  //void on_complexSlider_valueChanged(int value);

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
