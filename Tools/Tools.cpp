#include "Tools.h"

#include <QFileDialog>
#include <QImage>
#include <QDebug>
#include <QKeyEvent>
#include <QDir>

#include "BaseApi.h"

Tools::Tools(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    ui.hs_Num->setMinimum(0);
    ui.hs_Num->setMaximum(255);

    ui.Edit_Zoom->setText(QString::number(3));
    ui.hs_Zoom->setMinimum(0);
    ui.hs_Zoom->setMaximum(100);

    connect(ui.btn_MergeBox, SIGNAL(clicked()), this, SLOT(on_btn_MergeBox_clicked()), Qt::ConnectionType::UniqueConnection);
    connect(ui.btn_Load, SIGNAL(clicked()), this, SLOT(on_btn_Load_clicked()), Qt::ConnectionType::UniqueConnection);
    connect(ui.btn_GS, SIGNAL(clicked()), this, SLOT(on_btn_GS_clicked()), Qt::ConnectionType::UniqueConnection);
    connect(ui.btn_Bin, SIGNAL(clicked()), this, SLOT(on_btn_Bin_clicked()), Qt::ConnectionType::UniqueConnection);
	connect(ui.btn_Insert, SIGNAL(clicked()), this, SLOT(on_btn_Insert_clicked()), Qt::ConnectionType::UniqueConnection);
    connect(ui.btn_Save, SIGNAL(clicked()), this, SLOT(on_btn_Save_clicked()), Qt::ConnectionType::UniqueConnection);
    connect(ui.btn_Seg, SIGNAL(clicked()), this, SLOT(on_btn_Seg_clicked()), Qt::ConnectionType::UniqueConnection);
    connect(ui.btn_Up, SIGNAL(clicked()), this, SLOT(on_btn_Up_clicked()), Qt::ConnectionType::UniqueConnection);
    connect(ui.btn_Down, SIGNAL(clicked()), this, SLOT(on_btn_Down_clicked()), Qt::ConnectionType::UniqueConnection);

    connect(ui.hs_Num, SIGNAL(valueChanged(int)), this, SLOT(on_hs_Num_Changed(int)), Qt::ConnectionType::UniqueConnection);
    connect(ui.hs_Zoom, SIGNAL(valueChanged(int)), this, SLOT(on_hs_Zoom_Changed(int)), Qt::ConnectionType::UniqueConnection);
    
    connect(ui.hs_Zoom_Report, SIGNAL(valueChanged(int)), this, SLOT(on_hs_Zoom_Report_Changed(int)), Qt::ConnectionType::UniqueConnection);

    ui.cmb_Seg->insertItem(0, "Select....");
    ui.cmb_Seg->insertItem(1, "Projection Division");

    ui.SB_Height->setMinimum(0);
    ui.SB_Height->setMaximum(255);
    ui.SB_Width->setMinimum(0);
    ui.SB_Width->setMaximum(255);
    ui.SB_X->setMinimum(0);
    ui.SB_X->setMaximum(255);
    ui.SB_Y->setMinimum(0);
    ui.SB_Y->setMaximum(255);

    connect(ui.SB_Height, SIGNAL(valueChanged(int)), this, SLOT(on_SB_Height_ValueChanged(int)), Qt::ConnectionType::UniqueConnection);
    connect(ui.SB_Width, SIGNAL(valueChanged(int)), this, SLOT(on_SB_Width_ValueChanged(int)), Qt::ConnectionType::UniqueConnection);
    connect(ui.SB_X, SIGNAL(valueChanged(int)), this, SLOT(on_SB_X_ValueChanged(int)), Qt::ConnectionType::UniqueConnection);
    connect(ui.SB_Y, SIGNAL(valueChanged(int)), this, SLOT(on_SB_Y_ValueChanged(int)), Qt::ConnectionType::UniqueConnection);
    connect(ui.Edit_Char, SIGNAL(textChanged(const QString&)), this, SLOT(on_Edit_Char_TextChanged(const QString&)), Qt::ConnectionType::UniqueConnection);
    ui.Edit_Char->installEventFilter(this);

    connect(ui.cmb_Seg, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cmb_Seg_currentIndexChanged(int)), Qt::ConnectionType::UniqueConnection);
	//ui.lb_IMG->setScaledContents(true);
	ui.lb_ImgReport->setScaledContents(true);

	QStringList list;
	list << "Char" << "X" << "Y" << "Width"<<"Height";

	QStandardItemModel *model = new QStandardItemModel;
	model->setHorizontalHeaderLabels(list);  

	ui.LV_List->setModel(model);

    connect(ui.LV_List, SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_LV_List_Clicked(const QModelIndex&)));
	ui.LV_List->resizeColumnsToContents();
	ui.LV_List->resizeRowsToContents();
    
    ui.LV_List->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.LV_List->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_nIndex = 0;
}

void Tools::on_btn_Load_clicked()
{
    QFileDialog* lpDlg = new QFileDialog;
    lpDlg->setAcceptMode(QFileDialog::AcceptOpen);
    lpDlg->setFileMode(QFileDialog::ExistingFile);
    lpDlg->setNameFilter("Image Files(*.png *.jpg *.tif *.tiff);;Any Files(*.*)");
    lpDlg->setViewMode(QFileDialog::List);
    lpDlg->setWindowTitle("File Dialog");
    lpDlg->setDirectory("C:\\Users\\Administrator\\Documents\\Visual Studio 2015\\Projects\\TestOpenCV_Console\\TestOpenCV_Console\\img\\16-9");
    if (lpDlg->exec() == QDialog::Accepted)
    {
        m_strImgPath = lpDlg->selectedFiles()[0];
    }
    else
    {
        lpDlg->close();
    }

    if (m_strImgPath.length() >= 0)
    {
        ImgOpt theObj;
        int nCount = theObj.LoadTiff(m_strImgPath);
        if ( nCount <= 1  )
        {
            theObj.LoadImg(m_strImgPath);
            m_theImg = theObj.GetQImage();

            ShowImg(m_theImg);
            QFileInfo theInfo = QFileInfo(m_strImgPath);
            QString strFileName = theInfo.fileName();

            this->setWindowTitle( strFileName);
        }
        else if ( nCount > 1 )
        {
            //VTMats thePages = theObj.GetTiffPages();
            
            ui.lb_Count->setText(QString("%1 / %2").arg(1).arg(nCount));

            m_nIndex = 1;

            m_theImg = theObj.GetTiffPageByIndex(m_nIndex);

            ShowImg(m_theImg);

            on_hs_Zoom_Changed(ui.Edit_Zoom->toPlainText().toInt());

			ui.LV_List->model()->removeRows(0, ui.LV_List->model()->rowCount());

            BaseApi theApi;
            QStringList theList = theApi.GetBoxByIndex(m_strImgPath, 0);

			VTDataBox  theBoxs = theObj.GetImgRectsByFile(theList, m_theImg.height());

			for (int i = 0; i < theBoxs.size(); i++)
			{
				DataBox theBox = theBoxs.at(i);
				 
				AddRow(theBox.ch, theBox.theRect);
			}

			QModelIndex theIndex = ui.LV_List->model()->index(0, 0);

			ui.LV_List->setCurrentIndex(theIndex);

			on_LV_List_Clicked(theIndex);

        }
    }
    
}

void Tools::on_btn_GS_clicked()
{
    ImgOpt theObj;
    theObj.FromQImg(m_theImg);
    theObj.GrayScale();
    m_theImg = theObj.GetQImage();
    ShowImg( m_theImg );
	on_hs_Zoom_Changed(ui.Edit_Zoom->toPlainText().toInt());
}

void Tools::on_btn_Bin_clicked()
{
    ImgOpt theObj;
    theObj.FromQImg(m_theImg);
    m_theImg = theObj.Binarization();
    ShowImg(m_theImg);
	on_hs_Zoom_Changed(ui.Edit_Zoom->toPlainText().toInt());
}

void Tools::on_hs_Num_Changed(int nValue)
{
    ui.Edit_Threshold->setText(QString("%1").arg(nValue));
    ImgOpt theObj;
    theObj.FromQImg(m_theImg);

    ShowImg(theObj.Binarization(nValue));
	on_hs_Zoom_Changed(ui.Edit_Zoom->toPlainText().toInt());
}

void Tools::on_hs_Zoom_Changed(int nValue)
{
    ui.Edit_Zoom->setText(QString("%1").arg(nValue));
	
	const QPixmap* lpMap = ui.lb_IMG->pixmap();
	QImage theImg = lpMap->toImage();
    ImgOpt theObj;
    theObj.FromQImg(theImg);
    ShowImg(theObj.ImgResize(nValue));
}

void Tools::on_hs_Zoom_Report_Changed(int nValue)
{
    ui.Edit_Zoom_Report->setText(QString("%1").arg(nValue));

	const QPixmap* lpMap = ui.lb_ImgReport->pixmap();
	QImage theImg = lpMap->toImage();

    ImgOpt theObj;
    theObj.FromQImg(theImg);

    ShowImgReport(theObj.ImgResize(nValue));
}

void Tools::on_btn_Seg_clicked()
{
    ImgOpt theObj;
    theObj.FromQImg(m_theImg);
	m_theRGBImg = theObj.ProjectionSeg();

	VTRects  theRects = theObj.GetImgRects();
	for (int i = 0; i < theRects.size(); i++ )
	{
		AddRow("", theRects.at(i) );
	}
    QModelIndex theIndex = ui.LV_List->model()->index(0, 0);
    ui.LV_List->setCurrentIndex(theIndex);
    on_LV_List_Clicked( theIndex);
	//m_theImg = theTmp;
    ShowImg(m_theRGBImg);
	on_hs_Zoom_Changed(ui.Edit_Zoom->toPlainText().toInt());
    
}

void Tools::on_btn_Insert_clicked()
{
	QStandardItemModel* theModel = (QStandardItemModel*)(ui.LV_List->model());
	//AddRow("test","0","0","0","0");
	QModelIndex theIndex  = ui.LV_List->currentIndex();
	 
	QStandardItem *  lpItem = theModel->item(theIndex.row(),theIndex.column());
	
	 Rect theRect = lpItem->data().value<Rect>();
	 theRect.x += theRect.width;
	 QVariant theValue;
	 theValue.setValue(theRect);

	int nIndex = theIndex.row() + 1;
	theModel->insertRow(nIndex);
	QStandardItem* lpItemChar = new QStandardItem;
	lpItemChar->setText("");
	lpItemChar->setData(theValue);
	theModel->setItem(nIndex,0, lpItemChar);

	QStandardItem* lpItemX = new QStandardItem;
	lpItemX->setText(QString::number(theRect.x));
	lpItemX->setData(theValue);
	theModel->setItem(nIndex, 1, lpItemX);

	QStandardItem* lpItemY = new QStandardItem;
	lpItemY->setText(QString::number(theRect.y));
	lpItemY->setData(theValue);
	theModel->setItem(nIndex, 2, lpItemY);

	QStandardItem* lpItemWidth = new QStandardItem;
	lpItemWidth->setText(QString::number(theRect.width));
	lpItemWidth->setData(theValue);
	theModel->setItem(nIndex, 3, lpItemWidth);

	QStandardItem* lpItemHeight = new QStandardItem;
	lpItemHeight->setText(QString::number(theRect.height));
	lpItemHeight->setData(theValue);
	theModel->setItem(nIndex, 4, lpItemHeight);
}

void Tools::on_btn_Save_clicked()
{
    QFileDialog* lpDlg = new QFileDialog;
    lpDlg->setAcceptMode(QFileDialog::AcceptSave);
    lpDlg->setFileMode(QFileDialog::ExistingFile);
    lpDlg->setNameFilter("Image Files(*.tif *.tiff)");
    lpDlg->setViewMode(QFileDialog::List);
    lpDlg->setWindowTitle("File Save Dialog");
    lpDlg->setDirectory("C:\\Users\\Administrator\\Documents\\Visual Studio 2015\\Projects\\TestOpenCV_Console\\TestOpenCV_Console\\img\\16-9");
    if (lpDlg->exec() == QDialog::Accepted)
    {
        m_strImgPath = lpDlg->selectedFiles()[0];
    }
    else
    {
        lpDlg->close();
    }

    if ( m_strImgPath.length() )
    {
        QFileInfo theInfo = QFileInfo(m_strImgPath);
        QString strFileName = theInfo.baseName();
        QString strPath = theInfo.path();
        ImgOpt theObj;
        theObj.FromQImg(m_theImg);
        if ( theObj.SaveTIF(m_strImgPath) )
        {
            VTDataBox theBoxData = GetRowData();
            theObj.SaveBox(QString("%1\\%2.box").arg(strPath).arg(strFileName),theBoxData);
        }
    }
    
}

void Tools::on_btn_MergeBox_clicked()
{
    QString strDir;
    QFileDialog* lpDlg = new QFileDialog;
    lpDlg->setAcceptMode(QFileDialog::AcceptOpen);
    lpDlg->setFileMode(QFileDialog::DirectoryOnly);
    lpDlg->setViewMode(QFileDialog::List);
    lpDlg->setWindowTitle("Select Directory Dialog");
    lpDlg->setDirectory("C:\\Users\\Administrator\\Documents\\Visual Studio 2015\\Projects\\TestOpenCV_Console\\TestOpenCV_Console\\img\\16-9");
    if (lpDlg->exec() == QDialog::Accepted)
    {
        strDir = lpDlg->selectedFiles()[0];
    }
    else
    {
        lpDlg->close();
    }

    if (strDir.length())
    {
        QDir theDir(strDir);
        if ( theDir.exists(strDir) )
        {

            BaseApi theApi;
            
            QStringList theTiffFiles = theApi.ScanTiffFiles(strDir);
            theApi.CreateMultTiff("test.tif", theTiffFiles);
            QStringList theBoxFiles = theApi.ScanBoxFiles(strDir);
            theApi.CreateMultBox("test.box", theBoxFiles);
            QStringList theListLog = theApi.GetCharCount("test.box");
            for (int i =0;i < theListLog.size(); i++)
            {
                ui.Edit_Log->append(theListLog.at(i));
            }
            
        }
        
    }
}

void Tools::on_btn_Up_clicked()
{
    ImgOpt theObj;
    int nCount = theObj.LoadTiff(m_strImgPath);
    if ( nCount )
    {
        int nIndex = m_nIndex;
        if ( nIndex-1 > 0 && nIndex-1  <= nCount )
        {
            m_theImg = theObj.GetTiffPageByIndex(nIndex-1);

            ui.lb_Count->setText(QString("%1 / %2").arg(nIndex-1).arg(nCount));

            ShowImg(m_theImg);

            on_hs_Zoom_Changed(ui.Edit_Zoom->toPlainText().toInt());

			ui.LV_List->model()->removeRows(0, ui.LV_List->model()->rowCount());

			BaseApi theApi;
			QStringList theList = theApi.GetBoxByIndex(m_strImgPath, nIndex-2 );

			VTDataBox  theBoxs = theObj.GetImgRectsByFile(theList, m_theImg.height());

			for (int i = 0; i < theBoxs.size(); i++)
			{
				DataBox theBox = theBoxs.at(i);

				AddRow(theBox.ch, theBox.theRect);
			}

			QModelIndex theIndex = ui.LV_List->model()->index(0, 0);

			ui.LV_List->setCurrentIndex(theIndex);

			on_LV_List_Clicked(theIndex);

			ShowRectImg();
            
			--m_nIndex;
        }
    }
    
}

void Tools::on_btn_Down_clicked()
{
    ImgOpt theObj;
    int nCount = theObj.LoadTiff(m_strImgPath);
    if ( nCount )
    {
        int nIndex = m_nIndex;
        if ( nIndex+1 <= nCount )
        {
            m_theImg = theObj.GetTiffPageByIndex(nIndex+1);

            ui.lb_Count->setText(QString("%1 / %2").arg(nIndex+1).arg(nCount));

            ShowImg(m_theImg);

            on_hs_Zoom_Changed(ui.Edit_Zoom->toPlainText().toInt());



			ui.LV_List->model()->removeRows(0, ui.LV_List->model()->rowCount());

			BaseApi theApi;
			QStringList theList = theApi.GetBoxByIndex(m_strImgPath, nIndex );

			VTDataBox  theBoxs = theObj.GetImgRectsByFile(theList, m_theImg.height());

			for (int i = 0; i < theBoxs.size(); i++)
			{
				DataBox theBox = theBoxs.at(i);

				AddRow(theBox.ch, theBox.theRect);
			}

			QModelIndex theIndex = ui.LV_List->model()->index(0, 0);

			ui.LV_List->setCurrentIndex(theIndex);

			on_LV_List_Clicked(theIndex);

			ShowRectImg();

			++m_nIndex;

        }
    }
    
}

void Tools::on_cmb_Seg_currentIndexChanged(int)
{
    switch (ui.cmb_Seg->currentIndex())
    {
    case 1:
    {
        ImgOpt theObj;
        theObj.FromQImg(m_theImg);
        m_theRepImg = theObj.Projection();
        ShowImgReport(m_theRepImg);
    }
        break;
    default:
        break;
    }
}

void Tools::on_LV_List_itemChanged( QStandardItem* lpItem )
{
	qDebug() << lpItem->text();
	if ( lpItem )
	{
        ShowRectImg();
	}
}

void Tools::on_LV_List_Clicked(const QModelIndex& theIndex)
{
    QStandardItemModel* theModel = (QStandardItemModel*)(ui.LV_List->model());
    QStandardItem *  lpItemChar = theModel->item(theIndex.row(), 0);
    if ( lpItemChar)
    {
        ui.Edit_Char->setText( lpItemChar->text() );
    }
    QStandardItem *  lpItemX = theModel->item(theIndex.row(), 1);
    if (lpItemX)
    {
        ui.SB_X->setValue(lpItemX->text().toInt());
    }
    QStandardItem *  lpItemY = theModel->item(theIndex.row(), 2);
    if ( lpItemY )
    {
        ui.SB_Y->setValue(lpItemY->text().toInt());
    }
    QStandardItem *  lpItemWidth = theModel->item(theIndex.row(), 3);
    if (lpItemWidth)
    {
        ui.SB_Width->setValue(lpItemWidth->text().toInt());
    }
    QStandardItem *  lpItemHeight = theModel->item(theIndex.row(), 4);
    if (lpItemHeight)
    {
        ui.SB_Height->setValue(lpItemHeight->text().toInt());
    }
    ui.Edit_Char->setFocusPolicy(Qt::StrongFocus);
}

void Tools::on_SB_Height_ValueChanged( int nValue )
{
    QStandardItemModel* theModel = (QStandardItemModel*)(ui.LV_List->model());
    QModelIndex theIndex = ui.LV_List->currentIndex();
    QStandardItem * lpItem = theModel->item(theIndex.row(), 4);
    lpItem->setText(QString::number(nValue));

    ShowRectImg();

}

void Tools::ShowRectImg()
{
    VTDataBox theDataBox = GetRowData();
    VTRects theRects;
    for (int i = 0; i < theDataBox.size(); i++)
    {
        theRects.push_back( theDataBox.at(i).theRect);
    }
    ImgOpt theObj;
    theObj.FromQImg(m_theImg);

    ShowImg(theObj.DrawRects(theRects));

    on_hs_Zoom_Changed(ui.Edit_Zoom->toPlainText().toInt());
}

bool Tools::eventFilter(QObject * lpTarget, QEvent * lpEvent)
{
    if (lpTarget == ui.Edit_Char)
    {
        if ( lpEvent->type() == QEvent::KeyPress  )
        {
            QKeyEvent* eventKey = static_cast<QKeyEvent*>(lpEvent);
            if ( eventKey->key() == Qt::Key_Return)
            {
                QModelIndex theIndex = ui.LV_List->currentIndex();
                theIndex = ui.LV_List->model()->index(theIndex.row() + 1, 0);
                ui.LV_List->setCurrentIndex(theIndex);
                on_LV_List_Clicked(theIndex);
            }
        }
        
    }
    return false;
}

void Tools::on_SB_Width_ValueChanged( int nValue )
{
    QStandardItemModel* theModel = (QStandardItemModel*)(ui.LV_List->model());
    QModelIndex theIndex = ui.LV_List->currentIndex();
    QStandardItem * lpItem = theModel->item(theIndex.row(), 3);
    if ( lpItem )
    {
        lpItem->setText(QString::number(nValue));
    }
    
    ShowRectImg();
}

void Tools::on_SB_X_ValueChanged( int nValue )
{
    QStandardItemModel* theModel = (QStandardItemModel*)(ui.LV_List->model());
    QModelIndex theIndex = ui.LV_List->currentIndex();
    QStandardItem * lpItem = theModel->item(theIndex.row(), 1);
    if ( lpItem )
    {
        lpItem->setText(QString::number(nValue));
    }
    
    ShowRectImg();
}

void Tools::on_SB_Y_ValueChanged(int nValue)
{
    QStandardItemModel* theModel = (QStandardItemModel*)(ui.LV_List->model());
    QModelIndex theIndex = ui.LV_List->currentIndex();
    QStandardItem * lpItem = theModel->item(theIndex.row(), 2);
    if ( lpItem )
    {
        lpItem->setText(QString::number(nValue));
    }
    
    ShowRectImg();
}

void Tools::on_Edit_Char_TextChanged(const QString& strText)
{
    QStandardItemModel* theModel = (QStandardItemModel*)(ui.LV_List->model());
    QModelIndex theIndex = ui.LV_List->currentIndex();
    QStandardItem * lpItem = theModel->item(theIndex.row(), 0);
    if ( lpItem )
    {
        lpItem->setText(strText);
    }
    
}

void Tools::ShowImg( QImage theImg )
{
    QPixmap theMap = QPixmap::fromImage(theImg);
	ui.lb_IMG->resize(theMap.size());
    ui.lb_IMG->setPixmap(theMap);
    ui.lb_IMG->show();
}

void Tools::ShowImgReport(QImage theImg)
{
    QPixmap theMap = QPixmap::fromImage(theImg);
	//ui.lb_ImgReport->resize(theMap.size());
    ui.lb_ImgReport->setPixmap(theMap);
    ui.lb_ImgReport->show();
}

void Tools::AddTableViewRow(QList<QStandardItem*> theRow)
{
	QStandardItemModel* theModel = (QStandardItemModel*)(ui.LV_List->model());

	theModel->appendRow(theRow);
}
void Tools::ClearTableView()
{
	QStandardItemModel* theModel = (QStandardItemModel*)(ui.LV_List->model());
	theModel->removeRows(0, theModel->rowCount());
	theModel->removeColumns(0, theModel->columnCount());
}

void Tools::AddRow( QString strChar, Rect theRect)
{
	QVariant theValue;
	theValue.setValue(theRect);

	QList<QStandardItem *> theItem;
	QStandardItem* lpItemChar = new QStandardItem;
	lpItemChar->setText(strChar);
	lpItemChar->setData(theValue);
	theItem.push_back(lpItemChar);

	QStandardItem* lpItemX = new QStandardItem;
	lpItemX->setText(QString::number(theRect.x));
	lpItemX->setData(theValue);
	theItem.push_back(lpItemX);
	QStandardItem* lpItemY = new QStandardItem;
	lpItemY->setText(QString::number(theRect.y));
	lpItemY->setData(theValue);
	theItem.push_back(lpItemY);
	QStandardItem* lpItemWidth = new QStandardItem;
	lpItemWidth->setText(QString::number(theRect.width));
	lpItemWidth->setData(theValue);
	theItem.push_back(lpItemWidth);
	QStandardItem* lpItemHeight = new QStandardItem;
	lpItemHeight->setText(QString::number(theRect.height));
	lpItemHeight->setData(theValue);
	theItem.push_back(lpItemHeight);

	AddTableViewRow(theItem);
}

VTDataBox Tools::GetRowData()
{
	QStandardItemModel* theModel = (QStandardItemModel*)(ui.LV_List->model());

    VTDataBox theDataBoxs;
	for (int i = 0; i < theModel->rowCount();i++)
	{
        DataBox theBox;
        QStandardItem* lpItemChar = theModel->item(i, 0);
        if (lpItemChar)
        {
            theBox.ch = lpItemChar->text();
        }

		Rect theRect;
		QStandardItem* lpItemX = theModel->item(i, 1);
		if ( lpItemX )
		{
			theRect.x = lpItemX->text().toInt();
		}
		
		QStandardItem* lpItemY = theModel->item(i, 2);
		if ( lpItemY )
		{
			theRect.y = lpItemY->text().toInt();
		}
		
		QStandardItem* lpItemWidth = theModel->item(i, 3);
		if ( lpItemWidth )
		{
			theRect.width = lpItemWidth->text().toInt();
		}
		
		QStandardItem* lpItemHeight = theModel->item(i, 4);
		if ( lpItemHeight )
		{
			theRect.height = lpItemHeight->text().toInt();
		}
		if ( lpItemHeight && lpItemWidth&&lpItemY&&lpItemX)
		{
            theBox.theRect = theRect;
			theDataBoxs.push_back(theBox);
		}
	}
	return theDataBoxs;
}

