#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QWidget>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:
    void zmienione(bool );//jedna komorka się zmienia(wypełnia kolorem) to wysyła sygnał do zamknięcia rozmiaru
    void koniecgry(bool );// gra jest zakończona albo nie ma na niej zaznaczonej komorki - można zmienić rozmiar mapy

public slots:
    void startGame(const int &number = -1);
    void stopGame();
    void clear();

    int liczbakomorek(); //liczba komorek w wierszu
    void zmienliczbekomorek(const int &s); //zmien liczbe komorek

    int interval(); // czas miedzy generacjami

private slots:
    void rysujsiatke(QPainter &p);
    void rysujmape(QPainter &p);

    void nowageneracja();

private:
    QTimer* timer;
    int generacja;
    bool* mapa; // mapa
    bool* nastepny;
    int rozmiarmapy;
    bool czyzyje(int k, int j); // zwraca wartość true jeżeli pozcyja mapy spełnia warunki życia
    void resetmapa();// reset rozmiaru mapy
};

#endif // GAMEWIDGET_H
