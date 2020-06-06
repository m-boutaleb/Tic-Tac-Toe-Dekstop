#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(geometry().width(), geometry().height());
    connect(ui->cella_00, SIGNAL(clicked(bool)), this, SLOT(onClicked_00()));
    connect(ui->cella_01, SIGNAL(clicked(bool)), this, SLOT(onClicked_01()));
    connect(ui->cella_02, SIGNAL(clicked(bool)), this, SLOT(onClicked_02()));
    connect(ui->cella_10, SIGNAL(clicked(bool)), this, SLOT(onClicked_10()));
    connect(ui->cella_11, SIGNAL(clicked(bool)), this, SLOT(onClicked_11()));
    connect(ui->cella_12, SIGNAL(clicked(bool)), this, SLOT(onClicked_12()));
    connect(ui->cella_20, SIGNAL(clicked(bool)), this, SLOT(onClicked_20()));
    connect(ui->cella_21, SIGNAL(clicked(bool)), this, SLOT(onClicked_21()));
    connect(ui->cella_22, SIGNAL(clicked(bool)), this, SLOT(onClicked_22()));

    m_celle[0][0]=ui->cella_00;
    m_celle[0][1]=ui->cella_01;
    m_celle[0][2]=ui->cella_02;
    m_celle[1][0]=ui->cella_10;
    m_celle[1][1]=ui->cella_11;
    m_celle[1][2]=ui->cella_12;
    m_celle[2][0]=ui->cella_20;
    m_celle[2][1]=ui->cella_21;
    m_celle[2][2]=ui->cella_22;

    initMatrix();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Ritorna vero se le condizioni di vittoria sono soddisfatte
bool MainWindow::vittoria()
{
    return (stato(0,0) == stato(0,1) && stato(0,1) == stato(0,2) &&
            stato(0,2) != ""
            || stato(1,0) == stato(1,1) && stato(1,1) == stato(1,2) &&
            stato(1,2) != ""
            || stato(2,0) == stato(2,1) && stato(2,1) == stato(2,2) &&
            stato(2,2) != ""
            || stato(0,0) == stato(1,0) && stato(1,0) == stato(2,0) &&
            stato(2,0) != ""
            || stato(0,1) == stato(1,1) && stato(1,1) == stato(2,1) &&
            stato(2,1) != ""
            || stato(0,2) == stato(1,2) && stato(1,2) == stato(2,2) &&
            stato(2,2) != ""
            || stato(0,0) == stato(1,1) && stato(1,1) == stato(2,2) &&
            stato(2,2) != ""
            || stato(2,0) == stato(1,1) && stato(1,1) == stato(0,2) &&
            stato(0,2) != "");
}

void MainWindow::checkAndSet(const int &i, const int &j)
{
    if(stato(i, j)=="")
        m_celle[i][j]->setText(QChar(DEFAULT_OPTIONS[(++MainWindow::turn)%2]));
    if(vittoria()){
        MsgDialog m{(QString(QChar(DEFAULT_OPTIONS[(turn)%2]))+" ha vinto\nVuoi rigiocare?")};
        m.setVisible(true);
        if(m.exec()==QDialog::Accepted)
            initMatrix();
    }else if(noWinners()){
        MsgDialog m{"Nessun vincitore...\nVuoi rigiocare?"};
        m.setVisible(true);
        if(m.exec()==QDialog::Accepted)
            initMatrix();
    }
}

void MainWindow::initMatrix(){
    for(int i=0; i<3; i++)
        for(int j=0; j<3;j++)
            m_celle[i][j]->setText("");
}

bool MainWindow::noWinners()
{
    for(int i=0; i<3;i++)
        for(int j=0; j<3;j++)
            if(m_celle[i][j]->text()=="")
                return false;
    return true;
}

void MainWindow::onClicked_00()
{
    checkAndSet(0, 0);
}

void MainWindow::onClicked_01()
{
    checkAndSet(0, 1);
}


void MainWindow::onClicked_02()
{
    checkAndSet(0, 2);
}

void MainWindow::onClicked_10()
{
    checkAndSet(1, 0);
}

void MainWindow::onClicked_11()
{
    checkAndSet(1, 1);
}

void MainWindow::onClicked_12()
{
    checkAndSet(1, 2);
}

void MainWindow::onClicked_20()
{
    checkAndSet(2, 0);
}

void MainWindow::onClicked_21()
{
    checkAndSet(2, 1);
}

void MainWindow::onClicked_22()
{
    checkAndSet(2, 2);
}

// Ritorna lo stato della cella: "" (vuota), "O", "X"
QString MainWindow::stato(int riga, int colonna){
    return m_celle[riga][colonna]->text();
}
