#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

#include <QTimer>

#include <QMutex>

#include <iostream>
#include <thread>

namespace Ui {
class Widget;
}

class MoveBubble : public QGraphicsEllipseItem
{
public:
    MoveBubble(QPointF point);

    void animate();

    // QGraphicsItem interface
public:
    virtual void advance(int phase);

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

    // QGraphicsItem interface
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    float _stepX, _stepY;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();



private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QGraphicsScene* _scene;
    QTimer* _animationTimer;
    QList<QPointF> _itemPos;
    //QMutex	m_mutex;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent* em);
};

#endif // WIDGET_H
