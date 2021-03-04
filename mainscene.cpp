#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QSound>//多媒体模块下的音效头文件
#pragma execution_character_set("utf-8")
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){

        this->close();
    });

    //准备开始按钮音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);
    startSound->setLoops(3);//设置循环次数 -1代表循环无限次
    startSound->play();

    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5- startBtn->width() * 0.5,this->height() * 0.7);
    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回键的信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        chooseScene->hide();
        this->setGeometry(chooseScene->geometry());
        this->show();
    });

    //监听点击事件，执行特效
    connect(startBtn,&MyPushButton::clicked,[=](){
        startSound->play(); //开始音效

        qDebug() << QString::fromUtf8("点击了开始");
        //做弹起特效
         startBtn->zoom1();
         startBtn->zoom2();

         //延时0.5秒进入到选择关卡场景中
         QTimer::singleShot(500,this,[=](){
             //隐藏自身
             this->hide();
             chooseScene->setGeometry(this->geometry());
             //显示选择关卡场景
             chooseScene->show();

         });

    });

}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景图上图标
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

}

MainScene::~MainScene()
{
    delete ui;
}

