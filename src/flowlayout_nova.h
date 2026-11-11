#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H

#include <QLayout>
#include <QRect>

class FlowLayout : public QLayout
{
public:
    explicit FlowLayout(QWidget *parent, int margin = 0, int spacing = -1);
    FlowLayout(int spacing = -1);
    FlowLayout(int hspacing = -1, int vspacing = -1);
    ~FlowLayout() override;

    int horizontalSpacing() const;
    void setHorizontalSpacing(const int spacing);
    int verticalSpacing() const;
    void setVerticalSpacing(const int spacing);

    void addItem(QLayoutItem *item) override;
    Qt::Orientations expandingDirections() const override;
    bool hasHeightForWidth() const override;
    int heightForWidth(int) const override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    QSize sizeHint() const override;
    QLayoutItem *takeAt(int index) override;
    void addSpacing(const int size);

private:
    int doLayout(const QRect &rect, bool testOnly) const;

    QList<QLayoutItem *> itemList;
    int mHorizontalSpacing;
    int mVerticalSpacing;
};

#endif
