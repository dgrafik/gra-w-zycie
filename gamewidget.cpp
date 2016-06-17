#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include<iostream>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    generacja(0),
    rozmiarmapy(20)
{

    mapa = new bool[(rozmiarmapy   + 1) * (rozmiarmapy   + 1)];
    nastepny = new bool[(rozmiarmapy   + 1 ) * (rozmiarmapy   + 1)];
    connect(timer, SIGNAL(timeout()), this, SLOT(nowageneracja()));
    memset(mapa, false, sizeof(bool)*(rozmiarmapy   + 1) * (rozmiarmapy   + 1)); //Wypełnia kolejne bajty w pamięci ustaloną wartością.
    memset(nastepny, false, sizeof(bool)*(rozmiarmapy   + 1) * (rozmiarmapy   + 1));
}

GameWidget::~GameWidget()
{
    delete [] mapa;
    delete [] nastepny;
}

void GameWidget::startGame(const int &number)
{
    generacja = number;
    timer->start();
}

void GameWidget::stopGame()
{
    timer->stop();
}

void GameWidget::clear()
{
    for(int k = 1; k <= rozmiarmapy; k++)
        for(int j = 1; j <= rozmiarmapy; j++)
            mapa[k*rozmiarmapy +j] = false;


    koniecgry(true);
    update();
}

int GameWidget::liczbakomorek()
{
    return rozmiarmapy;
}

void GameWidget::zmienliczbekomorek(const int &s)
{
    rozmiarmapy = s;
    resetmapa();
    update();
}

void GameWidget::resetmapa()
{
    delete [] mapa;
    delete [] nastepny;
    mapa = new bool[(rozmiarmapy   + 1) * (rozmiarmapy   + 1)];
    nastepny = new bool[(rozmiarmapy   + 1) * (rozmiarmapy   + 1)];
    memset(mapa, false, sizeof(bool)*(rozmiarmapy   + 1) * (rozmiarmapy   + 1));
    memset(nastepny, false, sizeof(bool)*(rozmiarmapy   + 1) * (rozmiarmapy   + 1));
}

int GameWidget::interval()
{
    return timer->interval();
}

bool GameWidget::czyzyje(int k, int j)
{
    int zyje = 0;
    zyje += mapa[(k+1)*rozmiarmapy +  j];
    zyje += mapa[(k-1)*rozmiarmapy + j];
    zyje += mapa[k*rozmiarmapy + (j+1)];
    zyje += mapa[k*rozmiarmapy + (j-1)];
    zyje += mapa[(k+1)*rozmiarmapy + ( j-1)];
    zyje += mapa[(k-1)*rozmiarmapy + (j+1)];
    zyje += mapa[(k-1)*rozmiarmapy + (j-1)];
    zyje += mapa[(k+1)*rozmiarmapy +  (j+1)];
    if (((mapa[k*rozmiarmapy + j] == true) && (zyje == 2)) || (zyje == 3))
           return true;
    if((mapa[k*rozmiarmapy + j] == false) && (zyje == 3))
        return true;
    return false;
}

void GameWidget::nowageneracja()
{
    if(generacja < 0)
        generacja++;
    for(int k=1; k <= rozmiarmapy; k++)
        for(int j=1; j <= rozmiarmapy; j++)
            nastepny[k*rozmiarmapy + j] = czyzyje(k, j);

    for(int k=1; k <= rozmiarmapy; k++)
        for(int j=1; j <= rozmiarmapy; j++)
            mapa[k*rozmiarmapy + j] = nastepny[k*rozmiarmapy + j];
    update();

}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    rysujsiatke(p);
    rysujmape(p);
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    emit zmienione(true); //emitowanie sygnału
    double szerokosckomorki = (double)width()/rozmiarmapy;
    double wysokosckomorki = (double)height()/rozmiarmapy;
    int k = floor(e->y()/wysokosckomorki)+1;
    int j = floor(e->x()/szerokosckomorki)+1;
    mapa[k*rozmiarmapy + j] =! mapa[k*rozmiarmapy + j];
    update();
}

void GameWidget::mouseMoveEvent(QMouseEvent *e)
{
    double szerokosckomorki = (double)width()/rozmiarmapy;
    double wysokosckomorki = (double)height()/rozmiarmapy;
    int k = floor(e->y()/wysokosckomorki)+1;
    int j = floor(e->x()/szerokosckomorki)+1;
    if(!mapa[k*rozmiarmapy + j]) //jeżeli komórka == false(pusta) to ją wypełnij
    {
        mapa [k*rozmiarmapy + j] =! mapa[k*rozmiarmapy + j];
        update();
    }
}

void GameWidget::rysujsiatke(QPainter &p)
{
    QRect borders(0, 0, width()-1, height()-1);
    QColor gridColor = "#000"; // kolor siatki

    p.setPen(gridColor);
    double szerokosckomorki = (double)width()/rozmiarmapy; // szerokkość widgetu / liczba komorek w rzędzie
    for(double k = szerokosckomorki; k <= width(); k += szerokosckomorki)
        p.drawLine(k, 0, k, height());
    double wysokosckomorki = (double)height()/rozmiarmapy;
    for(double k = wysokosckomorki; k <= height(); k += wysokosckomorki)
        p.drawLine(0, k, width(), k);
    p.drawRect(borders);
}

void GameWidget::rysujmape(QPainter &p)
{

    double szerokosckomorki = (double)width()/rozmiarmapy;
    double wysokosckomorki = (double)height()/rozmiarmapy;
    for(int k=1; k <= rozmiarmapy; k++)
    {
        for(int j=1; j <= rozmiarmapy; j++)
        {
            if(mapa[k*rozmiarmapy + j] == true)
            {
                qreal left = (qreal)(szerokosckomorki*j-szerokosckomorki); //z lewej
                qreal top  = (qreal)(wysokosckomorki*k-wysokosckomorki); // z góry
                QRectF r(left, top, (qreal)szerokosckomorki, (qreal)wysokosckomorki);
                p.fillRect(r, QBrush("#000"));
            }
        }
    }
}


