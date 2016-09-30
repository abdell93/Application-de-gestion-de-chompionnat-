#ifndef SECONNECTER_H
#define SECONNECTER_H
#include "mainwindow.h"
#include <QWidget>

namespace Ui {
class seConnecter;
}

class seConnecter : public QWidget
{
    Q_OBJECT

public:
    explicit seConnecter(QWidget *parent = 0);
    ~seConnecter();

public slots:
    void authentification();
private:
    Ui::seConnecter *ui;
    MainWindow *w;
};

#endif // SECONNECTER_H
