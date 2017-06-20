/********************************************************************************
** Form generated from reading UI file 'Tools.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLS_H
#define UI_TOOLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ToolsClass
{
public:
    QGroupBox *groupBox;
    QLabel *lb_IMG;
    QTextEdit *Edit_Zoom;
    QSlider *hs_Num;
    QLabel *label;
    QPushButton *btn_Load;
    QPushButton *btn_Bin;
    QTextEdit *Edit_Threshold;
    QLabel *label_2;
    QSlider *hs_Zoom;
    QPushButton *btn_GS;
    QPushButton *btn_Up;
    QPushButton *btn_Down;
    QLabel *lb_Count;
    QGroupBox *groupBox_2;
    QLabel *lb_ImgReport;
    QComboBox *cmb_Seg;
    QTextEdit *Edit_Zoom_Report;
    QLabel *label_3;
    QSlider *hs_Zoom_Report;
    QPushButton *btn_Seg;
    QPushButton *btn_Merge;
    QPushButton *btn_Split;
    QPushButton *btn_Insert;
    QPushButton *btn_Delete;
    QTableView *LV_List;
    QSpinBox *SB_X;
    QSpinBox *SB_Y;
    QSpinBox *SB_Width;
    QSpinBox *SB_Height;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *LB_Char;
    QPushButton *btn_Save;
    QPushButton *btn_MergeBox;
    QTextEdit *Edit_Log;
    QLineEdit *Edit_Char;

    void setupUi(QDialog *ToolsClass)
    {
        if (ToolsClass->objectName().isEmpty())
            ToolsClass->setObjectName(QStringLiteral("ToolsClass"));
        ToolsClass->resize(1063, 760);
        groupBox = new QGroupBox(ToolsClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 691, 481));
        lb_IMG = new QLabel(groupBox);
        lb_IMG->setObjectName(QStringLiteral("lb_IMG"));
        lb_IMG->setGeometry(QRect(10, 10, 671, 261));
        Edit_Zoom = new QTextEdit(groupBox);
        Edit_Zoom->setObjectName(QStringLiteral("Edit_Zoom"));
        Edit_Zoom->setGeometry(QRect(160, 280, 51, 31));
        hs_Num = new QSlider(groupBox);
        hs_Num->setObjectName(QStringLiteral("hs_Num"));
        hs_Num->setGeometry(QRect(10, 410, 191, 22));
        hs_Num->setOrientation(Qt::Horizontal);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 380, 31, 16));
        btn_Load = new QPushButton(groupBox);
        btn_Load->setObjectName(QStringLiteral("btn_Load"));
        btn_Load->setGeometry(QRect(10, 290, 75, 23));
        btn_Load->setFocusPolicy(Qt::NoFocus);
        btn_Bin = new QPushButton(groupBox);
        btn_Bin->setObjectName(QStringLiteral("btn_Bin"));
        btn_Bin->setGeometry(QRect(10, 450, 75, 23));
        btn_Bin->setFocusPolicy(Qt::NoFocus);
        Edit_Threshold = new QTextEdit(groupBox);
        Edit_Threshold->setObjectName(QStringLiteral("Edit_Threshold"));
        Edit_Threshold->setGeometry(QRect(50, 370, 31, 31));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 290, 31, 16));
        hs_Zoom = new QSlider(groupBox);
        hs_Zoom->setObjectName(QStringLiteral("hs_Zoom"));
        hs_Zoom->setGeometry(QRect(220, 290, 160, 22));
        hs_Zoom->setOrientation(Qt::Horizontal);
        btn_GS = new QPushButton(groupBox);
        btn_GS->setObjectName(QStringLiteral("btn_GS"));
        btn_GS->setGeometry(QRect(10, 340, 75, 23));
        btn_GS->setFocusPolicy(Qt::NoFocus);
        btn_Up = new QPushButton(groupBox);
        btn_Up->setObjectName(QStringLiteral("btn_Up"));
        btn_Up->setGeometry(QRect(430, 310, 75, 23));
        btn_Down = new QPushButton(groupBox);
        btn_Down->setObjectName(QStringLiteral("btn_Down"));
        btn_Down->setGeometry(QRect(580, 310, 75, 23));
        lb_Count = new QLabel(groupBox);
        lb_Count->setObjectName(QStringLiteral("lb_Count"));
        lb_Count->setGeometry(QRect(520, 310, 47, 13));
        groupBox_2 = new QGroupBox(ToolsClass);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 580, 701, 171));
        lb_ImgReport = new QLabel(groupBox_2);
        lb_ImgReport->setObjectName(QStringLiteral("lb_ImgReport"));
        lb_ImgReport->setGeometry(QRect(10, 20, 381, 151));
        cmb_Seg = new QComboBox(groupBox_2);
        cmb_Seg->setObjectName(QStringLiteral("cmb_Seg"));
        cmb_Seg->setGeometry(QRect(470, 30, 131, 22));
        Edit_Zoom_Report = new QTextEdit(groupBox_2);
        Edit_Zoom_Report->setObjectName(QStringLiteral("Edit_Zoom_Report"));
        Edit_Zoom_Report->setGeometry(QRect(480, 60, 51, 31));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(450, 70, 31, 16));
        hs_Zoom_Report = new QSlider(groupBox_2);
        hs_Zoom_Report->setObjectName(QStringLiteral("hs_Zoom_Report"));
        hs_Zoom_Report->setGeometry(QRect(540, 70, 160, 22));
        hs_Zoom_Report->setOrientation(Qt::Horizontal);
        btn_Seg = new QPushButton(groupBox_2);
        btn_Seg->setObjectName(QStringLiteral("btn_Seg"));
        btn_Seg->setGeometry(QRect(470, 130, 75, 23));
        btn_Seg->setFocusPolicy(Qt::NoFocus);
        btn_Merge = new QPushButton(ToolsClass);
        btn_Merge->setObjectName(QStringLiteral("btn_Merge"));
        btn_Merge->setEnabled(false);
        btn_Merge->setGeometry(QRect(720, 20, 75, 23));
        btn_Merge->setFocusPolicy(Qt::NoFocus);
        btn_Split = new QPushButton(ToolsClass);
        btn_Split->setObjectName(QStringLiteral("btn_Split"));
        btn_Split->setEnabled(false);
        btn_Split->setGeometry(QRect(810, 20, 75, 23));
        btn_Split->setFocusPolicy(Qt::NoFocus);
        btn_Insert = new QPushButton(ToolsClass);
        btn_Insert->setObjectName(QStringLiteral("btn_Insert"));
        btn_Insert->setGeometry(QRect(900, 20, 75, 23));
        btn_Insert->setFocusPolicy(Qt::NoFocus);
        btn_Delete = new QPushButton(ToolsClass);
        btn_Delete->setObjectName(QStringLiteral("btn_Delete"));
        btn_Delete->setEnabled(false);
        btn_Delete->setGeometry(QRect(990, 20, 75, 23));
        btn_Delete->setFocusPolicy(Qt::NoFocus);
        LV_List = new QTableView(ToolsClass);
        LV_List->setObjectName(QStringLiteral("LV_List"));
        LV_List->setGeometry(QRect(710, 120, 321, 371));
        SB_X = new QSpinBox(ToolsClass);
        SB_X->setObjectName(QStringLiteral("SB_X"));
        SB_X->setGeometry(QRect(800, 80, 42, 22));
        SB_Y = new QSpinBox(ToolsClass);
        SB_Y->setObjectName(QStringLiteral("SB_Y"));
        SB_Y->setGeometry(QRect(870, 80, 42, 22));
        SB_Width = new QSpinBox(ToolsClass);
        SB_Width->setObjectName(QStringLiteral("SB_Width"));
        SB_Width->setGeometry(QRect(930, 80, 42, 22));
        SB_Height = new QSpinBox(ToolsClass);
        SB_Height->setObjectName(QStringLiteral("SB_Height"));
        SB_Height->setGeometry(QRect(1000, 80, 42, 22));
        label_4 = new QLabel(ToolsClass);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(810, 60, 21, 16));
        label_5 = new QLabel(ToolsClass);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(880, 60, 21, 16));
        label_6 = new QLabel(ToolsClass);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(930, 60, 31, 16));
        label_7 = new QLabel(ToolsClass);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(1000, 60, 41, 16));
        LB_Char = new QLabel(ToolsClass);
        LB_Char->setObjectName(QStringLiteral("LB_Char"));
        LB_Char->setGeometry(QRect(730, 60, 31, 16));
        btn_Save = new QPushButton(ToolsClass);
        btn_Save->setObjectName(QStringLiteral("btn_Save"));
        btn_Save->setGeometry(QRect(710, 500, 75, 23));
        btn_Save->setFocusPolicy(Qt::NoFocus);
        btn_MergeBox = new QPushButton(ToolsClass);
        btn_MergeBox->setObjectName(QStringLiteral("btn_MergeBox"));
        btn_MergeBox->setGeometry(QRect(924, 500, 111, 23));
        btn_MergeBox->setFocusPolicy(Qt::NoFocus);
        Edit_Log = new QTextEdit(ToolsClass);
        Edit_Log->setObjectName(QStringLiteral("Edit_Log"));
        Edit_Log->setGeometry(QRect(710, 530, 321, 221));
        Edit_Char = new QLineEdit(ToolsClass);
        Edit_Char->setObjectName(QStringLiteral("Edit_Char"));
        Edit_Char->setGeometry(QRect(710, 80, 71, 20));

        retranslateUi(ToolsClass);

        QMetaObject::connectSlotsByName(ToolsClass);
    } // setupUi

    void retranslateUi(QDialog *ToolsClass)
    {
        ToolsClass->setWindowTitle(QApplication::translate("ToolsClass", "Tools", 0));
        groupBox->setTitle(QApplication::translate("ToolsClass", "GroupBox", 0));
        lb_IMG->setText(QApplication::translate("ToolsClass", "TextLabel", 0));
        label->setText(QApplication::translate("ToolsClass", "value:", 0));
        btn_Load->setText(QApplication::translate("ToolsClass", "Load Img", 0));
        btn_Bin->setText(QApplication::translate("ToolsClass", "Binarization", 0));
        label_2->setText(QApplication::translate("ToolsClass", "Zoom:", 0));
        btn_GS->setText(QApplication::translate("ToolsClass", "GrayScale", 0));
        btn_Up->setText(QApplication::translate("ToolsClass", "<<", 0));
        btn_Down->setText(QApplication::translate("ToolsClass", ">>", 0));
        lb_Count->setText(QApplication::translate("ToolsClass", "Count", 0));
        groupBox_2->setTitle(QApplication::translate("ToolsClass", "GroupBox", 0));
        lb_ImgReport->setText(QApplication::translate("ToolsClass", "TextLabel", 0));
        label_3->setText(QApplication::translate("ToolsClass", "Zoom:", 0));
        btn_Seg->setText(QApplication::translate("ToolsClass", "Separation", 0));
        btn_Merge->setText(QApplication::translate("ToolsClass", "Merge", 0));
        btn_Split->setText(QApplication::translate("ToolsClass", "Split", 0));
        btn_Insert->setText(QApplication::translate("ToolsClass", "Insert", 0));
        btn_Delete->setText(QApplication::translate("ToolsClass", "Delete", 0));
        label_4->setText(QApplication::translate("ToolsClass", "X", 0));
        label_5->setText(QApplication::translate("ToolsClass", "Y", 0));
        label_6->setText(QApplication::translate("ToolsClass", "Width", 0));
        label_7->setText(QApplication::translate("ToolsClass", "height", 0));
        LB_Char->setText(QApplication::translate("ToolsClass", "Char", 0));
        btn_Save->setText(QApplication::translate("ToolsClass", "Save Box", 0));
        btn_MergeBox->setText(QApplication::translate("ToolsClass", "Merge TIFF And Box", 0));
    } // retranslateUi

};

namespace Ui {
    class ToolsClass: public Ui_ToolsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLS_H
