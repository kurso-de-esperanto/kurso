#ifndef LEC01_H
#define LEC01_H

#include <QFrame>


namespace Ui {
    class lec01;
}

class lec01 : public QFrame
{
    Q_OBJECT

public:
    explicit lec01(QWidget *parent = nullptr);
    ~lec01();


private slots:
    void on_Lec01_currentChanged(int index);

private:
    Ui::lec01 *ui;


};

#endif // LEC01_H
