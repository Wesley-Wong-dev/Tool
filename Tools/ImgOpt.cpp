#include "ImgOpt.h"
#include <QPixmap>
#include <QFile> 
#include "TiffHelper.h"

ImgOpt::ImgOpt()
{
}


ImgOpt::~ImgOpt()
{
}

bool ImgOpt::LoadImg(QString strFilePath)
{
        return m_theImg.load(strFilePath);
}

int ImgOpt::LoadTiff(const QString strFilePath)
{
    CTiffHelper theHelper;
    m_theTifMats = theHelper.ReadMultiPage(strFilePath.toLatin1().constData(), 1);
    return m_theTifMats.size();
}


QImage ImgOpt::GetTiffPageByIndex(int nIndex)
{
    if (nIndex <= 0 || nIndex > m_theTifMats.size())
    {
        return QImage();
    }

    return Mat2QImage(m_theTifMats.at(nIndex - 1));
}

QImage ImgOpt::Projection()
{
    QImage theRetImg;
    if ( !m_theImg.isGrayscale() )
    {
        return theRetImg;
    }
    
    cv::Mat theSrcMat = QImage2Mat(m_theImg);

    int nPerPixelValue = 0;
    int *lpProjectValArry = new int[m_theImg.width()];
    memset(lpProjectValArry, 0, m_theImg.width() * sizeof(int));


    for (  int nCol = 0; nCol < m_theImg.width(); nCol++ )
    {
        for ( int nRow = 0; nRow < m_theImg.height(); nRow++ )
        {
            nPerPixelValue = theSrcMat.at<uchar>(nRow, nCol);
            if ( nPerPixelValue == 0xff )
            {
                lpProjectValArry[nCol]++;
            }
        }
    }

    nPerPixelValue = 0xff;
    Mat VerticalProjectionMat(m_theImg.height(), m_theImg.width(), CV_8UC1 );
    for (int i = 0; i < m_theImg.height(); i++ )
    {
        for ( int j = 0; j < m_theImg.width(); j++ )
        {        
            VerticalProjectionMat.at<uchar>(i, j) = nPerPixelValue;
        }
    }
    nPerPixelValue = 0;
    for (int i = 0; i < m_theImg.width(); i++)
    {
        for (int j = 0; j < lpProjectValArry[i]; j++)
        {
            VerticalProjectionMat.at<uchar>( m_theImg.height() - 1 -j, i ) = nPerPixelValue;
        }
    }


    theRetImg = Mat2QImage(VerticalProjectionMat);
    delete[] lpProjectValArry;

    return theRetImg;
}

QImage ImgOpt::ProjectionSeg()
{
	cv::Mat theSrcMat = QImage2Mat(m_theImg);
	cv::Mat theDestMat;
	theDestMat.create(theSrcMat.rows, theSrcMat.cols, CV_8UC3);
	cvtColor(theSrcMat, theDestMat, CV_GRAY2BGR);
	m_thevtMats = SplitImg();
	RectAngleByMats(theDestMat, m_thevtMats);
    m_theImg = Mat2QImage(theDestMat);
	return m_theImg;
}

VTDataBox ImgOpt::GetImgRectsByFile(const QStringList& theList, int nHeight)
{
    VTDataBox theDataBoxs;
    for (int i =0;i < theList.size();i++)
    {
        QString theStr = theList.at(i);
        QStringList theLineItem = theStr.split(' ');
        DataBox theBox;
        theBox.ch = theLineItem.at(0);
        theBox.theRect;
        theBox.theRect.x = theLineItem.at(1).toInt();
        theBox.theRect.y = nHeight - theLineItem.at(4).toInt();
        theBox.theRect.width = theLineItem.at(3).toInt() - theBox.theRect.x;
        theBox.theRect.height = nHeight -  theLineItem.at(2).toInt()- theBox.theRect.y -1;
        //QString strData = QString("%1 %2 %3 %4 %5 %6\n").arg(theBox.ch).arg(theBox.theRect.x).arg(nHeight - (theBox.theRect.y + theBox.theRect.height + 1)).arg(theBox.theRect.x + theBox.theRect.width).arg(nHeight - theBox.theRect.y).arg(0);
        theDataBoxs.push_back(theBox);
    }
    return theDataBoxs;
}

bool ImgOpt::SaveTIF(const QString strFilePath)
{
    cv::Mat theSrcMat = QImage2Mat(m_theImg);
//     std::vector<uchar> theBuff;
// 
//     std::vector<int> param = std::vector<int>(2);
//     param[0] = CV_IMWRITE_PAM_FORMAT_GRAYSCALE;
// 
//     imencode(".tif", theSrcMat, theBuff, param);
//     cv::Mat theDestMat;
//     theDestMat.create(theSrcMat.rows, theSrcMat.cols, theSrcMat.type());
    return  imwrite(strFilePath.toStdString().c_str(), theSrcMat);
}

bool ImgOpt::SaveBox(const QString strFilePath, const VTDataBox& theDataBox )
{
    QFile theFile(strFilePath);
    if (!theFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    int nHeight = m_theImg.height();
    for (int i =0; i < theDataBox.size(); i++ )
    {
        DataBox theBox = theDataBox.at(i);
        QString strData = QString("%1 %2 %3 %4 %5 %6\n").arg(theBox.ch).arg(theBox.theRect.x).arg(nHeight - (theBox.theRect.y+theBox.theRect.height+1)).arg(theBox.theRect.x+theBox.theRect.width).arg(nHeight - theBox.theRect.y).arg(0);
        theFile.write(strData.toLatin1().toStdString().c_str());
    }
    theFile.close();
    return true;
}

QImage ImgOpt::DrawRects(VTRects theRects)
{
	cv::Mat theSrcMat = QImage2Mat(m_theImg);
	cv::Mat theDestMat;
	theDestMat.create(theSrcMat.rows, theSrcMat.cols, CV_8UC3);
	cvtColor(theSrcMat, theDestMat, CV_GRAY2BGR);
	RectAngleByMats(theDestMat, theRects);
	return Mat2QImage(theDestMat);
}

void ImgOpt::RectAngleByMats(Mat& theDestMat, VTRects& thevtMats)
{
	for (int i = 0; i < thevtMats.size(); i++)
	{
		Rect theRect = thevtMats.at(i);
		theRect.x -= 1;
		theRect.y -= 1;
		theRect.height += 3;
		theRect.width += 2;
		rectangle(theDestMat, theRect, Scalar(0, 0, 255));
	}
}

VTRects ImgOpt::SplitImg()
{

    QImage theImgProjection = Projection();

    cv::Mat theReportMat = QImage2Mat(theImgProjection);

    VTRects vtMats = FindRectsByProjection(theReportMat);
    
    VTRects vtContour = FindFontContour(vtMats);
   
    return vtContour;
}

VTRects ImgOpt::FindRectsByProjection(cv::Mat& theSrcMat)
{
    VTInts vectorV, VUpper,VDown, HVectors;

    VTRects vtMats;
    VUpper.clear();
    VDown.clear();

    for (int i = 0; i < theSrcMat.cols; i++)
    {
        Mat data = theSrcMat.col(i);
        int itmp = countNonZero(data);
        vectorV.push_back(itmp);
    }

    for (int i = 1; i < vectorV.size(); i++)
    {
        if (vectorV.at(i - 1) == 0 && vectorV.at(i) > 0)
        {
            VUpper.push_back(i);
        }
        if (vectorV.at(i - 1) > 0 && vectorV.at(i) == 0)
        {
            VDown.push_back(i);
        }
    }

    for ( int i = 0; i < VUpper.size(); i++ )
    {
            int nMax = 0;
            int nBegin = VUpper.at(i);
            int nEnd= VDown.at(i);
            for (int j = nBegin; j < nEnd; j++ )
            {
                if ( vectorV.at(j) > nMax )
                {
                    nMax = vectorV.at(j);
                }
            }
            HVectors.push_back(nMax);
    }

    for (int i = 0; i < VUpper.size(); i++)
    {
        vtMats.push_back(Rect(VUpper.at(i), 0, VDown.at(i) - VUpper.at(i), theSrcMat.rows));
    }

    return vtMats;
}

VTPoints ImgOpt::GetPointsByMat(cv::Mat& theSrcMat, int nBegin, int nEnd, int nX, int nY, int nColor)
{
    VTPoints thePoints;
    int nPerPixelValue = 0;
    for (int nCol = nBegin; nCol < nX; nCol++)
    {
        for (int nRow = nEnd; nRow < nY; nRow++)
        {
            nPerPixelValue = theSrcMat.at<uchar>(nRow, nCol);
            if (nPerPixelValue == nColor)
            {
                CvPoint thePoint;
                thePoint.x = nCol;
                thePoint.y = nRow;
                thePoints.push_back(thePoint);
            }
        }
    }
    return thePoints;
}

VTRects ImgOpt::FindFontContour(VTRects& vtRects)
{
    VTRects theRects;

    cv::Mat theSrcMat = QImage2Mat(m_theImg);

    for (int i = 0; i < vtRects.size(); i++)
    {
        Rect theRect = vtRects.at(i);
        Mat theTemp = theSrcMat(theRect);
        
        VTPoints thePoints = GetPointsByMat(theTemp, 0, 0, theTemp.cols, theTemp.rows, 0x00);

        int nMinY = 0;
        int nMaxY = 0;
        for (int i = 0; i < thePoints.size(); i++)
        {
            CvPoint thePoint = thePoints.at(i);
            if (thePoint.y  > nMaxY)
            {
                nMaxY = thePoint.y;
            }
        }

        nMinY = nMaxY;

        for (int i = 0; i < thePoints.size(); i++)
        {
            CvPoint thePoint = thePoints.at(i);
            if (thePoint.y < nMinY)
            {
                nMinY = thePoint.y;
            }
        }

        theRects.push_back(Rect(Point2i(theRect.x, nMinY), Point2i(theRect.x + theRect.width, nMaxY)));
        /*
        Mat theNew = theSrcMat(Rect(Point2i(theRect.x, nMinY), Point2i(theRect.x+ theRect.width,  nMaxY)));
        cv::Mat theDestMat;
        CvSize dstSize;
        dstSize.width = theNew.cols  ;
        dstSize.height = theNew.rows;
        resize(theNew, theDestMat, dstSize);
        imshow(QString("%1").arg(i).toLocal8Bit().constData(), theDestMat);
        */
    }
    //cvWaitKey();
    return theRects;
}

void ImgOpt::OnGrayScale(Mat input, Mat& output)
{
    cvtColor(input, output, CV_BGR2GRAY);
}

void ImgOpt::OnBinarization(Mat input, Mat& output, int nNum)
{
    threshold(input, output, nNum, 255, THRESH_BINARY);
}

void ImgOpt::OnAutoBinarization(cv::Mat input, cv::Mat& output)
{
    threshold(input, output, 255, 255, THRESH_BINARY|THRESH_OTSU);
}

QImage ImgOpt::Mat2QImage(Mat const& src)
{
    switch (src.type())
    {
    case CV_8UC4:
    {
        QImage image(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_ARGB32);
        return image;
    }
    case CV_8UC3:
    {
        QImage image(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    case CV_8UC1:
    {
        QImage image(src.cols, src.rows, QImage::Format_Grayscale8);
		/*
        image.setColorCount(256);
        for (int i = 0; i < 256; i++ )
        {
            image.setColor(i, qRgb(i, i, i));
        }
		*/
        uchar* pSrc = src.data;
        for (int nRow = 0; nRow < src.rows; nRow++ )
        {
            uchar* pDest = image.scanLine(nRow);
            memcpy(pDest, pSrc, src.cols);
            pSrc += src.step;
        }
        return image;
    }
    default:
        break;
    }
    return QImage();
}

Mat ImgOpt::QImage2Mat(QImage const& src)
{
    switch (src.format() )
    {
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
    {
        cv::Mat theMat(src.height(), src.width(), CV_8UC4, const_cast<uchar*>(src.bits()), static_cast<size_t>(src.bytesPerLine()));
        return theMat;
    }
    case QImage::Format_RGB32:
    case QImage::Format_RGB888:
    {
        QImage swapped = src;
        if ( src.format() == QImage::Format_RGB32 )
        {
            swapped = swapped.convertToFormat(QImage::Format_RGB888);
        }
        swapped = swapped.rgbSwapped();
        return cv::Mat(swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.constBits()), static_cast<size_t>(swapped.bytesPerLine())).clone();
    }
    case QImage::Format_Indexed8:
    {
        return cv::Mat(src.height(), src.width(), CV_8UC1, const_cast<uchar*>(src.constBits()), static_cast<size_t>(src.bytesPerLine())).clone();
    }
    case QImage::Format_Grayscale8:
    {
        return cv::Mat(src.height(), src.width(), CV_8UC1, const_cast<uchar*>(src.constBits()), static_cast<size_t>(src.bytesPerLine())).clone();
    }
    default:
        break;
    }
    
    return Mat();
}

QImage ImgOpt::ImgResize(int nNum)
{
    if ( nNum == 0)
    {
        return m_theImg;
    }

    cv::Mat theSrcMat = QImage2Mat(m_theImg);

    cv::Mat theDestMat;
    CvSize dstSize;
    dstSize.width = theSrcMat.cols * (nNum > 10?10:nNum);
    dstSize.height = theSrcMat.rows * (nNum > 10 ? 10 : nNum);

	//pyrUp(theSrcMat, theDestMat, Size(theSrcMat.cols * 2, theSrcMat.rows * 2));
    resize(theSrcMat, theDestMat, dstSize,0,0, CV_INTER_NN);

	//imshow(QString("%1").arg(1).toLocal8Bit().constData(), theDestMat);
	//cvWaitKey();
    return Mat2QImage(theDestMat);
}

QImage ImgOpt::GrayScale()
{
    if ( m_theImg.isGrayscale() )
    {
        return m_theImg;
    }

    cv::Mat theSrcMat = QImage2Mat(m_theImg);

    cv::Mat theDestMat;

    OnGrayScale(theSrcMat,theDestMat );

    m_theImg = Mat2QImage(theDestMat);

    return m_theImg;
}

QImage ImgOpt::Binarization(int nNum)
{
    cv::Mat theSrcMat = QImage2Mat(m_theImg);

    cv::Mat theDestMat;

    OnBinarization(theSrcMat, theDestMat, nNum);

    return Mat2QImage(theDestMat);
}

QImage ImgOpt::Binarization()
{
    cv::Mat theSrcMat = QImage2Mat(m_theImg);

    cv::Mat theDestMat;

     OnAutoBinarization(theSrcMat, theDestMat);

     m_theImg = Mat2QImage(theDestMat);

    return m_theImg;
}
