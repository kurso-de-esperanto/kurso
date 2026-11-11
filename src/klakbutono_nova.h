#ifndef KLAKBUTONO_NOVA_H
#define KLAKBUTONO_NOVA_H

#include <QLabel>

class klakbutono_nova : public QLabel
{
    Q_OBJECT
public:
    explicit klakbutono_nova(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~klakbutono_nova();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

public slots:

private slots:
    void klakita();

};

#endif // KLAKBUTONO_NOVA_H
