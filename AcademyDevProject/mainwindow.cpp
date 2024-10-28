#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "coordinate_calculator.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), calculator() {
    ui->setupUi(this);
    connect(ui->onWebButton, &QPushButton::clicked, this, &MainWindow::onWebButtonClicked);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_calculateButton_clicked() {
    handleUserInput();
}

void MainWindow::handleUserInput() {
    // Lettura dei dati dall'interfaccia utente
    double lat = ui->latitudeInput->text().toDouble();
    double lon = ui->longitudeInput->text().toDouble();
    double heading = ui->headingInput->text().toDouble();
    double distance = ui->distanceInput->text().toDouble();
    int model = ui->modelInput->currentIndex() + 1;

    // Imposta i dati dell'origine
    Data data;
    data.origin = {lat, lon};
    data.dist = distance;
    data.heading = heading;
    data.model = model;

    // Calcola le coordinate in base al modello scelto
    calculator.computeCoordinates(data);

    // Mostra i risultati all'utente
    displayResults();
}

void MainWindow::displayResults() {
    // File salvato con successo
    QMessageBox::information(this, "Success", "Coordinate calcolate e salvate nel file KML.");
}

// Callback per il pulsante "onWeb"
void MainWindow::onWebButtonClicked() {
    // Definisci il percorso dell'URL da aprire
    QString htmlFilePath = "https://earth.google.com/web/@45.52015247,9.26697256,130.21959004a,1475.22100893d,30y,-0h,0t,0r/data=CgRCAggBOgMKATBKCAiDhoiXBBAA";

    // Verifica se il browser (Google Chrome come esempio) è già aperto
    QProcess process;
    process.start("pgrep", QStringList() << "chrome");

    // Attendi il risultato del comando
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    if (!output.isEmpty()) {
        // Se il processo è già aperto, chiudilo
        QProcess::execute("pkill", QStringList() << "chrome");
        QMessageBox::information(this, "onWeb", "Browser già aperto. Lo sto chiudendo e riaprendo...");
    }

    // Avvia il browser con l'URL specificato
    QDesktopServices::openUrl(QUrl(htmlFilePath));
}
