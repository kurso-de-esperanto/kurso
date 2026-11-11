#ifndef KLAKBUTONO_H
#define KLAKBUTONO_H

#include <QLabel>

class klakbutono : public QLabel
{
    Q_OBJECT
public:
    explicit klakbutono(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~klakbutono();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

public slots:

private slots:
    void klakita();

};

#endif // KLAKBUTONO_H
