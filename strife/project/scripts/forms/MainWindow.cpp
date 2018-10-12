#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "Engine.h"
#include "events/RenderEvent.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    //new QTreeWidgetItem();
}
