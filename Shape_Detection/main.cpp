#include "main.hpp"

using namespace cv;

int main(int ac, char** av) {

    Mat img = imread("Result.png");
    imshow("img", img);
    waitKey(0);

    return 0;
}