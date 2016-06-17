#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    kolor(QColor("#000")),
    game(new GameWidget(this))
{
    ui->setupUi(this);

    QPixmap icon(20, 20);
    icon.fill(kolor);

    connect(ui->startButton_2, SIGNAL(clicked()), game,SLOT(startGame()));
    connect(ui->stopButton_2, SIGNAL(clicked()), game,SLOT(stopGame()));
    connect(ui->clearButton_2, SIGNAL(clicked()), game,SLOT(clear()));

    connect(ui->cellsControl_2, SIGNAL(valueChanged(int)), game, SLOT(zmienliczbekomorek(int)));
    connect(game,SIGNAL(zmienione(bool)),ui->cellsControl_2,SLOT(setDisabled(bool)));
    connect(game,SIGNAL(koniecgry(bool)),ui->cellsControl_2,SLOT(setEnabled(bool)));

    ui->horizontalLayout_2->setStretchFactor(ui->gameLayout_2, 8);
    ui->horizontalLayout_2->setStretchFactor(ui->setLayout_2, 2);
    ui->gameLayout_2->addWidget(game);
}

MainWindow::~MainWindow()
{
    delete ui;
}



