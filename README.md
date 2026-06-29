# Image Compression Using FFT

## Algorithm Description

This project implements image compression using the **Fast Fourier Transform (FFT)**.

The main idea is to transform an image from the spatial domain into the frequency domain. In the spatial domain, the image is represented by pixel values. After applying FFT, the image is represented by frequency coefficients.

The image is first separated into three color channels: red, green, and blue. A two-dimensional FFT is then applied independently to each channel.

After the transformation, the coefficients with the largest magnitudes are considered the most important because they contain most of the visual information of the image. Compression is performed by keeping only a selected percentage of the largest coefficients and setting the remaining coefficients to zero.

After that, the inverse FFT is applied to each channel in order to reconstruct the image. Finally, the three reconstructed channels are combined back into one RGB image.

The algorithm follows these steps:

1. Load the input image.
2. Separate the image into RGB channels.
3. Apply 2D FFT to each channel.
4. Sort or select the frequency coefficients by magnitude.
5. Keep only the largest coefficients.
6. Set the remaining coefficients to zero.
7. Apply inverse 2D FFT to reconstruct each channel.
8. Combine the reconstructed channels.
9. Save the compressed image.

This method is lossy, because some frequency coefficients are permanently removed. A smaller percentage of retained coefficients gives stronger compression, but lower image quality. A larger percentage gives better quality, but weaker compression.

## Technologies Used

The project is implemented in **C++**.

The following technologies and libraries are used:

* **C++ Standard Library**

  * used for vectors, complex numbers, sorting, mathematical operations, and file handling logic;

* **Custom FFT implementation**

  * used for one-dimensional and two-dimensional Fast Fourier Transform and inverse FFT;

* **stb_image.h**

  * used for loading image files;

* **stb_image_write.h**

  * used for saving the reconstructed compressed image.

The image is processed as an RGB image, where each color channel is compressed independently in the frequency domain.

