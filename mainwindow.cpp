#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TypeTraits.hpp"
#include <QMessageBox>
#include <QDesktopServices>
#include <QEnterEvent>
#include <QToolTip>

HoverLabel::HoverLabel(const QString &text, const QString &message, QWidget *parent)
    : QLabel(text, parent), message(message) {
}

void HoverLabel::enterEvent(QEnterEvent *event) {

    QPoint tooltipPos;
    tooltipPos.setY(35);
    tooltipPos.setX(30);

    if (event->type() == QEvent::Enter) {

        QToolTip::showText(QCursor::pos() - tooltipPos, message);
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
    label = new HoverLabel("Origin:", "Punto di partenza dell'albero", ui->widgetOrigin);
    label = new HoverLabel("Heading (0 to 360):", "Rotazione dell'albero" , ui->widgetHeading);
    label = new HoverLabel("Distance (NM):", "Distanza tra punti" , ui->widgetDistance);
    label = new HoverLabel("MSL (m):", "Altitudine" , ui->widgetMsl);
    label = new HoverLabel("Select Earth Model:", "Modello di calcolo" , ui->widgetModel);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_calculateButton_clicked(){

    UserInput();
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



