#pragma once

#include <QtWidgets/QDialog>
#include "ui_Tools.h"
#include "ImgOpt.h"
#include <QStandardItemModel>

#include <QSpinBox>


Q_DECLARE_METATYPE(Rect	)

class Tools : public QDialog
{
    Q_OBJECT

public:
    Tools(QWidget *parent = Q_NULLPTR);

private slots:
    //btn_Load
    void on_btn_Load_clicked();
    //btn_GS
    void on_btn_GS_clicked();
    //btn_Bin
    void on_btn_Bin_clicked();
    //hs_Num
    void on_hs_Num_Changed(int);
    //hs_Zoom
    void on_hs_Zoom_Changed(int);
    //hs_Zoom_Report
    void on_hs_Zoom_Report_Changed(int);
    //btn_Seg
    void on_btn_Seg_clicked();
	//btn_Insert
	void on_btn_Insert_clicked();

    void on_btn_Save_clicked();

    void on_btn_MergeBox_clicked();

    void on_btn_Up_clicked();
    void on_btn_Down_clicked();

    //cmb_Seg
    void on_cmb_Seg_currentIndexChanged(int);
public slots :
	void on_LV_List_itemChanged(QStandardItem*);
    void on_LV_List_Clicked(const QModelIndex&);


    void on_SB_Height_ValueChanged(int);
    void on_SB_Width_ValueChanged(int);
    void on_SB_X_ValueChanged(int);
    void on_SB_Y_ValueChanged(int);
    void on_Edit_Char_TextChanged(const QString&);
protected:
    virtual bool eventFilter(QObject *o, QEvent *e);
private:
    void ShowImg(QImage);
    void ShowImgReport(QImage);
	void AddTableViewRow(QList<QStandardItem*> theRow);
	void ClearTableView();
	void AddRow(QString, Rect);
    VTDataBox GetRowData();
    void ShowRectImg();

private:
    Ui::ToolsClass ui;
    QString   m_strImgPath;

    QImage   m_theImg;
	QImage   m_theRGBImg;
    QImage   m_theRepImg;
    int            m_nIndex;
};
