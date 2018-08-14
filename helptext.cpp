#include "helptext.h"
#include "ui_helptext.h"

helpText::helpText(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::helpText)
{
    ui->setupUi(this);
}

helpText::~helpText()
{
    delete ui;
}
