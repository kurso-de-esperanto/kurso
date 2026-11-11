#ifndef LEC11_H
#define LEC11_H

#include <QFrame>

namespace Ui {
    class lec11;
}

class lec11 : public QFrame
{
    Q_OBJECT

public:
    explicit lec11(QWidget *parent = nullptr);
    ~lec11();

private slots:
    void on_Lec11_currentChanged(int index);

private:
    Ui::lec11 *ui;
};

#endif // LEC11_H
