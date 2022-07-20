#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#pragma once

#include <cmath>
#include <complex.h>
#include <random>
#include <chrono>

extern std::mt19937 rng;

const int INF = 2;

class ComplexNumber
{
public:
  ComplexNumber(double a, double b);
  ComplexNumber(double a);
  ComplexNumber();
  ComplexNumber operator+(ComplexNumber other);
  ComplexNumber operator*(ComplexNumber other);
  ComplexNumber& operator=(ComplexNumber other);
  double mod();
//private:
  double a_, b_;
};

#endif // COMPLEXNUMBER_H
