#ifndef PROCESSIMAGE_H
#define PROCESSIMAGE_H
#include <QStringList>
#include <QDirIterator>
#include <QDir>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/photo.hpp"
#include <opencv2/core.hpp>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>
#include <vector>       // std::vector
class ProcessImage
{
public:
    ProcessImage();
    QStringList get_all_image_file(QString dirPath, QStringList extension);
    void fastNlMeansDenoising(cv::Mat imgIn, cv::Mat &imgOut);
    void convet_to_gray(QString folderPath);
    void convet_to_fastNlMeansDenoising(QString forderPath);
    void convet_to_blu(QString forderPath);
    void convet_to_MedianBlur(QString forderPath);
    void convet_canbangsang(QString forderPath);
    void lamNet2(cv::Mat imgInput,cv::Mat &imgOutput);
    void addNoisy(cv::Mat imgInput,cv::Mat &imgOutput);
    void convert_to_addNoisy(QString forderPath);
    void convertOne(QString forderPath);

    void sharpness(cv::Mat imgIn, cv::Mat &imgOut);
    void convert_to_sharpness(QString forderPath);
    void removeRegion(cv::Mat img);
    void convert_to_removeRegion(QString forderPath);
    void transform1(cv::Mat img);
    void convert_to_transform1(QString forderPath);
    void transform2(cv::Mat src, cv::Mat &dst);
    void convert_transform2(QString forderPath);
    void transformMatrix2D(cv::Mat src, cv::Mat &dst);
    void convert_transformMatrix2D(QString forderPath);
};

#endif // PROCESSIMAGE_H
