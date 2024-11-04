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
    _labelOrigin = new HoverLabel("Origin:", "Starting point(Longitude,Latitude) of tree's creation.", _ui->widgetOrigin);
    _labelHeading = new HoverLabel("Heading (0 to 360):", "Tree rotation." , _ui->widgetHeading);
    _labelDistance = new HoverLabel("Distance (NM):", "Distance between generation points." , _ui->widgetDistance);
    _labelMsl = new HoverLabel("MSL (m):", "Altitude above sea level." , _ui->widgetMsl);
    _labelModel = new HoverLabel("Select Earth Model:", "Calculation Model." , _ui->widgetModel);
    _ui->widgetMsl->hide();
    _ui->widgetCheckBox->hide();
    _ui->widgetFileName->hide();
}

MainWindow::~MainWindow(){
    delete _ui;
}

void MainWindow::on_calculateButton_clicked(){
    _fromUserInputToOutput();
}

void MainWindow::_fromUserInputToOutput(){

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

    //Dati da passare
    QString urlSafeFileName = QUrl::toPercentEncoding(_ui->lineFileName->text());
    bool success = true;

    if (_ui->checkBox->isChecked()) {
        PathCalculatorManager manager(pathSpecP2P, urlSafeFileName.toStdString()+"_p2p", false);
        success = manager.genPath(
            _ui->latitudeBox->text().toDouble(),
            _ui->longitudeBox->text().toDouble(),
            _ui->distanceBox->text().toDouble(),
            _ui->headingBox->text().toDouble(),
            _ui->mslBox->text().toDouble(),
            _ui->modelInput->currentIndex()
        );
    }

    if (_ui->checkBox_2->isChecked()) {
        PathCalculatorManager manager(pathSpecOrigin, urlSafeFileName.toStdString()+"_fo", true);
        success = manager.genPath(
            _ui->latitudeBox->text().toDouble(),
            _ui->longitudeBox->text().toDouble(),
            _ui->distanceBox->text().toDouble(),
            _ui->headingBox->text().toDouble(),
            _ui->mslBox->text().toDouble(),
            _ui->modelInput->currentIndex()
        ) && success;
    }

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

void MainWindow::on_checkBox_3_toggled(bool checked){
    if (checked) {
        _ui->widgetMsl->show();
        _ui->widgetCheckBox->show();
        _ui->widgetFileName->show();
    } else {
        _ui->widgetMsl->hide();
        _ui->widgetCheckBox->hide();
        _ui->widgetFileName->hide();
    }
}

