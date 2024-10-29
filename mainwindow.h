#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class HoverLabel : public QLabel {
    Q_OBJECT

public:
    HoverLabel(const QString &text, const QString &message ,QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    QString message;

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calculateButton_clicked();
    void on_onWebButton_clicked();

private:
    Ui::MainWindow *ui;
    HoverLabel *label;
    void UserInput();
    void displayResults();
};
#endif // MAINWINDOW_H
