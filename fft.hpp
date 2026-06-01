#ifndef FFT_HPP
#define FFT_HPP
#include <iostream>
#include <vector>
#include "complex.hpp"

namespace FFT{
    bool isPowerOfTwo(int n);
    int nextPowerOfTwo(int n);
    
    void fft(const std::vector<Complex>& a, int start_a,const std::vector<Complex>& w,
            std::vector<Complex>& rezultat, int start_rezultat,int korak);
    std::vector<Complex> fft(const std::vector<Complex>& a);
    std::vector<Complex> ifft(const std::vector<Complex>& a);
    std::vector<Complex> fftPadded(const std::vector<Complex>& a);
    std::vector<Complex> ifftPadded(const std::vector<Complex> &a, int originalSize);
    
    std::vector<Complex> fft2D(const std::vector<Complex>& data, int width, int height);
    std::vector<Complex> ifft2D(const std::vector<Complex>& data, int width, int height);
    std::vector<Complex> fft2DPadded(const std::vector<Complex>& data, int width, int height, int paddedWidth, int paddedHeight);
    std::vector<Complex> ifft2DPadded(const std::vector<Complex>& data, int originalWidth, int originalHeight, int paddedWidth, int paddedHeight);
}

#endif