#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "Manager.hpp"
#include <QMessageBox>
#include <QDesktopServices>
#include <QEnterEvent>
#include <QToolTip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _label = new HoverLabel("Origin:", "Starting point(Longitude,Latitude) of tree's creation.", _ui->widgetOrigin);
    _label = new HoverLabel("Heading (0 to 360):", "Tree rotation." , _ui->widgetHeading);
    _label = new HoverLabel("Distance (NM):", "Distance between generation points." , _ui->widgetDistance);
    _label = new HoverLabel("MSL (m):", "Altitude above sea level." , _ui->widgetMsl);
    _label = new HoverLabel("Select Earth Model:", "Calculation Model." , _ui->widgetModel);

}

MainWindow::~MainWindow(){
    delete _ui;
}

void MainWindow::on_calculateButton_clicked(){

    _fromUserInputToOutput();
}

void MainWindow::_fromUserInputToOutput(){

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
        _ui->latitudeBox->text().toDouble(),
        _ui->longitudeBox->text().toDouble(),
        _ui->distanceBox->text().toDouble(),
        _ui->headingBox->text().toDouble(),
        _ui->mslBox->text().toDouble(),
        _ui->modelInput->currentIndex()
    );

    if(success)
        _displayResults();
}

void MainWindow::_displayResults() {
    QMessageBox::information(this, "Success", "Coordinate calcolate e salvate nel file KML.");
}

void MainWindow::on_onWebButton_clicked()
{
    QString htmlFilePath = "https://earth.google.com/web";
    QDesktopServices::openUrl(QUrl(htmlFilePath));
}



