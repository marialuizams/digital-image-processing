#include <iostream>
#include <opencv2/opencv.hpp>
#include "motiondetector.h"

using namespace cv;

int motiondetector() {
    cv::Mat frame1, frame2;
    int width, height;
    cv::VideoCapture cap;
    std::vector<cv::Mat> planes;
    cv::Mat histR1, histR2;
    cv::Vec3b val;
    int nbins = 64;
    float range[] = { 0, 255 }, comp = 0;
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
    cv::Mat histImgR(histh, histw, CV_8UC3, cv::Scalar(0, 0, 0));


    while (1) {
        cap >> frame1;
        cv::split(frame1, planes);
        cv::calcHist(&planes[0], 1, 0, cv::Mat(), histR1, 1, &nbins, &histrange, uniform, acummulate);

        cv::normalize(histR1, histR1, 0, histImgR.rows, cv::NORM_MINMAX, -1, cv::Mat());

        histImgR.setTo(cv::Scalar(0));

        cap >> frame2;
        cv::split(frame2, planes);
        cv::calcHist(&planes[0], 1, 0, cv::Mat(), histR2, 1, &nbins, &histrange, uniform, acummulate);

        cv::normalize(histR2, histR2, 0, histImgR.rows, cv::NORM_MINMAX, -1, cv::Mat());

        comp = compareHist(histR1, histR2, 4);

        //std::cout << comp << std::endl;
        val[0] = 0;   //B
        val[1] = 0;   //G
        val[2] = 255; //R

        if (comp > 7) {
            std::cout << "Movimento detectado!" << std::endl;

            for (int i = 420; i < 460; i++) {
                for (int j = 580; j < 620; j++) {
                    frame1.at<Vec3b>(i, j) = val;
                }
            }
        }

        for (int i = 0; i < nbins; i++) {
            cv::line(histImgR,
                cv::Point(i, histh),
                cv::Point(i, histh - cvRound(histR1.at<float>(i))),
                cv::Scalar(0, 0, 255), 1, 8, 0);
        }
        histImgR.copyTo(frame1(cv::Rect(0, 0, nbins, histh)));

        cv::imshow("Motion Detector", frame1);
        key = cv::waitKey(30);
        if (key == 27) break;
    }
    return 0;
}