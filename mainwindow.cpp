#include "MainWindow.hpp"
#include "./ui_mainwindow.h"
#include "Manager.hpp"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QEnterEvent>
#include <QToolTip>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow){
    _ui->setupUi(this);

    //Create Hoverlabel
    _labelOrigin = new HoverLabel("<b>Origin:</b>", "Starting point(Longitude,Latitude) of tree's creation.", _ui->widgetOrigin);
    _labelHeading = new HoverLabel("<b>Heading (0 to 360):</b>", "Tree rotation." , _ui->widgetHeading);
    _labelDistance = new HoverLabel("<b>Distance (NM):</b>", "Distance between generation points." , _ui->widgetDistance);
    _labelMsl = new HoverLabel("<b>MSL (m):</b>", "Altitude above sea level." , _ui->widgetMsl);
    _labelModel = new HoverLabel("<b>Select Earth Model:</b>", "Calculation Model." , _ui->widgetModel);

    //set Advanced Settings disabled
    _ui->widgetMsl->setEnabled(false);
    _ui->widgetCheckBox->setEnabled(false);
    _ui->widgetFileName->setEnabled(false);
}

MainWindow::~MainWindow(){
    delete _ui;
}

void MainWindow::on_calculateButton_clicked(){
    _fromUserInputToOutput();
}

void MainWindow::_fromUserInputToOutput(){

    //Path to calculate points from the origin
    static const Type::PathSpec pathSpecOrigin = {
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

    //Path to calculate points from the previuos point
    static const Type::PathSpec pathSpecP2P = {
        {1.0, 90.0},
        {1.0, 0.0},
        {1.0, 90.0},
        {std::sqrt(2.0), -45.0},
        {1.0, 90.0},
        {3.0/std::sqrt(2.0), -45.0},
        {3.0/std::sqrt(2.0), -135.0},
        {1.0, 90.0},
        {std::sqrt(2), -135.0},
        {1.0, 90.0},
        {1.0, 180.0}
    };

    //Set correct Latitude in Flat and Spheric
    Type::Model model = _ui->modelInput->currentIndex();
    Type::Scalar latitude = _ui->latitudeBox->text().toDouble();
    if(std::abs (latitude) == 90 && model != 2u){
        latitude = latitude * 0.9999999999888889;
    }

    //Take file name from the GUI
    QString urlSafeFileName = QUrl::toPercentEncoding(_ui->lineFileName->text());
    bool success = true;

    //Send GUI input to "point to point path calculator"
    if (_ui->checkBox->isChecked()) {
        PathCalculatorManager manager(pathSpecP2P, urlSafeFileName.toStdString()+"_p2p", false);
        success = manager.genPath(
            latitude,
            _ui->longitudeBox->text().toDouble(),
            _ui->distanceBox->text().toDouble(),
            _ui->headingBox->text().toDouble(),
            _ui->mslBox->text().toDouble(),
            model
        );
    }

    //Send GUI input to "from origin calculator"
    if (_ui->checkBox_2->isChecked()) {
        PathCalculatorManager manager(pathSpecOrigin, urlSafeFileName.toStdString()+"_fo", true);
        success = manager.genPath(
            latitude,
            _ui->longitudeBox->text().toDouble(),
            _ui->distanceBox->text().toDouble(),
            _ui->headingBox->text().toDouble(),
            _ui->mslBox->text().toDouble(),
            model
        ) && success;
    }

    //Display messagges
    if(success)
        _displayResults();
    else
        _displayResultsN();

}

void MainWindow::_displayResults() {
    QMessageBox::information(this, "Success!", "Coordinates calculated and saved in the KML file.");
}

void MainWindow::_displayResultsN() {
    QMessageBox::information(this, "Error!", "Something went wrong while writing KML file.");
}

void MainWindow::on_onWebButton_clicked(){
    QString htmlFilePath = "https://earth.google.com/web";
    QDesktopServices::openUrl(QUrl(htmlFilePath));
}

//Enable and Disable advanced settings
void MainWindow::on_checkBox_3_toggled(bool checked){
    if (checked) {
        _ui->widgetMsl->setEnabled(true);
        _ui->widgetCheckBox->setEnabled(true);
        _ui->widgetFileName->setEnabled(true);
    } else {
        _ui->widgetMsl->setEnabled(false);
        _ui->widgetCheckBox->setEnabled(false);
        _ui->widgetFileName->setEnabled(false);
    }
}

