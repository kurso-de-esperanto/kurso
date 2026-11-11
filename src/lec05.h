#ifndef LEC05_H
#define LEC05_H

#include <QFrame>

namespace Ui {
    class lec05;
}

class lec05 : public QFrame
{
    Q_OBJECT

public:
    explicit lec05(QWidget *parent = nullptr);
    ~lec05();

private slots:
    void on_Lec05_currentChanged(int index);

private:
    Ui::lec05 *ui;
};

#endif // LEC05_H
