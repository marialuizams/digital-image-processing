#include <iostream>
#include <opencv2/opencv.hpp>
#include "labeling.h"

using namespace cv;

int labeling() {
    cv::Mat image, realce;
    int width, height;
    int nobjects, holes;

    cv::Point p;
    image = cv::imread("bolhas.png", cv::IMREAD_GRAYSCALE);

    if (!image.data) {
        std::cout << "imagem nao carregou corretamente\n";
        return 0;
    }

    width = image.cols;
    height = image.rows;
    std::cout << width << "x" << height << std::endl;

    p.x = 0;
    p.y = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                if (image.at<uchar>(i, j) == 255)
                {
                    p.x = j;
                    p.y = i;
                    floodFill(image, p, 0);
                }
            }
        }
    }

    // busca objetos presentes
    nobjects = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (image.at<uchar>(i, j) == 255) {
                // achou um objeto
                nobjects++;
                p.x = j;
                p.y = i;
                // preenche o objeto com o contador
                cv::floodFill(image, p, nobjects);
            }
        }
    }

    p.x = 0;
    p.y = 0;

    cv:floodFill(image, p, 255);

    holes = 0;
    for (int i = 1; i < height; i++) 
    {
        for (int j = 1; j < width; j++) 
        {
            if (image.at<uchar>(i, j) == 0) 
            {
                holes++;
                p.x = j;
                p.y = i;
                floodFill(image, p, 255);
                p.x = j - 1;
                floodFill(image, p, 255);
            }
        }
    }

    std::cout << "A figura tem " << nobjects << " bolhas.\n";
    std::cout << holes << " bolhas com buracos e " << (nobjects - holes) << " bolhas sem buracos.\n";
    //cv::equalizeHist(image, realce);
    cv::imshow("image", image);
    //cv::imshow("realce", realce);
    cv::imwrite("labeling.png", image);
    cv::waitKey();
    return 0;
}