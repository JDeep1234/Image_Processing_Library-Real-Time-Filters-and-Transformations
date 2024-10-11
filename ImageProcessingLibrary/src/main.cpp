#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImageProcessor.h"

int main() {
    // Load an image
    cv::Mat image = cv::imread("input.jpg");
    if (image.empty()) {
        std::cerr << "Could not open or find the image!" << std::endl;
        return -1;
    }

    // Apply filters
    cv::Mat blurred = ImageProcessor::applyGaussianBlur(image, 5);
    cv::Mat edges = ImageProcessor::applyEdgeDetection(image);
    cv::Mat sharpened = ImageProcessor::applySharpening(image);
    cv::Mat resized = ImageProcessor::resizeImage(image, 0.5);
    cv::Mat rotated = ImageProcessor::rotateImage(image, 45);
    cv::Mat simdBlurred = ImageProcessor::applyGaussianBlurSIMD(image, 3);

    // Show results
    cv::imshow("Original", image);
    cv::imshow("Blurred", blurred);
    cv::imshow("SIMD Blurred", simdBlurred);
    cv::imshow("Edges", edges);
    cv::imshow("Sharpened", sharpened);
    cv::imshow("Resized", resized);
    cv::imshow("Rotated", rotated);

    cv::waitKey(0);
    return 0;
}
