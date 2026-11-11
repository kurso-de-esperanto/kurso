
// Self
#include "flowlayout_nova.h"

// Qt
#include <QHash>

FlowLayout::FlowLayout(QWidget *parent, int margin, int spacing)
    : QLayout(parent)
{
    setMargin(margin);
    setHorizontalSpacing(spacing);
    setVerticalSpacing(spacing);
}

FlowLayout::FlowLayout(int spacing)
{
    setHorizontalSpacing(spacing);
    setVerticalSpacing(spacing);
}

FlowLayout::FlowLayout(int hspacing, int vspacing)
{
    setHorizontalSpacing(hspacing);
    setVerticalSpacing(vspacing);
}


FlowLayout::~FlowLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

int FlowLayout::horizontalSpacing() const
{
    return mHorizontalSpacing;
}

void FlowLayout::setHorizontalSpacing(const int spacing)
{
    mHorizontalSpacing = spacing;
}

int FlowLayout::verticalSpacing() const
{
    return mVerticalSpacing;
}

void FlowLayout::setVerticalSpacing(const int spacing)
{
    mVerticalSpacing = spacing;
}

void FlowLayout::addItem(QLayoutItem *item)
{
    itemList.append(item);
}

int FlowLayout::count() const
{
    return itemList.size();
}

QLayoutItem *FlowLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem *FlowLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
        return itemList.takeAt(index);
    else
        return nullptr;
}

Qt::Orientations FlowLayout::expandingDirections() const
{
    return 0;
}

bool FlowLayout::hasHeightForWidth() const
{
    return true;
}

int FlowLayout::heightForWidth(int width) const
{
    int height = doLayout(QRect(0, 0, width, 0), true);
    return height;
}

void FlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize FlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize FlowLayout::minimumSize() const
{
    QSize size;
    QLayoutItem *item;
    foreach(item, itemList)
        size = size.expandedTo(item->minimumSize());

    size += QSize(2 * margin(), 2 * margin());
    return size;
}

void FlowLayout::addSpacing(const int size)
{
    addItem(new QSpacerItem(size, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));
}

int FlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    const int left = rect.x() + margin();
    int x = left;
    int y = rect.y() + margin();
    int lineHeight = 0;
    bool lastItemIsSpacer = false;
    QHash<int, int> widthForY;

    QLayoutItem *item;
    foreach(item, itemList) {
        const bool itemIsSpacer = item->spacerItem() != nullptr;
        // Don't add invisible items or succeeding spacer items
        if (item->sizeHint().width() == 0 || (itemIsSpacer && lastItemIsSpacer)) {
            continue;
        }

        int nextX = x + item->sizeHint().width() + horizontalSpacing();
        if (nextX - horizontalSpacing() > rect.right() - margin() && lineHeight > 0) {
            x = left;
            y = y + lineHeight + verticalSpacing();
            nextX = x + item->sizeHint().width() + horizontalSpacing();
            lineHeight = 0;
        }

        // Don't place spacer items at start of line
        if (itemIsSpacer && x == left) {
            continue;
        }

        if (!testOnly)
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

        x = nextX;
        // Don't add spacer items at end of line
        if (!itemIsSpacer) {
            widthForY[y] = x - margin();
        }
        lineHeight = qMax(lineHeight, item->sizeHint().height());
        lastItemIsSpacer = itemIsSpacer;
    }

    if (!testOnly) {
        const int contentWidth = rect.width() - 2 * margin();
        for (auto item : itemList) {
            QRect itemRect = item->geometry();
            // Center lines horizontally if flag AlignHCenter is set
            //if (alignment() & Qt::AlignHCenter) {
            if (true) {
                if (widthForY.contains(itemRect.y())) {
                    const int offset = (contentWidth - widthForY[itemRect.y()]) / 2;
                    itemRect.translate(offset, 0);
                }
            }
            // Center items vertically if flag AlignVCenter is set
            if (alignment() & Qt::AlignVCenter) {
                const int offset = (lineHeight - itemRect.height()) / 2;
                itemRect.translate(0, offset);
            }
            item->setGeometry(itemRect);
        }
    }

    return y + lineHeight - rect.y() + margin();
}
