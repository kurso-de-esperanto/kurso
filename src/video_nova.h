#ifndef VIDEO_NOVA_H
#define VIDEO_NOVA_H

#include <QFrame>

namespace Ui {
class video_nova;
}

class video_nova : public QFrame
{
    Q_OBJECT

public:
    explicit video_nova(QWidget *parent = nullptr);
    ~video_nova();

private:
    Ui::video_nova *ui;
};

#endif // VIDEO_NOVA_H
