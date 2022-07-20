#ifndef MYCOLOR_H
#define MYCOLOR_H
#pragma once

#include <QColor>
#include <complexnumber.h>

class MyColor
{
public:
  MyColor() : r_(0), g_(0), b_(0) {}
  MyColor(int r, int g, int b) : r_(r), g_(g), b_(b) {}
  MyColor(QColor clr) : r_(clr.red()), g_(clr.green()), b_(clr.blue()) {}

  QColor getColor() {
    return QColor(r_ % 256, g_ % 256, b_ % 256);
  }

  MyColor operator+(int val) {
    MyColor tmp(r_ + rng() % val, g_ + rng() % val, b_ + rng() % val);
    return tmp;
  }

  MyColor operator+(MyColor other) {
    MyColor tmp(r_ + other.r_, g_ + other.g_, b_ + other.b_);
    return tmp;
  }

  MyColor operator/ (int other) {
    MyColor tmp(r_ / other, g_ / other, b_ / other);
    return tmp;
  }

  MyColor& operator= (MyColor other) {
    r_ = other.r_;
    g_ = other.g_;
    b_ = other.b_;
    return *this;
  }

private:
  int r_, g_, b_;
};

#endif // MYCOLOR_H
