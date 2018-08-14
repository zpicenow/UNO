#include "index.h"
#include "ui_index.h"
#include "helptext.h"
#include "maininterface.h"
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QDialog>
#include <QMovie>

Index::Index(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Index)
{
    originWindow();         //初始化窗体
    originStartButton();    //初始化开始游戏按钮
    originHelpButton();   //初始化帮助按钮
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/img/myico.ico"));
}

Index::~Index()
{
    delete ui;
}

void Index::originWindow(){
    setFixedSize(800,600);
}

//绘图事件(设置背景)
void Index::paintEvent(QPaintEvent *event)
{
    static QPixmap backpic(":/img/img/register.jpg");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),backpic);
}

//初始化单机按钮
void Index::originStartButton()
{
    start=new QPushButton(this);
    start->setGeometry(200,180,400,70);
    QFont font;
    font.setPointSize(25);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    start->setFont(font);
    start->setStyleSheet("color:#2b2b2b");
    start->setCursor(Qt::PointingHandCursor);
    start->setText("开始游戏");
    start->installEventFilter(this);//设置监听
    canStart=true;                  //刚开始可以点击
}

//初始化联机按钮
void Index::originHelpButton()
{


    help=new QPushButton(this);
    help->setGeometry(200,350,400,70);
    QFont font;
    font.setPointSize(25);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    help->setFont(font);
    help->setStyleSheet("color:#2b2b2b");
    help->setCursor(Qt::PointingHandCursor);
    help->setText("帮助");
    help->installEventFilter(this);//设置监听
    canHelp=true;                  //刚开始可以点击
}

//事件过滤器
/*
 * 注: 设置按钮可用不可用 是为了 防止连续快速多次点击 造成的多余的事件
 * if 按下 进入单机模式 且 该按钮可用
 * {
 *    设置该按钮不可用
 *    关闭该界面
 *    创建并打开单机界面
 * }
 * if 按下 进入联机模式 且 该按钮可用
 * {
 *    设置该按钮不可用
 *    关闭该界面
 *    创建并打开联机界面
 * }
*/
bool Index::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==start && event->type()==QEvent::MouseButtonPress && canStart)
    {
        canStart=false;
        close();
        mainInterface * newPage=new mainInterface;
        newPage->setWindowTitle("人机对战");
        newPage->show();
        return true;
    }
    if(obj==help && event->type()==QEvent::MouseButtonPress && canHelp)
    {

        this->hide();


            QDialog *dlg = new QDialog();

            QLabel *testLable = new QLabel(dlg);
            dlg->setWindowTitle(tr("帮 助"));
            dlg->setFixedSize(316,186);
            testLable->move(10,10);
            testLable->resize(296,166);
            QMovie *movie = new QMovie(":/img/img/uno_help.gif");
            testLable->setMovie(movie);
            movie->start();


            dlg->setWindowIcon(QIcon(":/img/img/myico.ico"));
            dlg->setStyleSheet("background-color: #dfdfdf");

            dlg->exec();

            this->show();



        return true;
    }
    return QWidget::eventFilter(obj,event);
}
