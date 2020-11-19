#include "processimage.h"

ProcessImage::ProcessImage()
{

}

QStringList ProcessImage::get_all_image_file(QString dirPath, QStringList extension)
{
    QStringList result;
        QDirIterator it(dirPath, QStringList() << extension, QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext())
        {
            QString absolutePath = it.filePath();
            if(absolutePath!="")
            result.push_back(absolutePath);

             it.next();
        }
        QString absolutePath = it.filePath();
        if(absolutePath!="")
        result.push_back(absolutePath);
        std::cout<<"get all file size: "<<result.size();
        return result;
}

void ProcessImage::fastNlMeansDenoising(cv::Mat imgIn, cv::Mat &imgOut)//lam min da
{
    cv::fastNlMeansDenoisingColored(imgIn, imgOut,10,10,7,21);
}

void ProcessImage::convet_to_gray(QString forderPath)
{
    cv::Mat out;
    QStringList extention = {"*.jpg","*.png"};
        QStringList listImage = get_all_image_file(forderPath,extention);
        for (int i=0;i<listImage.size();i++)
        {
            std::string temp=listImage.at(i).toLocal8Bit().constData();
            cv::Mat imgIn = cv::imread(temp);
            //bien doi anh o day
            cv::cvtColor(imgIn,out,cv::COLOR_BGR2GRAY);
            //end
            temp = temp.substr(0,temp.length()-4)+"_gray.png";   //luu anh voi ten moi
            std::cout<<"saved in :"<<temp<<std::endl;
            cv::imwrite(temp,out);
        }
}

void ProcessImage::convet_to_fastNlMeansDenoising(QString forderPath)
{
    cv::Mat out;
    QStringList extention = {"*.jpg","*.png"};
        QStringList listImage = get_all_image_file(forderPath,extention);
        for (int i=0;i<listImage.size();i++)
        {
            std::string temp=listImage.at(i).toLocal8Bit().constData();
            cv::Mat imgIn = cv::imread(temp);
            fastNlMeansDenoising(imgIn,out);
            temp = temp.substr(0,temp.length()-4)+"_Denoise.png";
            std::cout<<"saved in :"<<temp<<std::endl;
            cv::imwrite(temp,out);
        }
}

void ProcessImage::convet_to_blu(QString forderPath)
{
    cv::Mat out;
    QStringList extention = {"*.jpg","*.png"};
        QStringList listImage = get_all_image_file(forderPath,extention);
        for (int i=0;i<listImage.size();i++)
        {
            std::string temp=listImage.at(i).toLocal8Bit().constData();
            cv::Mat imgIn = cv::imread(temp);
            cv::blur(imgIn,out,cv::Size(10,10));
            temp = temp.substr(0,temp.length()-4)+"_blu.png";
            std::cout<<"saved in :"<<temp<<std::endl;
            cv::imwrite(temp,out);
        }
}

void ProcessImage::convet_to_MedianBlur(QString forderPath)
{
    cv::Mat out;
    QStringList extention = {"*.jpg","*.png"};
        QStringList listImage = get_all_image_file(forderPath,extention);
        for (int i=0;i<listImage.size();i++)
        {
            std::string temp=listImage.at(i).toLocal8Bit().constData();
            cv::Mat imgIn = cv::imread(temp);
            cv::medianBlur(imgIn,out,2);
            temp = temp.substr(0,temp.length()-4)+"_medianBlur.png";
            std::cout<<"saved in :"<<temp<<std::endl;
            cv::imwrite(temp,out);
        }
}


void ProcessImage::convet_canbangsang(QString forderPath)
{
    cv::Mat out;
    QStringList extention = {"*.jpg","*.png"};
        QStringList listImage = get_all_image_file(forderPath,extention);
        for (int i=0;i<listImage.size();i++)
        {
            std::string temp=listImage.at(i).toLocal8Bit().constData();
            cv::Mat imgIn = cv::imread(temp);
            lamNet2(imgIn,out);
            temp = temp.substr(0,temp.length()-4)+"_canbangsang.png";
            std::cout<<"saved in :"<<temp<<std::endl;
            cv::imwrite(temp,out);
        }
}

void ProcessImage::lamNet2(cv::Mat imgInput, cv::Mat &imgOutput)
{
    cv::Mat lab_image;
    cv::cvtColor(imgInput, lab_image,cv::COLOR_BGR2Lab);
    // Extract the L channel
    std::vector<cv::Mat> lab_planes(3);
    cv::split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]
   // apply the CLAHE algorithm to the L channel
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    clahe->setClipLimit(4);
    cv::Mat dst;
    clahe->apply(lab_planes[0], dst);

    // Merge the the color planes back into an Lab image
    dst.copyTo(lab_planes[0]);
    cv::merge(lab_planes, lab_image);

   // convert back to RGB
    cv::cvtColor(lab_image,imgOutput,cv::COLOR_Lab2BGR);
}

void ProcessImage::addNoisy(cv::Mat imgInput, cv::Mat &imgOutput)
{
    cv::Mat noise(imgInput.size(),imgOutput.type());
    float m = (10,12,34);
    float sigma = (1,5,50);
    cv::randn(noise,m,sigma);
    imgOutput += noise;
}

void ProcessImage::convert_to_addNoisy(QString forderPath)
{
    cv::Mat out;
    QStringList extention = {"*.jpg","*.png"};
        QStringList listImage = get_all_image_file(forderPath,extention);
        for (int i=0;i<listImage.size();i++)
        {
            std::string temp=listImage.at(i).toLocal8Bit().constData();
            cv::Mat imgIn = cv::imread(temp);
            cv::imshow("text",imgIn);
            addNoisy(imgIn,imgIn);
            temp = temp.substr(0,temp.length()-4)+"_addNoise.png";
            std::cout<<"saved in :"<<temp<<std::endl;
            cv::imwrite(temp,imgIn);
        }
}

void ProcessImage::convertOne(QString forderPath)
{

}

void ProcessImage::sharpness(cv::Mat imgIn, cv::Mat &imgOut)
{
    cv::GaussianBlur(imgIn,imgOut,cv::Size(0,0),3);
    cv::addWeighted(imgIn,1.5, imgOut,-0.5, 0, imgOut);
}

void ProcessImage::convert_to_sharpness(QString forderPath)
{
    cv::Mat out;
    QStringList extention = {"*.jpg","*.png"};
        QStringList listImage = get_all_image_file(forderPath,extention);
        for (int i=0;i<listImage.size();i++)
        {
            std::string temp=listImage.at(i).toLocal8Bit().constData();
            cv::Mat imgIn = cv::imread(temp);
            cv::imshow("text",imgIn);
            sharpness(imgIn,out);
            temp = temp.substr(0,temp.length()-4)+"_shapness.png";
            std::cout<<"saved in :"<<temp<<std::endl;
            cv::imwrite(temp,out);
        }
}

void ProcessImage::removeRegion(cv::Mat src)
{
    cv::Mat img(src.size(),src.type());
    img = cv::Scalar(0,0,0);
    int x,y,w,h;
    do
    {
        x= rand() % (src.cols - (src.cols /10) -1);
        y= rand() % (src.rows - (src.rows/10) -1 );
        w= rand() % (src.cols /10)+1;
        h= rand() % (src.rows /10)+1;
    }while(x>src.cols-w | y>src.rows-h);
    printf("\nkich thuoc anh: %d,%d\n",src.cols,src.rows);
    printf("random: %d,%d,%d,%d\n",x,y,w,h);
    cv::Rect roi = cv::Rect(x,y,w,h);
    img = img(roi);
    img.copyTo(src(cv::Rect(x,y,w,h)));
}

void ProcessImage::convert_to_removeRegion(QString forderPath)
{
    cv::Mat out;
    QStringList extention = {"*.jpg","*.png"};
        QStringList listImage = get_all_image_file(forderPath,extention);
        for (int i=0;i<listImage.size();i++)
        {
            std::string temp=listImage.at(i).toLocal8Bit().constData();
            cv::Mat imgIn = cv::imread(temp);
            removeRegion(imgIn);
            temp = temp.substr(0,temp.length()-4)+"_removeRegion.png";
            std::cout<<"saved in :"<<temp<<std::endl;
            cv::imwrite(temp,imgIn);
        }
}

void ProcessImage::transform1(cv::Mat img)
{
    double I[2][3] = {1,0.5,0,0,1,0};
    cv::Mat mat_rot(2,3,CV_64F,I);
    cv::warpAffine(img,img,mat_rot,img.size());
}

void ProcessImage::convert_to_transform1(QString forderPath)
{
    QStringList extention = {"*.jpg","*.png"};
        QStringList listImage = get_all_image_file(forderPath,extention);
        for (int i=0;i<listImage.size();i++)
        {
            std::string temp=listImage.at(i).toLocal8Bit().constData();
            cv::Mat imgIn = cv::imread(temp);
            transform1(imgIn);
            temp = temp.substr(0,temp.length()-4)+"_transform1.png";
            std::cout<<"saved in :"<<temp<<std::endl;
            cv::imwrite(temp,imgIn);
        }
}

void ProcessImage::transform2(cv::Mat src, cv::Mat &dst)
{
    cv::Point2f srcTri[3];
    srcTri[0] = cv::Point2f( 0.f, 0.f );
    srcTri[1] = cv::Point2f( src.cols - 1.f, 0.f );
    srcTri[2] = cv::Point2f( 0.f, src.rows - 1.f );
    cv::Point2f dstTri[3];
    dstTri[0] = cv::Point2f( 0.f, src.rows*0.33f );
    dstTri[1] = cv::Point2f( src.cols*2.0f, src.rows*0.25f );
    dstTri[2] = cv::Point2f( 0.f, src.rows - 1.f);
   cv::Mat warp_mat = cv::getAffineTransform(srcTri,dstTri);
   dst = cv::Mat::zeros(src.size(),src.type());
   cv::warpAffine(src,dst,warp_mat,dst.size());
}

void ProcessImage::convert_transform2(QString forderPath)
{
    cv::Mat out;
    QStringList extention = {"*.jpg","*.png"};
        QStringList listImgage = get_all_image_file(forderPath,extention);
        for(int i=0;i<listImgage.size();i++)
        {
            std::string temp = listImgage.at(i).toLocal8Bit().constData();
            cv::Mat imgIn = cv::imread(temp);
            transform2(imgIn,out);
            temp = temp.substr(0,temp.length()-4)+"transform2.png";
            std::cout<<"saved in :"<<temp<<std::endl;
            cv::imwrite(temp,imgIn);
        }
}

void ProcessImage::transformMatrix2D(cv::Mat src, cv::Mat &dst)
{
    int n=2;
   dst = cv::Mat::zeros(src.size(),src.type());
   cv::Point center = cv::Point(src.cols/n,src.rows/n);
   double angle = -50.0;
   double scale = 0.6;
   cv::Mat rot_mat = cv::getRotationMatrix2D(center,angle,scale);
   cv::warpAffine(src,dst,rot_mat,dst.size());
}

void ProcessImage::convert_transformMatrix2D(QString forderPath)
{
    cv::Mat out;
    QStringList extention = {"*.jpg","*.png"};
        QStringList listImgage = get_all_image_file(forderPath,extention);
        for(int i=0;i<listImgage.size();i++)
        {
            std::string temp = listImgage.at(i).toLocal8Bit().constData();
            cv::Mat imgIn = cv::imread(temp);
            transformMatrix2D(imgIn,out);
            temp = temp.substr(0,temp.length()-4)+"trfM2D.png";
            std::cout<<"saved in :"<<temp<<std::endl;
            cv::imwrite(temp,imgIn);
        }
}



//    /home/tuanp/Data/zalo/za_traffic_2020/traffic_public_test/images/0.jpg
 //   /home/tuanp/Data/zalo/za_traffic_2020/traffic_public_test/images/0_gray.jpg
