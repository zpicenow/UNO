#include "gameover.h"
#include "ui_gameover.h"

gameOver::gameOver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameOver)
{
    ui->setupUi(this);
}

gameOver::~gameOver()
{
    delete ui;
}
