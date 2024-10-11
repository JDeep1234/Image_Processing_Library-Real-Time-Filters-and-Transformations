#include "ImageProcessor.h"

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
