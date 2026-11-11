#ifndef KOREKTA_BUTONO_H
#define KOREKTA_BUTONO_H

#include <QPushButton>

class korekta_butono : public QPushButton
{
    Q_OBJECT
public:
    explicit korekta_butono(QWidget *parent = nullptr);


signals:


public slots:

private slots:
    void klakita();

};

#endif // KOREKTA_BUTONO_H
