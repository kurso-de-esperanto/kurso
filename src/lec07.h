#ifndef LEC07_H
#define LEC07_H

#include <QFrame>

namespace Ui {
    class lec07;
}

class lec07 : public QFrame
{
    Q_OBJECT

public:
    explicit lec07(QWidget *parent = nullptr);
    ~lec07();

private slots:
    void on_Lec07_currentChanged(int index);

private:
    Ui::lec07 *ui;
};

#endif // LEC07_H
