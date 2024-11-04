#include "HoverLabel.hpp"
#include <QMessageBox>
#include <QDesktopServices>
#include <QEnterEvent>
#include <QToolTip>

HoverLabel::HoverLabel(const QString &text, const QString &message, QWidget *parent)
    : QLabel(text, parent), _message(message) {
}

void HoverLabel::enterEvent(QEnterEvent *event) {

    //Correct QToolTip spawn point
    QPoint tooltipPos;
    tooltipPos.setY(35);
    tooltipPos.setX(30);

    //Spawn a QToolTip in the mouse location when the user enter in the label
    if (event->type() == QEvent::Enter) {
        QToolTip::showText(QCursor::pos() - tooltipPos, _message);
    }

    QLabel::enterEvent(event);
}

void HoverLabel::leaveEvent(QEvent *event) {

    //hide the QToolTip when the user leave the label
    QToolTip::hideText();
    QLabel::leaveEvent(event);
}
