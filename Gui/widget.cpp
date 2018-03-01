#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include "math.h"
#include "qdebug.h"
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include "main.cpp"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    _scene = new QGraphicsScene(0, 0, 800, 600, this);
    ui->graphicsView->setScene(_scene);

    _animationTimer = new QTimer(this);
    connect(_animationTimer, SIGNAL( timeout() ), _scene, SLOT( advance() ) );

    _animationTimer->start(1000/60);//60 fps
}

Widget::~Widget()
{
    delete _scene;
    delete _animationTimer;
    delete ui;
}

void MoveBubble::animate()
{
    float stepX = 0;
    float stepY = 0;
    foreach (QGraphicsItem* itemi, scene()->items() )
    {
        foreach (QGraphicsItem* itemj, scene()->items() )
        {
            if( itemi->pos()!=itemj->pos() )
            {
                calculateStep( itemi->pos().x(), itemi->pos().y(), itemj->pos().x(), itemj->pos().y(), &stepX, &stepY );
                itemj->moveBy( stepX, stepY );
                itemi->moveBy( -stepX, -stepY );
            }
        }
    }
}

void Widget::mousePressEvent(QMouseEvent *em)//Создание шарика по ЛКМ
{
    if((em->buttons() & Qt::LeftButton) )
    {
        qDebug()<<"QMouseEvent"<<em->pos();
        _scene->addItem( new MoveBubble(em->pos()));
    }
}

MoveBubble::MoveBubble(QPointF point) : QGraphicsEllipseItem(0)//Создание шарика
{
    _stepX = 0;
    _stepY = 0;
    QColor color = QColor( rand()%255, rand()%255, rand()%255 );//задание случайного цвета шарику
    setBrush( color );
    setRect( 0, 0, 50, 50 );//задание размера шарика
    setPos(point-QPointF(125,100));
}

void MoveBubble::advance(int phase)
{

    if(phase)
    {
        if(scene()->items().count()>1)
        {
            animate();
        }
    }
}

void MoveBubble::mousePressEvent(QGraphicsSceneMouseEvent *event)//Удаление шарика по ПКМ
{
    if((event->buttons() & Qt::RightButton) )
    {
        delete this;
    }
}

void MoveBubble::mouseMoveEvent(QGraphicsSceneMouseEvent *event)//Перемещение шарика по СКМ
{
    if((event->buttons() & Qt::MiddleButton) )
    {
        setPos( mapToParent( event->pos() - QPointF(25,25) ) );
    }
}

void Widget::on_pushButton_clicked()//Создание N-шариков
{
    if(ui->lineEdit->text().contains(QRegExp("\\D")) || ui->lineEdit->text().isEmpty() )
    {
        ui->lineEdit->setStyleSheet("background-color: rgb(149, 0, 0);");
    }
    else
    {
        ui->lineEdit->setStyleSheet("");
        for(int i = 0; i<ui->lineEdit->text().toInt(); i++)
        {
            _scene->addItem( new MoveBubble(QPointF(rand()%800, rand()%600 ) ) );
        }
    }
}
