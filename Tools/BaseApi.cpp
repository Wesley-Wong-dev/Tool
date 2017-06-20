#include "BaseApi.h"

#include <QDir>
#include <QFile>
#include <QVector>
#include <QMap>

#include "ImgOpt.h"
#include "TiffHelper.h"

BaseApi::BaseApi()
{
}


BaseApi::~BaseApi()
{
}

QStringList BaseApi::ScanTiffFiles(QString dir)
{
    QStringList theList;
    theList << "*.tif";

    QDir theDir(dir);
    theDir.setNameFilters(theList);

    QStringList theFiles;

    QFileInfoList list = theDir.entryInfoList();
    for ( int i = 0; i < list.size();i++ )
    {
        QFileInfo theFileInfo = list.at(i);
        theFiles.push_back(theFileInfo.filePath());
    }
    return theFiles;
}

QStringList BaseApi::ScanBoxFiles(QString dir)
{
    QStringList theList;
    theList << "*.box";

    QDir theDir(dir);
    theDir.setNameFilters(theList);

    QStringList theFiles;
    QFileInfoList list = theDir.entryInfoList();
    for (int i = 0; i < list.size(); i++)
    {
        QFileInfo theFileInfo = list.at(i);
        theFiles.push_back(theFileInfo.filePath());
    }
    return theFiles;
}

bool BaseApi::CreateMultTiff( QString strFileName, QStringList theFiles )
{
    VTMats theMats;
    for ( int i = 0; i < theFiles.size(); i++ )
    {
        ImgOpt theOpt;
        if ( theOpt.LoadImg(theFiles.at(i)) )
        {
            cv::Mat theMat = theOpt.GetMat();
            theMats.push_back(theMat);
        }
    }
    
    CTiffHelper theObj;
    theObj.WriteMultTiff(theMats, strFileName.toLocal8Bit().constData());
    return false;
}

bool BaseApi::CreateMultBox(QString strFileName, QStringList theFiles)
{
    QFile theNewFile(strFileName);
    theNewFile.open(QIODevice::WriteOnly | QIODevice::Text);

    for (int i = 0; i < theFiles.size(); i++)
    {
        QFile theFile(theFiles.at(i));
        if ( theFile.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            while (!theFile.atEnd())
            {
                QByteArray theLine = theFile.readLine();
                theLine.replace('\n', ' ');
                QList<QByteArray> theLineItem = theLine.split(' ');
                QString theText = QString("%1 %2 %3 %4 %5 %6\n")
                    .arg(theLineItem.at(0).constData())
                    .arg(theLineItem.at(1).constData())
                    .arg(theLineItem.at(2).constData())
                    .arg(theLineItem.at(3).constData())
                    .arg(theLineItem.at(4).constData()).
                    arg(i);
                theNewFile.write(theText.toLatin1().constData());
            }
        }
        theFile.close();
    }
    theNewFile.close();
    return false;
}

QStringList BaseApi::GetCharCount(QString strFilePath)
{
    int vtUp[26] = {0};
    int vtDown[26] = { 0 };
    QStringList theList;
    QFile theFile(strFilePath);
    if (theFile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        while (!theFile.atEnd())
        {
            QByteArray theLine = theFile.readLine();
            QList<QByteArray> theLineItem = theLine.split(' ');
            if ( theLineItem.at(0).size() >= 1)
            {
                const char* lpData = theLineItem.at(0).data();
                int nNum = lpData[0];

                if (nNum >= 'a' && nNum <= 'z')
                {
                    vtDown[nNum - 'a']++;
                }
                if (nNum >= 'A' && nNum <= 'Z')
                {
                    vtUp[nNum - 'A']++;
                }
            }
            
        }
    }
    for (int i = 0; i < sizeof(vtUp)/sizeof(int); i++ )
    {
        if ( vtUp[i] == 0 )
        {
            theList.push_back(QString("%1 : [%2]").arg((char)(i + 'A')).arg(vtUp[i]));
        }
        if ( vtDown[i] == 0 )
        {
            theList.push_back(QString("%1 : [%2]").arg((char)(i + 'a')).arg(vtDown[i]));
        }
    }

    return theList;
}

QStringList BaseApi::GetBoxByIndex(const QString strFilePath,int nIndex )
{
    QFileInfo theInfo = QFileInfo(strFilePath);
    QString strPath = theInfo.path();
    QString strName = theInfo.baseName();

    QStringList theList;
    QFile theFile(QString("%1\\%2.box").arg(strPath).arg(strName));
    if (theFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!theFile.atEnd())
        {
            QByteArray theLine = theFile.readLine();
            theLine.replace('\n', ' ');
            QList<QByteArray> theLineItem = theLine.split(' ');
            if (theLineItem.size() >= 5)
            {
                if ( QString::number(nIndex) == theLineItem.at(5))
                {
                    theList.push_back(theLine);
                }
                
            }
        }
    }
    theFile.close();
    return theList;
}
