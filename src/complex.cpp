#include <iostream>
#include "complex.hpp"
#include <cmath>
#include <stdexcept>

double Complex::real_part() const{
    return _real;
}

double Complex::imaginary_part() const{
    return _imaginary;
}

void Complex::set_real_part(double real){
    _real = real;
}

void Complex::set_imaginary_part(double imaginary){
    _imaginary = imaginary;
}

double Complex::magnitude() const{
    return std::sqrt(_real*_real + _imaginary*_imaginary);
}

Complex Complex::operator+(const Complex& z) const{
    return Complex(_real + z.real_part(), _imaginary + z.imaginary_part());
}

Complex Complex::operator-(const Complex& z) const{
    return Complex(_real - z.real_part(), _imaginary - z.imaginary_part());
}

Complex Complex::operator*(const Complex& z) const{
    return Complex(_real * z.real_part() - _imaginary * z.imaginary_part(), _real * z.imaginary_part() + _imaginary * z.real_part());
}

Complex Complex::operator/(const Complex& z) const{
    if(z.real_part() == 0.0 && z.imaginary_part() == 0.0)
        throw std::runtime_error("Division by zero");

    Complex z0 = (*this)*(z.conjugate());
    z0.set_real_part(z0.real_part()/(z.real_part() * z.real_part() + z.imaginary_part() *z.imaginary_part()));
    z0.set_imaginary_part(z0.imaginary_part()/(z.real_part() * z.real_part() + z.imaginary_part() *z.imaginary_part()));

    return z0;
}

Complex Complex::conjugate() const{
    return Complex(_real, -_imaginary);
}

bool Complex::operator==(const Complex& z) const{
    return _real == z.real_part() && _imaginary == z.imaginary_part();
}

bool Complex::operator<(const Complex& z) const{
    return this->magnitude() < z.magnitude();
}

Complex Complex::exp() const{
    double e = std::exp(_real);

    return Complex(
        e * std::cos(_imaginary),
        e * std::sin(_imaginary)
    );
}

std::ostream& operator<<(std::ostream& output, const Complex& z){
        output << z.real_part();

    if (z.imaginary_part() >= 0)
        output << "+" << z.imaginary_part() << "i";
    else
        output << z.imaginary_part() << "i";

    return output;

}

std::istream& operator>>(std::istream& input, Complex& z){
    double real,imaginary;
    input >> real >> imaginary;

    z.set_real_part(real);
    z.set_imaginary_part(imaginary);

    return input;
}