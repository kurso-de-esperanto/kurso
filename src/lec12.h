#ifndef LEC12_H
#define LEC12_H

#include <QFrame>

namespace Ui {
    class lec12;
}

class lec12 : public QFrame
{
    Q_OBJECT

public:
    explicit lec12(QWidget *parent = nullptr);
    ~lec12();


private slots:
    void on_Lec12_currentChanged(int index);

private:
    Ui::lec12 *ui;

};

#endif // LEC12_H
