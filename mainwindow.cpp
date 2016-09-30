#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table();
}
void MainWindow::table()
{
    f1=new joueur ;
    f2=new terrain ;
    f3=new Fenetre ;
    f4=new reservation ;
    f5=new administration ;
    //QWidget *a=f3->page();
    ui->onglets->addTab(f1, "Joueur");
    ui->onglets->addTab(f2, "Terrain");
    ui->onglets->addTab(f3, "tour");
    ui->onglets->addTab(f4, "Reservation");
    ui->onglets->addTab(f5, "Administration");


}
MainWindow::~MainWindow()
{
    delete ui;
}
