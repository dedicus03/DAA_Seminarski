#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>


class Complex{
public:
    Complex(double real = 0.0,double imaginary = 0.0)
    : _real(real),_imaginary(imaginary) {}

    double real_part() const;
    double imaginary_part() const;
    void set_real_part(double real);
    void set_imaginary_part(double imaginary);
    double magnitude() const;

    Complex operator+(const Complex& z) const;
    Complex operator-(const Complex& z) const;
    Complex operator*(const Complex& z) const;
    Complex operator/(const Complex& z) const;
    Complex conjugate() const;

    bool operator==(const Complex& z) const;
    bool operator<(const Complex& z) const;

    Complex exp() const;
private:
    double _real;
    double _imaginary;
};

std::ostream& operator<<(std::ostream& output, const Complex& z);
std::istream& operator>>(std::istream& input, Complex& z);

#endif
