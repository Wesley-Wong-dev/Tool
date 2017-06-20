#pragma once
#include <QObject>
#include <QImage>

#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
using namespace cv;

typedef  QVector<int> VTInts;
typedef QVector<Rect> VTRects;
typedef QVector<CvPoint> VTPoints;
typedef QVector<Mat> VTMats;

#include "TiffHelper.h"

typedef struct _Box
{
    QString  ch;
    Rect theRect;
}DataBox;
typedef QVector<DataBox> VTDataBox;


class ImgOpt
{
public:
    ImgOpt();
    ~ImgOpt();
public:
    QImage ImgResize(int nNum);

    QImage GrayScale();

    QImage Binarization(int nNum);
    QImage Binarization();

    QImage GetQImage() { return m_theImg; }
    cv::Mat GetMat() {
        return QImage2Mat(m_theImg);
    }
    bool LoadImg(const QString strFilePath);
    int     LoadTiff(const QString strFilePath);

    QImage GetTiffPageByIndex(int nIndex);

    void FromQImg(QImage theImg) { m_theImg = theImg; }
    QImage Projection();
	QImage ProjectionSeg();
	VTRects GetImgRects() { return m_thevtMats; }
    VTDataBox GetImgRectsByFile(const QStringList&,int nHeight);
    bool SaveTIF( const QString strFilePath );
    bool SaveBox(const QString strFilePath,const VTDataBox&);
	QImage DrawRects(VTRects);
private:
	VTRects SplitImg();
    VTPoints        GetPointsByMat(cv::Mat&,int ,int, int, int, int);
    VTRects FindFontContour(VTRects&);
    VTRects FindRectsByProjection(cv::Mat&);
	void RectAngleByMats(Mat& theDestMat, VTRects& thevtMats);
private:
    //GrayScale
    void OnGrayScale(cv::Mat input, cv::Mat& output);
    //Binarization
    void OnBinarization(cv::Mat input, cv::Mat& output, int nNum);
    void OnAutoBinarization(cv::Mat input, cv::Mat& output);
    QImage Mat2QImage(cv::Mat const& src);
    Mat QImage2Mat(QImage const& src );
private:
    QImage m_theImg;
	VTRects m_thevtMats;
    VTMats m_theTifMats;
};

