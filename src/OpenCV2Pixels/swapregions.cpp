#include <iostream>
#include <opencv2/opencv.hpp>
#include "swapregions.h"

using namespace cv;
using namespace std;

void swapregions() {
    cv::Mat image;
    cv::Vec3b val;
    cv::Size sz;

    image = cv::imread("biel.png", cv::IMREAD_GRAYSCALE);
    if (!image.data)
        std::cout << "Can't open image." << std::endl;

    cv::namedWindow("swapregions.cpp", cv::WINDOW_AUTOSIZE);

    sz = image.size();

    int width = sz.width;
    int height = sz.height;

    cv::Mat one(image, Rect(0, 0, (width / 2), (height / 2)));
    cv::Mat two(image, Rect((width / 2), 0, (width / 2), (height / 2)));
    cv::Mat three(image, Rect(0, (height / 2), (width / 2), (height / 2)));
    cv::Mat four(image, Rect((width / 2), (height / 2), (width / 2), (height/2)));
    
    cv::Mat first, second;
    
    cv::vconcat(four, two, first);
    cv::vconcat(three, one, second);

    cv::hconcat(first, second, image);

    cv::imshow("swapregions.cpp", image);
    cv::waitKey();
}