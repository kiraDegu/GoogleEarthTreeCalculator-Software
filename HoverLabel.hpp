#ifndef HOVERLABEL_H
#define HOVERLABEL_H

#include <QLabel>
#include <QMessageBox>

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
