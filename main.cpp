#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <vector>
#include "complex.hpp"
#include "fft.hpp"
#include <algorithm>

void keepLargestCoefficients(std::vector<Complex>& F, double keepRatio){
    std::vector<double> magnitudes;
    magnitudes.reserve(F.size());

    for(const auto& z : F){
        magnitudes.push_back(z.magnitude());
    }

    std::sort(magnitudes.begin(), magnitudes.end());

    int keepCount = static_cast<int>(keepRatio * F.size());
    int threshholdIndex = static_cast<int>(F.size() - keepCount);

    double threshhold = magnitudes[threshholdIndex];

    for(auto& z : F){
        if(z.magnitude() < threshhold){
            z = Complex(0.0, 0.0);
        }
    }
}



int main() {
    int width, height, channels;


    // Nakon ovoga smo dobili niz koji sadrzi R G B R G B R G B ... 
    // za sve piksele slike redom
    unsigned char* image = stbi_load(
        "input.png",
        &width,
        &height,
        &channels,
        3
    );

    if (!image){
        std::cout << "Greska pri ucitavanju slike.\n";
        return 1;
    }

    std::vector<Complex> R(width * height);
    std::vector<Complex> G(width * height);
    std::vector<Complex> B(width * height);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int rgbIndex = (i * width + j) * 3;
            int index = i * width + j;

            R[index] = Complex(image[rgbIndex], 0.0);
            G[index] = Complex(image[rgbIndex + 1], 0.0);
            B[index] = Complex(image[rgbIndex + 2], 0.0);
        }
    }
    
    int paddedWidth = FFT::nextPowerOfTwo(width), paddedHeight = FFT::nextPowerOfTwo(height);
   std::vector<Complex> RFFT = FFT::fft2DPadded(R,width,height,paddedWidth, paddedHeight);
   std::vector<Complex> GFFT = FFT::fft2DPadded(G,width,height,paddedWidth, paddedHeight);
   std::vector<Complex> BFFT = FFT::fft2DPadded(B,width,height,paddedWidth, paddedHeight);


    keepLargestCoefficients(RFFT,0.1);
    keepLargestCoefficients(GFFT,0.1);
    keepLargestCoefficients(BFFT,0.1);

    std::vector<unsigned char> output(width * height * 3);

    std::vector<Complex> Rrec = FFT::ifft2DPadded(RFFT,width,height,paddedWidth, paddedHeight);
    std::vector<Complex> Grec = FFT::ifft2DPadded(GFFT,width,height,paddedWidth, paddedHeight);
    std::vector<Complex> Brec = FFT::ifft2DPadded(BFFT,width,height,paddedWidth, paddedHeight);

    for(int i = 0; i < width * height; i++){
        double r = R[i].real_part();
        double g = G[i].real_part();
        double b = B[i].real_part();

        r = std::min(255.0, std::max(0.0, Rrec[i].real_part()));
        g = std::min(255.0, std::max(0.0, Grec[i].real_part()));
        b = std::min(255.0, std::max(0.0, Brec[i].real_part()));

        output[i * 3] = static_cast<unsigned char>(r);
        output[i * 3 + 1] = static_cast<unsigned char>(g);
        output[i * 3 + 2] = static_cast<unsigned char>(b);
    }

    stbi_write_png("kompresovana.png", width,height,3,output.data(), width * 3);

    stbi_image_free(image);

    return 0;
}
