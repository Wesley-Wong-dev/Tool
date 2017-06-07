#pragma once

#include <QtWidgets/QDialog>
#include "ui_Tools.h"

class Tools : public QDialog
{
    Q_OBJECT

public:
    Tools(QWidget *parent = Q_NULLPTR);

private:
    Ui::ToolsClass ui;
};
