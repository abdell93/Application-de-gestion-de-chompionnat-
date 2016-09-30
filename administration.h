#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

#include <QWidget>

namespace Ui {
class administration;
}

class administration : public QWidget
{
    Q_OBJECT

public:
    explicit administration(QWidget *parent = 0);
    ~administration();
public slots :
    void deconnexion();
private:
    Ui::administration *ui;
};

#endif // ADMINISTRATION_H
