#ifndef _ACADEMY_MAINWINDOW_HPP_
#define _ACADEMY_MAINWINDOW_HPP_

#include <QMainWindow>
#include "HoverLabel.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calculateButton_clicked();
    void on_onWebButton_clicked();
    void on_checkBox_3_toggled(bool checked);

private:
    Ui::MainWindow *_ui;
    HoverLabel *_labelOrigin;
    HoverLabel *_labelHeading;
    HoverLabel *_labelDistance;
    HoverLabel *_labelMsl;
    HoverLabel *_labelModel;
    void _fromUserInputToOutput();
    void _displayResults();
    void _displayResultsN();
};
#endif // MAINWINDOW_H
