#ifndef PARTIE_H
#define PARTIE_H
#include <QPushButton>
#include <QWidget>

namespace Ui {
class partie;
}

class partie : public QWidget
{
    Q_OBJECT

public:
    explicit partie(QWidget *parent = 0);
    ~partie();

private:
    Ui::partie *ui;

};

#endif // PARTIE_H
