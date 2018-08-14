#include "maininterface.h"
#include "ui_maininterface.h"
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

#define card_width 80
#define card_height 105

mainInterface::mainInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainInterface)
{
    ui->setupUi(this);
    setWindowTitle("uno");
    setFixedSize(1000,650);
    m_gameprocess = new gameProcess(this);
    m_Selected=NULL;
    cardToGet=1;
    init();
    initCardsMap();

    /*****连接GameProcess发出的信号**********/
    connect(m_gameprocess,SIGNAL(tellPlayerStatus(Player*,Player::playerStatus)),\
            this,SLOT(setPlayerStatus(Player* ,Player::playerStatus)));
    connect(m_gameprocess,SIGNAL(tellPlayerPlayHand(Player*,card)),\
            this,SLOT(playingHand(Player*,card)));
    connect(m_gameprocess,SIGNAL(tellGameProcess(gameProcess::gameStatus)),\
            this,SLOT(startProcess(gameProcess::gameStatus)));
    ui->setupUi(this);
    connect(m_gameprocess,SIGNAL(changeClockwise()),this,SLOT(change()));
    connect(m_gameprocess,SIGNAL(twoCards()),this,SLOT(addTwoCards()));
    connect(m_gameprocess,SIGNAL(fourCards()),this,SLOT(addFourCards()));

}

mainInterface::~mainInterface()
{
    delete ui;
}

void mainInterface::init(){
    QFont ft;
    ft.setPointSize(30);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);

    time=20;
    moveDistance=0;
    m_pickingCardTimer=new QTimer(this);
    m_pickingCardTimer->setInterval(8);
    connect(m_pickingCardTimer,SIGNAL(timeout()),this,SLOT(pickingCards()));
    timer=new QTimer(this);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeDisplay()));
    /*****设置移动的牌和放在中间不动的牌***********/
    m_AllCardsPic.load(":/img/img/uno_card.png");
    m_cardBackPic.load(":/img/img/uno_back.png");
    m_basecardPos = QPoint( (width()-card_width)/2, 250 );
    m_movingcard=new cardPicture(this);
    m_basecard=new cardPicture(this);
    m_movingcard->setPic(m_cardBackPic);
    m_basecard->setPic(m_cardBackPic);
    m_movingcard->move(m_basecardPos);
    m_basecard->move(m_basecardPos);

    m_rePickingCards = new QLabel(this);
    m_rePickingCards->setText("重新发牌");
    m_rePickingCards->setFont(ft);
    m_rePickingCards->setPalette(pa);
    m_rePickingCards->move(width()/2-50,250);
    m_rePickingCards->hide();

    m_timeLabel=new QLabel(this);
    m_timeLabel->setFont(ft);
    m_timeLabel->setPalette(pa);
    m_timeLabel->move(490,400);
    m_timeLabel->hide();

    /**********按钮初始化*****************/
    /*开始按钮*/
    m_start= new QPushButton(this);
    m_start->setText("开始游戏");
    m_start->move((width()-m_start->width())/2+10,height()-card_height-20);
    connect(m_start,SIGNAL(clicked()),this,SLOT(on_start_clicked()));
    /*出牌,提示和要不起按钮*/
    m_playhand=new QPushButton(this);
    m_pass = new QPushButton(this);
    m_tip = new QPushButton(this);
    m_red = new QPushButton(this);
    m_yellow = new QPushButton(this);
    m_green = new QPushButton(this);
    m_blue = new QPushButton(this);
    m_playhand->hide();
    m_pass->hide();
    m_tip->hide();
    m_red->hide();
    m_yellow->hide();
    m_green->hide();
    m_blue->hide();
    m_playhand->setText("出牌");
    m_pass->setText("抽牌");
    m_tip->setText("提示");
    m_red->setText("红色");
    m_yellow->setText("黄色");
    m_green->setText("绿色");
    m_blue->setText("蓝色");
    m_pass->move(width()/2-120,height()-card_height-60);
    m_playhand->move(width()/2-20,height()-card_height-60);
    m_tip->move(width()/2+80,height()-card_height-60);
    m_red->move(width()/2-220,height()-card_height-60);
    m_yellow->move(width()/2-120,height()-card_height-60);
    m_green->move(width()/2-20,height()-card_height-60);
    m_blue->move(width()/2+20,height()-card_height-60);

    connect(m_playhand,SIGNAL(clicked()),this,SLOT(on_playhand_clicked()));
    connect(m_pass,SIGNAL(clicked()),this,SLOT(on_pass_clicked()));
    connect(m_tip,SIGNAL(clicked()),this,SLOT(on_tip_clicked()));
    connect(m_red,SIGNAL(clicked()),this,SLOT(changToRed()));
    connect(m_yellow,SIGNAL(clicked()),this,SLOT(changeToYellow()));
    connect(m_green,SIGNAL(clicked()),this,SLOT(changeToGreen()));
    connect(m_blue,SIGNAL(clicked()),this,SLOT(changeToBlue()));

    /*继续按钮*/
    m_continue= new QPushButton(this);
    m_continue->hide();
    m_continue->setText("继续游戏");
    m_continue->move((width()-m_continue->width())/2+10,height()-card_height-40);

    connect(m_continue,SIGNAL(clicked()),this,SLOT(on_continue_clicked()));

    m_gameprocess->getDownPlayer()->passLabel=new QLabel(this);
    m_gameprocess->getDownPlayer()->passLabel->setText("过牌");
    m_gameprocess->getDownPlayer()->passLabel->move(width()/2-50,(height()-card_height-100));
    m_gameprocess->getDownPlayer()->passLabel->setFont(ft);
    m_gameprocess->getDownPlayer()->passLabel->setPalette(pa);
    m_gameprocess->getDownPlayer()->passLabel->hide();

    m_gameprocess->getLeftPlayer()->passLabel=new QLabel(this);
    m_gameprocess->getLeftPlayer()->passLabel->setText("过牌");
    m_gameprocess->getLeftPlayer()->passLabel->move(150,m_basecardPos.y());
    m_gameprocess->getLeftPlayer()->passLabel->setFont(ft);
    m_gameprocess->getLeftPlayer()->passLabel->setPalette(pa);
    m_gameprocess->getLeftPlayer()->passLabel->hide();

    m_gameprocess->getRightPlayer()->passLabel=new QLabel(this);
    m_gameprocess->getRightPlayer()->passLabel->setText("过牌");
    m_gameprocess->getRightPlayer()->passLabel->move(width()-250,m_basecardPos.y());
    m_gameprocess->getRightPlayer()->passLabel->setFont(ft);
    m_gameprocess->getRightPlayer()->passLabel->setPalette(pa);
    m_gameprocess->getRightPlayer()->passLabel->hide();

    m_gameprocess->getUpPlayer()->passLabel=new QLabel(this);
    m_gameprocess->getUpPlayer()->passLabel->setText("过牌");
    m_gameprocess->getUpPlayer()->passLabel->move(width()-250,m_basecardPos.y());
    m_gameprocess->getUpPlayer()->passLabel->setFont(ft);
    m_gameprocess->getUpPlayer()->passLabel->setPalette(pa);
    m_gameprocess->getUpPlayer()->passLabel->hide();
}

void mainInterface::initCardsMap()
{
    for(int i =0;i<4;++i){
        card c;
        c.setPoint(card_zero);
        c.setColor((card_color)(i+1));
        cutCardPic( 0 , i * card_height, c);
    }
    for (int point = 2,j = 1; point<card_addfour; point++,j++)
    {
        for (int color=1, i =0 ; color<9; color++,i++)
        {
            card c;
            c.setPoint((card_point)point);
            c.setColor((card_color)color);
            cutCardPic( j *card_width , i * card_height, c);
        }
        if(j==12){
            for(int z=0;z<8;z++){
                card c;
                if(z<4) c.setPoint(card_change);
                else c.setPoint(card_addfour);
                c.setColor((card_color)(z+1));
                cutCardPic( 13* card_width, z* card_height, c);
            }
        }
    }
}

void mainInterface::cutCardPic(int x,int y,card c)
{
    QPixmap pic = m_AllCardsPic.copy(x,y,card_width,card_height);
    cardPicture* cardpic = new cardPicture(this);
    cardpic->hide();                //暂时隐藏
    cardpic->setPic(pic);
    cardpic->setCard(c);
    m_Cards.insert(c,cardpic);       //插入QMap中
    connect(cardpic,SIGNAL(tellSelected()),this,SLOT(cardSelected()));
}

void mainInterface::startProcess(gameProcess::gameStatus status)
{
    switch(status)
    {
    case (gameProcess::pickingCard):
        reStart();
        m_basecard->show();
        m_movingcard->show();
        m_pickingCardTimer->start();
        m_gameprocess->m_gamestatus=gameProcess::pickingCard;
        break;
    case (gameProcess::started):
        m_gameprocess->m_gamestatus = gameProcess::started;
        m_timeLabel->setText("20");
        m_timeLabel->show();
        timer->start();
        m_gameprocess->start();
        break;
    case (gameProcess::playingCard):
        m_gameprocess->m_gamestatus=gameProcess::playingCard;
        updateCards(m_gameprocess->getCurrentPlayer());
        break;
    }
}

void mainInterface::setPlayerStatus(Player *player, Player::playerStatus status)
{
   if(status==Player::waitingPlayingHand)
    {
        /*隐藏上次出的牌*/
        card cardToPlay=player->getCardToPlay();
        if(cardToPlay.getPoint()!=card_end&&cardToPlay.getPoint()!=card_point_begain) m_Cards.value(cardToPlay)->hide();

        player->passLabel->hide();

        player->getCardToPlay().setPoint(card_point_begain);

        if(player==m_gameprocess->getDownPlayer())
        {
            time=20;
            timer->start();
            m_timeLabel->setText("20");
            m_timeLabel->show();
            m_pass->show();
            m_playhand->show();
            m_tip->show();

        }
        else
        {
            timer->stop();
            m_timeLabel->hide();

            m_tip->hide();
            m_pass->hide();
            m_playhand->hide();
        }
    }
    else if(status==Player::winning)
    {
        m_playhand->hide();
        m_pass->hide();
        m_tip->hide();
        m_timeLabel->hide();
        timer->stop();

        //翻转显示场上剩余牌
        card c;
        foreach(c,m_gameprocess->getDownPlayer()->getCards())
            m_Cards.value(c)->setTurn(true);
        foreach(c,m_gameprocess->getLeftPlayer()->getCards())
            m_Cards.value(c)->setTurn(true);
        foreach(c,m_gameprocess->getRightPlayer()->getCards())
            m_Cards.value(c)->setTurn(true);
        foreach(c,m_gameprocess->getUpPlayer()->getCards())
            m_Cards.value(c)->setTurn(true);

        updateCards(m_gameprocess->getDownPlayer());
        updateCards(m_gameprocess->getLeftPlayer());
        updateCards(m_gameprocess->getRightPlayer());
        updateCards(m_gameprocess->getUpPlayer());

        m_continue->show();
        if(player==m_gameprocess->getDownPlayer())
        {
            QMessageBox::about(this,tr("结果"),tr("你赢了!"));
        }
        else
        {
            QMessageBox::about(this,tr("结果"),tr("你输了!"));
        }

        m_gameprocess->setCurrentPlayer(player);
    }
}

void mainInterface::on_start_clicked()
{
    m_start->hide();                            //隐藏开始按钮
    startProcess(gameProcess::pickingCard);     //执行发牌进程
}

void mainInterface::pickingCards()
{
    Player* curPlayer=m_gameprocess->getCurrentPlayer();
    if(moveDistance>270)
    {
        m_gameprocess->getCards(curPlayer,1);
        moveDistance=0;
        updateCards(curPlayer);

        if(m_gameprocess->getAllCards().size() == 80)            //发牌结束
        {

            m_pickingCardTimer->stop();

            m_movingcard->hide();
            int i;
            do{
                QTime t = QTime::currentTime();
                qsrand(t.msec()+t.second()*1000);
                i = qrand()% (m_gameprocess->getAllCards().size());
            }while(m_gameprocess->getAllCards()[i].getPoint()==card_addfour||m_gameprocess->getAllCards()[i].getPoint()==card_change);
            card first = m_gameprocess->getAllCards()[i];
            m_gameprocess->getAllCards().removeAt(i);
            cardPicture* c=m_Cards.value(first);
            c ->move(300,250);
            c->setTurn(true);
            c->show();
            m_gameprocess->setHitCard(first);
            m_gameprocess->setCurrentPlayer(m_gameprocess->getNextPlayer());

            startProcess(gameProcess::started);
            return;
        }

        m_gameprocess->setCurrentPlayer(m_gameprocess->getNextPlayer());


    }
    else
    {
        moveDistance+=14;
        pickingCardsAnimation(curPlayer);
    }
}
void mainInterface::pickingCardsAnimation(Player* player)
{
    if(player == m_gameprocess->getLeftPlayer())
        m_movingcard->move(m_basecardPos.x()-moveDistance*1.5,m_basecardPos.y());
    if(player == m_gameprocess->getRightPlayer())
        m_movingcard->move(moveDistance*1.5+m_basecardPos.x(),m_basecardPos.y());
    if(player == m_gameprocess->getDownPlayer())
        m_movingcard->move(m_basecardPos.x(),m_basecardPos.y()+moveDistance);
    if(player==m_gameprocess->getUpPlayer())
        m_movingcard->move(m_basecardPos.x(),m_basecardPos.y()-moveDistance);
}

void mainInterface::paintEvent(QPaintEvent *event)
{
    /*画背景图*/
    QPixmap bk;
    if(m_gameprocess->getClockwise()==true) bk = QPixmap(":/img/img/await5.png");
    else bk = QPixmap(":/img/img/clockwise.png");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),bk);
}


void mainInterface::cardSelected()
{
    if( (m_gameprocess->m_gamestatus) == gameProcess::pickingCard) return;

    cardPicture* cardpic=(cardPicture*) sender();//发送信号的图片

    if(cardpic->getSelected())
    {
        cardpic->setSelected(false);
        m_Selected=NULL;
    }
    else
    {
        if(m_Selected!=NULL && m_Selected->getTurn()==true) m_Selected->setSelected(false);
        cardpic->setSelected(true);
        m_Selected = cardpic;
    }
    updateCards(m_gameprocess->getDownPlayer()); //更新本方玩家牌
}

void mainInterface::updateCards(Player *player)
{
    QList<card> cards=player->getCards();
    qSort(cards.begin(),cards.end());
    int cardsInterval=30;

    //铺牌
    if(player == m_gameprocess->getDownPlayer())
    {
        for(int j=0;j<cards.size();j++)
        {
            int topBorder = (height()-card_height-5);                           //上边界
            int leftbase=m_basecardPos.x()-((cards.size()-1)*cardsInterval)/2;  //左边起点
            cardPicture* cardpic=m_Cards.value(cards[j]);
            cardpic->setTurn(true);
            if(cardpic->getSelected()) topBorder-=20;
            cardpic->move(leftbase+j*cardsInterval,topBorder);
            cardpic->repaint();
            cardpic->show();
        }
    }
    else if(player== m_gameprocess->getUpPlayer()){
        for(int j=0;j<cards.size();j++)
        {
            int topBorder = 5;                           //上边界
            int leftbase=m_basecardPos.x()-((cards.size()-1)*cardsInterval)/2;  //左边起点
            cardPicture* cardpic=m_Cards.value(cards[j]);
            cardpic->move(leftbase+j*cardsInterval,topBorder);
            cardpic->show();
        }
    }
    else if(player == m_gameprocess->getLeftPlayer()){
        int leftBorder=5,upbase;
         for(int j=0;j<cards.size();j++)
         {
                upbase= m_basecardPos.y()-((cards.size()-1)*cardsInterval)/2;
                cardPicture* cardpic = m_Cards.value(cards[j]);

                cardpic->move(leftBorder,upbase+j*cardsInterval);
                cardpic->show();
            }
     }
    else if(player == m_gameprocess->getRightPlayer())
    {
        int leftBorder=width()-card_width-5,upbase;
        for(int j=0;j<cards.size();j++)
        {
            upbase= m_basecardPos.y()-((cards.size()-1)*cardsInterval)/2;
            cardPicture* cardpic = m_Cards.value(cards[j]);
            cardpic->move(leftBorder,upbase+j*cardsInterval);
            cardpic->show();
        }
    }


    //牌打出去效果
    card cardToPlay = player->getCardToPlay();
    if(cardToPlay.getPoint()==card_end){
        return ;
    }
    if(cardToPlay.getPoint()!=card_point_begain)
    {
        if(player==m_gameprocess->getDownPlayer())
        {

            int topBorder = (height()-card_height-150);
            int leftbase=m_basecardPos.x();
            cardPicture* cardpic=m_Cards.value(cardToPlay);
            cardpic->setTurn(true);
            cardpic->move(leftbase,topBorder);
            cardpic->show();
        }
        else if(player==m_gameprocess->getLeftPlayer())
        {
            int topBorder = m_basecardPos.y();
            int leftbase=105;
            cardPicture* cardpic=m_Cards.value(cardToPlay);
            cardpic->setTurn(true);
            cardpic->move(leftbase,topBorder);
            cardpic->show();
        }
        else if(player==m_gameprocess->getRightPlayer())
        {
            int topBorder = m_basecardPos.y();
            int leftbase = width()-card_width*2-105;
            cardPicture* cardpic=m_Cards.value(cardToPlay);
            cardpic->setTurn(true);
            cardpic->move(leftbase,topBorder);
            cardpic->show();
        }
        else if(player==m_gameprocess->getUpPlayer()){
            int topBorder = 130;
            int leftbase=m_basecardPos.x();
            cardPicture* cardpic=m_Cards.value(cardToPlay);
            cardpic->setTurn(true);
            cardpic->move(leftbase,topBorder);
            cardpic->show();
        }
    }

}

void mainInterface::playerStartPlayingHand()
{
    /*从选中的牌图片中得到要打出去的牌组*/
    if(m_Selected==NULL) return;
    card out;
    out = m_Selected->getCard();

    /****************判断是否能打出*********************/
    hand hands(out);
    //打不过不能出
    hand handToHit(m_gameprocess->getHitCard());
    if(!hands.defeat(handToHit))
    {
        qDebug()<<"Cannot Defeat";
        return;
    }


    /****************************************/
    m_Selected=NULL;
    m_gameprocess->getDownPlayer()->playHand(out);

}

void mainInterface::playingHand(Player* player,card out)
{
    if(out.getPoint()!=card_end){
         player->getCardToPlay()=out;   //写入本次出的牌
        updateCards(player);
    }
    else {
        m_gameprocess->getCards(player,cardToGet);
        cardToGet=1;
        moveDistance=0;
        updateCards(player);
    }
}

void mainInterface::on_playhand_clicked()
{
    playerStartPlayingHand();
}

void mainInterface::on_pass_clicked()
{
    //选中的牌降下
    cardPicture* cardpic;
    cardpic = m_Selected;
    if(cardpic!=NULL) cardpic->setSelected(false);
    m_Selected=NULL;
    m_gameprocess->getCards(m_gameprocess->getDownPlayer(),cardToGet);
    cardToGet=1;
    moveDistance=0;
    updateCards(m_gameprocess->getDownPlayer());

    m_gameprocess->getDownPlayer()->playHand(card((card_point)0,(card_color)0));
}

void mainInterface::on_continue_clicked()
{
    startProcess(gameProcess::pickingCard);
}

void mainInterface::on_tip_clicked()
{
    m_Selected->setSelected(false);
    m_Selected=NULL;
    method st(m_gameprocess->getDownPlayer(),m_gameprocess->getDownPlayer()->getCards());
    card out = st.makeDecision();
    m_Selected=m_Cards.value(out);
    m_Selected->setSelected(true);
    updateCards(m_gameprocess->getDownPlayer());
}

void mainInterface::reStart()
{
    m_timeLabel->hide();
    timer->stop();
    time=20;
    m_continue->hide();             //隐藏继续按钮

    //清空玩家牌组
    m_gameprocess->getDownPlayer()->getCards().clear();
    m_gameprocess->getRightPlayer()->getCards().clear();
    m_gameprocess->getLeftPlayer()->getCards().clear();
    m_gameprocess->getUpPlayer()->getCards().clear();

    m_gameprocess->getDownPlayer()->getCardToPlay().setPoint(card_point_begain);
    m_gameprocess->getRightPlayer()->getCardToPlay().setPoint(card_point_begain);
    m_gameprocess->getLeftPlayer()->getCardToPlay().setPoint(card_point_begain);
    m_gameprocess->getUpPlayer()->getCardToPlay().setPoint(card_point_begain);
    m_gameprocess->restart();

}

void mainInterface::timeDisplay(){
    if(time<1)
    {
        timer->stop();
        //电脑托管
    }
    else
    {
        QString str;
        str.setNum(--time);
        m_timeLabel->setText(str);
    }
}

void mainInterface::change(){
    update();
}

void mainInterface::addTwoCards(){
    if(cardToGet==1){
        cardToGet+=1;
    }
    else{
        cardToGet+=2;
    }
}

void mainInterface::addFourCards(){
    if(cardToGet==1){
        cardToGet+=3;
    }
    else{
        cardToGet+=4;
    }
}

void mainInterface::changeToRed(){
    m_gameprocess->getHitCard().setColor(red);
}

void mainInterface::changeToYellow(){
    m_gameprocess->getHitCard().setColor(yellow);
}

void mainInterface::changeToBlue(){
    m_gameprocess->getHitCard().setColor(blue);
}

void mainInterface::changeToGreen(){
    m_gameprocess->getHitCard().setColor(green);
}

void mainInterface::setColor(){
    m_playhand->hide();
    m_pass->hide();
    m_tip->hide();
    m_red->show();
    m_yellow->show();
    m_green->show();
    m_blue->show();
}
