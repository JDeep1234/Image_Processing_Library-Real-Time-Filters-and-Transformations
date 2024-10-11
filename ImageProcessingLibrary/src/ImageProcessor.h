#pragma once

#include <opencv2/opencv.hpp>

class ImageProcessor {
public:
    static cv::Mat applyGaussianBlur(const cv::Mat& input, int kernelSize);
    static cv::Mat applyEdgeDetection(const cv::Mat& input);
    static cv::Mat applySharpening(const cv::Mat& input);
    static cv::Mat resizeImage(const cv::Mat& input, double scale);
    static cv::Mat rotateImage(const cv::Mat& input, double angle);
    static cv::Mat applyGaussianBlurSIMD(const cv::Mat& input, int kernelSize);
};
