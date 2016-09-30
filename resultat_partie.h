#ifndef RESULTAT_PARTIE_H
#define RESULTAT_PARTIE_H

#include <QWidget>

namespace Ui {
class Resultat_partie;
}

class Resultat_partie : public QWidget
{
    Q_OBJECT

public:
    explicit Resultat_partie(QWidget *parent = 0);
    ~Resultat_partie();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Resultat_partie *ui;
};

#endif // RESULTAT_PARTIE_H
