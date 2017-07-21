#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QCloseEvent>
#include <QLayout>
#include "breadcrumb/breadcrumbview.h"

//! The main window of the application that holds the individual components.
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    readSettings();
    //this->setStyleSheet("background-color:white;");
    boost::filesystem::path test("home/flo/ownCloud/Dokumente/SDAJ");
    //sBreadcrumbView* breadcrumbView = new BreadcrumbView(this, test, 12);
    //setCentralWidget(breadcrumbView);
    statusBar()->showMessage(QString("Ready"));
}

//! This function persistently stores settings of the application.
void MainWindow::writeSettings() {
    QSettings settings("FlorettiKonfetti Inc.", "Otiat");

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

//! This function reads the persisted settings and restores the program's state.
void MainWindow::readSettings() {
    QSettings settings("FlorettiKonfetti Inc.", "Otiat");

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(600, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    writeSettings();
    event->accept();
}

MainWindow::~MainWindow() {
    delete ui;
}
