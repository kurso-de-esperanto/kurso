#ifndef LEC09_H
#define LEC09_H

#include <QFrame>

namespace Ui {
    class lec09;
}

class lec09 : public QFrame
{
    Q_OBJECT

public:
    explicit lec09(QWidget *parent = nullptr);
    ~lec09();

private slots:
    void on_Lec09_currentChanged(int index);

private:
    Ui::lec09 *ui;
};

#endif // LEC09_H
