#include "listview.h"
#include <QPainter>
#include <QDebug>

ListView::ListView(QWidget *parent) : QWidget(parent)
{
    rowHeight = 44;
    padding = 10;
    offsetY = 0;
    scrollBarWidth = 6;
    scrollBarPadding = 8;
    isDragScrollBar = false;

    setMouseTracking(true);
}

ListView::~ListView()
{
}

void ListView::addItem(ListItem *item)
{
    listItems << item;

    update();
}

void ListView::clearAllItems()
{
    listItems.clear();

    update();
}

void ListView::clearLastItem()
{
    listItems.removeLast();

    update();
}

void ListView::setScrollToBottom()
{
    offsetY = getItemsTotalHeight() - rect().height();

    update();
}

void ListView::insert(const QString &str)
{
    if (!listItems.isEmpty()) {
        listItems.last()->insert(str);
        update();
    }
}

void ListView::backspace()
{
    listItems.last()->backspace();

    update();
}

void ListView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw background and content.
    int drawHeight = 0;
    int count = 0;

    for (ListItem *item : listItems) {
        if (count >= offsetY / rowHeight) {
            const int lastIndex = listItems.indexOf(listItems.last());
            const bool isLast = lastIndex == count;

            item->drawBackground(QRect(0, count * rowHeight - offsetY, rect().width(), rowHeight), &painter);
            item->drawContent(QRect(padding,
                                    count * rowHeight - offsetY,
                                    rect().width() - padding * 2 - scrollBarPadding,
                                    rowHeight), &painter, isLast);

            drawHeight += rowHeight;

            if (drawHeight > rect().height())
                break;
        }

        ++count;
    }

    // Draw scrollbar.
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#000000"));

    if (isDragScrollBar) {
        painter.setOpacity(0.7);
    }else {
        painter.setOpacity(0.5);
    }

    if (listItems.count() > 4)
        painter.drawRoundedRect(QRect(width() - scrollBarPadding, getScrollBarY(), scrollBarWidth, getScrollBarHeight()), 5, 5);
}

void ListView::mouseMoveEvent(QMouseEvent *e)
{
    if (isDragScrollBar) {
        offsetY = adjustOffsetY(e->y() / (rect().height() * 1.0) * getItemsTotalHeight());

        update();
    }
}

void ListView::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        if (e->x() >= getScrollBarX()) {
            isDragScrollBar = true;

            offsetY = adjustOffsetY(e->y() / (rect().height() * 1.0) * getItemsTotalHeight());
        }

        update();
    }
}

void ListView::mouseReleaseEvent(QMouseEvent *e)
{
    if (isDragScrollBar)
        isDragScrollBar = false;

    update();
}

int ListView::getItemsTotalHeight() const
{
    return listItems.count() * rowHeight;
}

int ListView::getScrollBarHeight() const
{
    return rect().height() * 1.0 / getItemsTotalHeight() * rect().height();
}

int ListView::getScrollBarX() const
{
    return rect().width() - scrollBarWidth - scrollBarPadding;
}

int ListView::getScrollBarY() const
{
    return offsetY / (getItemsTotalHeight() * 1.0) * rect().height();
}

int ListView::adjustOffsetY(const int &offset) const
{
    return qMax(0, qMin(offset, getItemsTotalHeight() - rect().height()));
}