#include "complexnumber.h"
#include <complex.h>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

ComplexNumber::ComplexNumber(double a, double b)
{
  a_ = a;
  b_ = b;
}

ComplexNumber::ComplexNumber(double a) {
  a_ = a;
  b_ = 0;
}

ComplexNumber::ComplexNumber() {
  a_ = 0;
  b_ = 0;
}

ComplexNumber ComplexNumber::operator+(ComplexNumber other){
  ComplexNumber tmp = *this;
  tmp.a_ += other.a_;
  tmp.b_ += other.b_;
  return tmp;
}

ComplexNumber ComplexNumber::operator*(ComplexNumber other) {
  ComplexNumber tmp = *this;
  tmp.a_ = a_ * other.a_ - b_ * other.b_;
  tmp .b_ = a_ * other.b_ + b_ * other.a_;
  return tmp;
}

double ComplexNumber::mod() {
  return std::sqrt(a_ * a_ + b_ * b_);
}

ComplexNumber& ComplexNumber::operator=(ComplexNumber other) {
  a_ = other.a_;
  b_ = other.b_;
  return *this;
}
