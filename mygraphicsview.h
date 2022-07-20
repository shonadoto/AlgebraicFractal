#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#pragma once

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QMouseEvent>
#include <QLabel>
#include <stack>
#include <QVector>
#include "complexnumber.h"
#include "mycolor.h"

class MyGraphicsView : public QGraphicsView
{
public:
  MyGraphicsView(QWidget *parent) : QGraphicsView(parent) {
    scene_ = new QGraphicsScene();
    setScene(scene_);
    zoom_pen_ = QPen(QColor(Qt::gray), Qt::DashLine);
  }
  QGraphicsScene * scene_;
  void preset();
  void draw(int mod, ComplexNumber C);
  static const int Mondelbroth = 0, Julia = 1, Stohastic = 2;

private:
  QPixmap * pix_img_;
  QPair<double, double> y_range, x_range;
  std::stack<QPair<QPair<double, double>, QPair<double, double>>> *resize_stack;
  int zoom_rect_x_, zoom_rect_y_;
  QGraphicsRectItem *zoom_rect_;
  QPen zoom_pen_;
  bool pressed_ = 0;
  double scale_;
  std::vector<QColor>* colors_;
  int mod_;
  ComplexNumber C_;

  QPair<double, double> getCoords(int i, int j);
  QColor getMondColor(QPair<double, double> coords);
  QColor getJuliaColor(QPair<double, double> coords, ComplexNumber C = ComplexNumber(0, 0));
  void drawStohastic(int x1, int y1, int x2, int y2, QImage *& image);

protected:
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual void mouseReleaseEvent(QMouseEvent* event);
  virtual void resizeEvent(QResizeEvent* event);
  virtual void keyPressEvent(QKeyEvent* event);
};

#endif // MYGRAPHICSVIEW_H
