#pragma once
#include <QString>

class BaseApi
{
public:
    BaseApi();

    ~BaseApi();
    QStringList ScanTiffFiles(QString dir);
    QStringList ScanBoxFiles(QString dir);
    bool CreateMultTiff(QString strFileName,QStringList);
    bool CreateMultBox(QString strFileName, QStringList);
    QStringList GetCharCount(QString strFilePath);
    QStringList GetBoxByIndex(const QString strFilePath,int);
};

