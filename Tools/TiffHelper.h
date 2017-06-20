#pragma once
#include <QVector>
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
typedef QVector<cv::Mat> VTMats;
class CTiffHelper
{
public:
    CTiffHelper();
    ~CTiffHelper();
    VTMats ReadMultiPage(const char*, int nr_channels);
    void WriteMultTiff(VTMats image_stack, const char*file);
};

