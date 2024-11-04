#ifndef HOVERLABEL_H
#define HOVERLABEL_H

#include <QLabel>
#include <QMessageBox>

// Subclass of QLabel that override enter and leave events to spawn a QToolTip in the mouse location
class HoverLabel : public QLabel {
    Q_OBJECT

public:
    HoverLabel(const QString &text, const QString &message, QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    QString _message;

};

#endif // HOVERLABEL_H
