#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "terrain.h"
#include "administration.h"
#include "connection.h"
#include "joueur.h"
#include "partie.h"
#include "exemple.h"
#include "reservation.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void table();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    joueur *f1;
    terrain *f2;
    Fenetre *f3;
    reservation *f4;
    administration *f5;

    };

#endif // MAINWINDOW_H
