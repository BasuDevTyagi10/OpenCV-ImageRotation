#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat rotate(Mat src,int angle){
    Point2f center((src.cols-1)/2.0, (src.rows-1)/2.0);
    Mat rot = getRotationMatrix2D(center, angle, 1.0);
    Rect2f bbox = RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
    rot.at<double>(0,2) += bbox.width/2.0 - src.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - src.rows/2.0;
    Mat final_img;
    warpAffine(src, final_img, rot, bbox.size());
    return final_img;
}

int main() {
    cout<<"Enter Image File Path : ";
    string imgPath;
    getline(cin,imgPath);
    Mat img = imread(imgPath,IMREAD_UNCHANGED);
    if(img.empty()){
        cout<<"ERROR Loading Image File."<<endl;
        return -1;
    }
    cout<<"Enter Angle : ";
    int angle;
    cin>>angle;
    angle = angle%360;
    Mat rotated = rotate(img,angle);
    if(rotated.empty()){
        cout<<"ERROR Rotating Image."<<endl;
        return -1;
    }
    imshow("Original", img);
    imshow("Rotated", rotated);
    waitKey(0);
    return 0;
}