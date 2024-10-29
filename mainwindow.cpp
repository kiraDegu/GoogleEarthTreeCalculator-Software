#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TypeTraits.hpp"
#include <QMessageBox>
#include <QDesktopServices>
#include <QEnterEvent>
#include <QToolTip>

HoverLabel::HoverLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent) {
}

void HoverLabel::enterEvent(QEnterEvent *event) {
    // Controlla se l'evento è di tipo QEnterEvent
    if (event->type() == QEvent::Enter) {
        QToolTip::showText(QCursor::pos(), "Questo è un tooltip informativo!");
    }
    QLabel::enterEvent(event); // Chiama il metodo base
}

void HoverLabel::leaveEvent(QEvent *event) {

    QToolTip::hideText();
    QLabel::leaveEvent(event);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Crea e aggiungi la HoverLabel
    label = new HoverLabel("Origin:", ui->labelLongitude);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_calculateButton_clicked(){


}

void MainWindow::UserInput(){
    Type::Scalar latitude = ui->latitudeBox->text().toDouble();
    Type::Scalar longitude = ui->longitudeBox->text().toDouble();
    Type::Scalar heading = ui->headingBox->text().toDouble();
    Type::Scalar distance = ui->distanceBox->text().toDouble();
    Type::Scalar msl = ui->mslBox->text().toDouble();
    Type::Model model = ui->modelInput->currentIndex();

    displayResults();
}

void MainWindow::displayResults() {
    QMessageBox::information(this, "Success", "Coordinate calcolate e salvate nel file KML.");
}

void MainWindow::on_onWebButton_clicked()
{
    QString htmlFilePath = "https://earth.google.com/web/@45.52015247,9.26697256,130.21959004a,1475.22100893d,30y,-0h,0t,0r/data=CgRCAggBOgMKATBKCAiDhoiXBBAA";
    QDesktopServices::openUrl(QUrl(htmlFilePath));
}



