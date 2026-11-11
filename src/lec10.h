#ifndef LEC10_H
#define LEC10_H

#include <QFrame>

namespace Ui {
    class lec10;
}

class lec10 : public QFrame
{
    Q_OBJECT

public:
    explicit lec10(QWidget *parent = nullptr);
    ~lec10();

private slots:
    void on_Lec10_currentChanged(int index);

private:
    Ui::lec10 *ui;
};

#endif // LEC10_H
