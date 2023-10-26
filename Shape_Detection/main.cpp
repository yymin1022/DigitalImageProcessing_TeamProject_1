#include "main.hpp"

using namespace cv;
using namespace std;

int main() {
    Mat imgs[4];

    if(detectShape("1.png", &imgs[0]))
        imshow("1.png", imgs[0]);
    if(detectShape("2.png", &imgs[1]))
        imshow("2.png", imgs[1]);
    if(detectShape("3.png", &imgs[2]))
        imshow("3.png", imgs[2]);
    if(detectShape("4.png", &imgs[3]))
        imshow("4.png", imgs[3]);

    waitKey(0);
    return 0;
}

bool detectShape(string fileName, Mat* img_org) {
    Mat img_gray, img_bin;
    vector<vector<Point>> contours;

    *img_org = imread(fileName, IMREAD_COLOR);
    if ((*img_org).empty()) {
        cout << "Image Not Found: " << fileName << endl;
        return false;
    }

    imageColorToGray(*img_org, img_gray);
    imageGrayToBin(img_gray, img_bin);
    findContours(img_bin, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    vector<Point2f> approx;
    for (size_t i = 0; i < contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx,
            arcLength(Mat(contours[i]), true) / 100, true);
        if (fabs(contourArea(Mat(approx))) < 100000) {
            int size = approx.size();
            if (size == 3)
                showLabel(*img_org, "Triangle", contours[i]);
            else
                showLabel(*img_org, "Circle", contours[i]);
        }
    }

    return true;
}

void imageColorToGray(Mat& org, Mat& res) {
    int cols = org.cols;
    int rows = org.rows;
    res.create(org.size(), CV_8UC1);

    if(org.isContinuous() && res.isContinuous()) {
        cols = rows * cols;
        rows = 1;
    }

    for(int r = 0; r < rows; r++) {
        uchar* pointer_row = org.ptr<uchar>(r);
        uchar* pointer_row_gray = res.ptr<uchar>(r);

        for(int c = 0; c < cols; c++) {
            pointer_row_gray[c] =
                (uchar)(0.3f * pointer_row[0] +
                    0.6f * pointer_row[1] +
                    0.1f * pointer_row[2]);
            pointer_row += 3;
        }
    }
}

void imageGrayToBin(Mat& org, Mat& res) {
    int cols = org.cols;
    int rows = org.rows;
    res.create(org.size(), CV_8UC1);

    if (org.isContinuous() && res.isContinuous()) {
        cols = rows * cols;
        rows = 1;
    }

    for(int r = 0; r < rows; r++) {
        uchar* pointer_row = org.ptr<uchar>(r);
        uchar* pointer_row_binary = res.ptr<uchar>(r);

        for(int c = 0; c < cols; c++) {
            if(pointer_row[c] > 30)
                pointer_row_binary[c] = 255;
            else
                pointer_row_binary[c] = 0;
        }
    }
}

void showLabel(Mat& img, string str, vector<Point> contour) {
    int baseline = 0;

    Size text = getTextSize(str, FONT_HERSHEY_SIMPLEX, 0.75, 1, &baseline);
    Rect r = boundingRect(contour);
    Point pt(r.x + ((r.width - text.width) / 2),
        r.y + ((r.height + text.height) / 2));

    rectangle(img, pt + Point(0, baseline),
        pt + Point(text.width, -text.height),
        CV_RGB(120, 120, 120),
        FILLED);

    putText(img, str, pt, FONT_HERSHEY_SIMPLEX, 0.75, CV_RGB(0, 0, 0), 1, 8);
}