#ifndef SENDUJO_H
#define SENDUJO_H

#include <QFrame>

namespace Ui {
class sendujo;
}

class sendujo : public QFrame
{
    Q_OBJECT

public:
    explicit sendujo(QWidget *parent = nullptr);
    ~sendujo();

private:
    Ui::sendujo *ui;
};

#endif // SENDUJO_H
