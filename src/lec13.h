#ifndef LEC13_H
#define LEC13_H

#include <QFrame>

namespace Ui {
    class lec13;
}

class lec13 : public QFrame
{
    Q_OBJECT

public:
    explicit lec13(QWidget *parent = nullptr);
    ~lec13();

private slots:
    void on_Lec13_currentChanged(int index);

private:
    Ui::lec13 *ui;
};

#endif // LEC13_H
