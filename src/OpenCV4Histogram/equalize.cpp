#include <iostream>
#include <opencv2/opencv.hpp>
#include "equalize.h"

using namespace cv;

int equalize() {
	
	cv::Mat image, eq_image;
    int width, height;
    cv::VideoCapture cap;
    cv::Mat hist, histEq;
    int nbins = 64;
    float range[] = { 0, 255 };
    const float* histrange = { range };
    bool uniform = true;
    bool acummulate = false;
    int key;

    cap.open(0);

    if (!cap.isOpened()) {
        std::cout << "cameras indisponiveis";
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "largura = " << width << std::endl;
    std::cout << "altura  = " << height << std::endl;

    int histw = nbins, histh = nbins / 2;
    cv::Mat histImg(histh, histw, CV_8U, cv::Scalar(0));
    cv::Mat histImgEq(histh, histw, CV_8U, cv::Scalar(0));

    while (1) {
        cap >> image;
        cvtColor(image, image, cv::COLOR_BGR2GRAY);
        equalizeHist(image, eq_image);

        cv::calcHist(&image, 1, 0, cv::Mat(), hist, 1, &nbins, &histrange, uniform, accumulate);
        cv::calcHist(&eq_image, 1, 0, cv::Mat(), histEq, 1, &nbins, &histrange, uniform, accumulate);

        cv::normalize(hist, hist, 0, histImg.rows, cv::NORM_MINMAX, -1, cv::Mat());
        cv::normalize(histEq, histEq, 0, histImgEq.rows, cv::NORM_MINMAX, -1, cv::Mat());

        histImg.setTo(cv::Scalar(0));
        histImgEq.setTo(cv::Scalar(0));

        for (int i = 0; i < nbins; i++) {
            cv::line(histImg,
                cv::Point(i, histh),
                cv::Point(i, histh - cvRound(hist.at<float>(i))),
                cv::Scalar(255), 1, 8, 0);
        }

        histImg.copyTo(image(cv::Rect(0, 0, nbins, histh)));

        for (int i = 0; i < nbins; i++) {
            cv::line(histImgEq,
                cv::Point(i, histh),
                cv::Point(i, histh - cvRound(histEq.at<float>(i))),
                cv::Scalar(255), 1, 8, 0);
        }

        histImgEq.copyTo(eq_image(cv::Rect(0, 0, nbins, histh)));

        cv::imshow("image", image);
        cv::imshow("equalized image", eq_image);

        key = cv::waitKey(30);  
        if (key == 27) break;
    }

	return 0;
}