#include "fft.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

bool FFT::isPowerOfTwo(int n){
    return n > 0 && (n & (n-1)) == 0;
}

int FFT::nextPowerOfTwo(int n){
    int power = 1;

    while(n > power){
        power *= 2;
    }

    return power;
}

void FFT::fft(const std::vector<Complex>& a, int start_a, const std::vector<Complex>& w, 
        std::vector<Complex>& rezultat, int start_rezultat, int korak){

    int n = a.size()/korak;

    if(n == 1){
        rezultat[start_rezultat] = a[start_a];
        return;
    }

    fft(a,start_a,w,rezultat,start_rezultat,korak*2);
    fft(a,start_a + korak,w,rezultat,start_rezultat + n/2, korak* 2);

    for(int k = 0; k < n/2; k++){
        Complex r1 = rezultat[start_rezultat + k];
        Complex r2 = rezultat[start_rezultat + (k + n/2)];

        rezultat[start_rezultat + k] = r1 + w[k*korak]*r2;
        rezultat[start_rezultat + (k + n/2)] = r1 - w[k*korak]*r2;
    }
}

std::vector<Complex> FFT::fft(const std::vector<Complex>& a){
    int n = a.size();

    std::vector<Complex> w(n/2);

    for(int k = 0; k < n/2; k++){
        w[k] = (Complex(2 * k * M_PI/n, 0) * Complex(0,1)).exp();
    }

    std::vector<Complex> rezultat(n);
    fft(a,0,w,rezultat,0,1);

    return rezultat;
}

std::vector<Complex> FFT::ifft(const std::vector<Complex>& a){
    int n = a.size();

    std::vector<Complex> w(n);
    for(int k = 0; k < n; k++)
        w[k] = (Complex(-2 * k * M_PI/n, 0) * Complex(0,1)).exp();

    std::vector<Complex> rezultat(n);

    fft(a,0,w,rezultat,0,1);

    for(int i = 0; i < n; i++)
        rezultat[i] = rezultat[i]/Complex(n,0);

    return rezultat;
}

std::vector<Complex> FFT::fftPadded(const std::vector<Complex>& a){
    if(a.empty())
        throw std::runtime_error("FFT ne moze nad praznim nizom.");
    
    int n = a.size();

    if(isPowerOfTwo(n))
        return fft(a);
    
    int paddedSize = nextPowerOfTwo(n);

    std::vector<Complex> b(paddedSize);

    for(int j = 0; j < n; j++)
        b[j] = a[j];

    return fft(b);
}

std::vector<Complex> FFT::ifftPadded(
    const std::vector<Complex>& a,
    int originalSize
) {
    if (a.empty()) {
        throw std::runtime_error("IFFT ne moze raditi nad praznim nizom.");
    }

    if (originalSize <= 0 || originalSize > (int)a.size()) {
        throw std::runtime_error("Neispravna originalna duzina.");
    }

    std::vector<Complex> reconstructed = FFT::ifft(a);

    reconstructed.resize(originalSize);

    return reconstructed;
}


std::vector<Complex> FFT::fft2D(const std::vector<Complex>& data, int width, int height){
    if((int) data.size() != width * height){
        throw std::runtime_error("Neispravna velicina podataka za 2D FFT.");
    }

    std::vector<Complex> result = data;

    for(int y = 0; y < height; y++){
        std::vector<Complex> row(width);

        for(int x=  0; x < width; x++){
            row[x] = result[y * width + x];
        }

        row = FFT::fft(row);

        for(int x = 0; x < width; x++){
            result[y * width + x] = row[x];
        }
    }

    for(int x = 0; x < width; x++){
        std::vector<Complex> column(height);

        for(int y = 0; y < height; y++){
            column[y] = result[y * width + x];
        }

        column = FFT::fft(column);

        for(int y = 0; y < height; y++){
            result[y * width + x] = column[y];
        }
    }

    return result;
}

std::vector<Complex> FFT::ifft2D(const std::vector<Complex>& data, int width,int height){
    if((int) data.size() != width * height){
        throw std::runtime_error("Neispravna velicina podataka za 2D IFFT.");
    }

    std::vector<Complex> result = data;

    for(int y = 0; y < height; y++){
        std::vector<Complex> row(width);

        for(int x = 0; x < width; x++){
            row[x] = result[y * width + x];
        }

        row = FFT::ifft(row);

        for(int x = 0; x< width; x++){
            result[y * width + x] = row[x];
        }
    }

    for(int x = 0 ;x < width; x++){
        std::vector<Complex> column(height);

        for(int y = 0; y < height; y++){
            column[y] = result[y*width + x];
        }

        column = FFT::ifft(column);

        for(int y = 0; y < height; y++){
            result[y * width + x] = column[y];
        }
    }

    return result;
}

std::vector<Complex> FFT::fft2DPadded(
    const std::vector<Complex>& data,
    int width,
    int height,
    int paddedWidth,
    int paddedHeight
) {
    if ((int)data.size() != width * height) {
        throw std::runtime_error("Neispravna velicina podataka za 2D FFT.");
    }

    std::vector<Complex> padded(
        paddedWidth * paddedHeight,
        Complex(0.0, 0.0)
    );

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            padded[y * paddedWidth + x] = data[y * width + x];
        }
    }

    return FFT::fft2D(padded, paddedWidth, paddedHeight);
}

std::vector<Complex> FFT::ifft2DPadded(
    const std::vector<Complex>& data,
    int originalWidth,
    int originalHeight,
    int paddedWidth,
    int paddedHeight
) {
    if ((int)data.size() != paddedWidth * paddedHeight) {
        throw std::runtime_error("Neispravna velicina podataka za 2D IFFT.");
    }

    std::vector<Complex> reconstructed =
        FFT::ifft2D(data, paddedWidth, paddedHeight);

    std::vector<Complex> cropped(originalWidth * originalHeight);

    for (int y = 0; y < originalHeight; y++) {
        for (int x = 0; x < originalWidth; x++) {
            cropped[y * originalWidth + x] =
                reconstructed[y * paddedWidth + x];
        }
    }

    return cropped;
}