#include "test.h"

Test::Test()
{

}

void Test::testConvtImage()
{
    ProcessImage pro;
    QString forderPath = "/home/tuanp/Data/zalo/za_traffic_2020/traffic_public_test/images/";
//    pro.convet_to_fastNlMeansDenoising(forderPath);
//    pro.convet_to_gray(forderPath);
   // pro.convet_canbangsang(forderPath);
   // pro.convert_to_addNoisy(forderPath);
    //pro.convert_to_sharpness(forderPath);
    //pro.convert_to_removeRegion(forderPath);
    pro.convert_to_transform1(forderPath);
    pro.convert_transform2(forderPath);
    pro.convert_transformMatrix2D(forderPath);
}
