#include <iostream>
#include <opencv2/opencv.hpp>
#include "regions.h"

using namespace cv;
using namespace std;

bool isvalid(int x, int y, int w, int h) {
    if (x < 0 || x > w) 
    {
        return false;
    }

    if (y < 0 || y > h)
    {
        return false;
    }

    return true;
}

bool isgreater(int x1, int x2, int y1, int y2) {
    if (x1 > x2 || y1 > y2)
    {
        return false;
    }

    return true;
}

int regions() {
    cv::Mat image;
    cv::Vec3b val;
    cv::Size sz;

    bool valid, greater;

    image = cv::imread("biel.png", cv::IMREAD_GRAYSCALE);
    if (!image.data)
        std::cout << "Image not found" << std::endl;
    
    sz = image.size();

    cv::namedWindow("regions.cpp", cv::WINDOW_AUTOSIZE);

    int x1, x2, y1, y2;

    std::cout << "P1: ";
    std::cin >> x1 >> y1;

    valid = isvalid(x1, y1, sz.width, sz.height);

    if (!valid) 
    {
        cout << "Invalid P1" << endl;
        return 0;
    }

    std::cout << "P2: ";
    std::cin >> x2 >> y2;

    valid = isvalid(x2, y2, sz.width, sz.height);

    if (!valid) 
    {
        cout << "Invalid P2" << endl;
        return 0;
    }

    greater = isgreater(x1, x2, y1, y2);

    if (!greater)
    {
        cout << "Invalid coordinates" << endl;
        return 0;
    }

    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
        }
    }

    cv::imshow("regions.cpp", image);
    cv::waitKey();

    return 0;
}