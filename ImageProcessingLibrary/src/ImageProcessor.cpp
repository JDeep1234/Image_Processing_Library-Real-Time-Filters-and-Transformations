#include "ImageProcessor.h"
#include <immintrin.h>  // For AVX2 intrinsics

cv::Mat ImageProcessor::applyGaussianBlur(const cv::Mat& input, int kernelSize) {
    cv::Mat output;
    cv::GaussianBlur(input, output, cv::Size(kernelSize, kernelSize), 0);
    return output;
}

cv::Mat ImageProcessor::applyEdgeDetection(const cv::Mat& input) {
    cv::Mat gray, edges;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::Canny(gray, edges, 100, 200);
    return edges;
}

cv::Mat ImageProcessor::applySharpening(const cv::Mat& input) {
    cv::Mat kernel = (cv::Mat_<float>(3,3) << 
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0);
    cv::Mat output;
    cv::filter2D(input, output, CV_32F, kernel);
    return output;
}

cv::Mat ImageProcessor::resizeImage(const cv::Mat& input, double scale) {
    cv::Mat output;
    cv::resize(input, output, cv::Size(), scale, scale);
    return output;
}

cv::Mat ImageProcessor::rotateImage(const cv::Mat& input, double angle) {
    cv::Point2f center(input.cols / 2.0, input.rows / 2.0);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::Mat output;
    cv::warpAffine(input, output, rotationMatrix, input.size());
    return output;
}

cv::Mat ImageProcessor::applyGaussianBlurSIMD(const cv::Mat& input, int kernelSize) {
    cv::Mat output = input.clone();
    int width = input.cols;
    int height = input.rows;

    // Define Gaussian kernel (for simplicity, using a fixed 3x3 kernel)
    float kernel[3][3] = {
        {1/16.0, 2/16.0, 1/16.0},
        {2/16.0, 4/16.0, 2/16.0},
        {1/16.0, 2/16.0, 1/16.0}
    };

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; x += 8) { // Process 8 pixels at a time
            __m256 sum = _mm256_setzero_ps(); // Initialize sum for SIMD
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    // Load 8 pixels from input image
                    __m256 pixels = _mm256_loadu_ps((float*)&input.at<cv::Vec3b>(y + ky, x + kx)[0]);
                    // Multiply by the corresponding kernel value
                    __m256 kernelValue = _mm256_set1_ps(kernel[ky + 1][kx + 1]);
                    sum = _mm256_fmadd_ps(pixels, kernelValue, sum); // Fused multiply-add
                }
            }
            // Store the result in output image
            _mm256_storeu_ps((float*)&output.at<cv::Vec3b>(y, x)[0], sum);
        }
    }
    return output;
}
