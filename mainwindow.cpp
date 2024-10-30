#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "Manager.hpp"
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

    static const Type::PathSpec pathSpec = {
        {1.0, 0.0},
        {1.0, 90.0},
        {std::sqrt(2.0), 45.0},
        {std::sqrt(5.0), 63.435},
        {std::sqrt(5.0), 26.565},
        {2.0 * std::sqrt(2.0), 45.0},
        {std::sqrt(12.5), 8.13},
        {std::sqrt(5.0), -26.565},
        {2.0, 0.0},
        {std::sqrt(2.0), -45.0},
        {1.0, 0.0},
        {0.0, 0.0}
    };
    PathCalculatorManager manager(pathSpec);

    const bool success = manager.genPath(
        ui->latitudeBox->text().toDouble(),
        ui->longitudeBox->text().toDouble(),
        ui->headingBox->text().toDouble(),
        ui->distanceBox->text().toDouble(),
        ui->mslBox->text().toDouble(),
        ui->modelInput->currentIndex()
    );

    if(success)
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



