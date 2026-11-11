#ifndef LEC02_H
#define LEC02_H


#include <QFrame>





namespace Ui {
    class lec02;
}

class lec02 : public QFrame
{
    Q_OBJECT

public:
    explicit lec02(QWidget *parent = nullptr);
    ~lec02();


private slots:
    void on_Lec02_currentChanged(int index);

private:
    Ui::lec02 *ui;


};

#endif // LEC02_H
