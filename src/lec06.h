#ifndef LEC06_H
#define LEC06_H

#include <QFrame>

namespace Ui {
    class lec06;
}

class lec06 : public QFrame
{
    Q_OBJECT

public:
    explicit lec06(QWidget *parent = nullptr);
    ~lec06();

private slots:
    void on_Lec06_currentChanged(int index);

private:
    Ui::lec06 *ui;
};

#endif // LEC06_H
