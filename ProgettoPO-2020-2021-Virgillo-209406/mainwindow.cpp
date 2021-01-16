/*
This file is part of ProgettoPO

ProgettoPO is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ProgettoPO is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ProgettoPO.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestore.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gestore = new Gestore();

    pageArticolo = new paginaArticolo(gestore);
    ui->stackedWidget->addWidget(pageArticolo);

    pageAutore = new paginaAutore(gestore);
    ui->stackedWidget->addWidget(pageAutore);

    pageConferenza = new paginaConferenza(gestore);
    ui->stackedWidget->addWidget(pageConferenza);

    pageRivista = new paginaRivista(gestore);
    ui->stackedWidget->addWidget(pageRivista);

    connect(ui->buttonHome, &QPushButton::clicked, pageAutore, &paginaAutore::clearCampiAutore);
    connect(ui->buttonHome, &QPushButton::clicked, pageArticolo, &paginaArticolo::clearCampiArticolo);
    connect(ui->buttonHome, &QPushButton::clicked, pageConferenza, &paginaConferenza::clearCampiConferenza);
    connect(ui->buttonHome, &QPushButton::clicked, pageRivista, &paginaRivista::clearCampiRivista);


    ui->stackedWidget->setCurrentWidget(ui->Home);

    ui->buttonHome->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gestore;
    delete pageArticolo;
    delete pageAutore;
    delete pageConferenza;
    delete pageRivista;
}

void MainWindow::on_buttonAutore_clicked()
{
    ui->stackedWidget->setCurrentWidget(pageAutore);
}

void MainWindow::on_buttonArticolo_clicked()
{
    if(gestore->getAutori().empty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Errore", "Devi prima inserire almeno un autore", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    if(gestore->getConferenze().empty() == true && gestore->getRiviste().empty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Errore", "Devi prima inserire almeno una conferenza o una rivista", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    ui->stackedWidget->setCurrentWidget(pageArticolo);
}

void MainWindow::on_buttonConferenza_clicked()
{
    ui->stackedWidget->setCurrentWidget(pageConferenza);
}

void MainWindow::on_buttonRivista_clicked()
{
    ui->stackedWidget->setCurrentWidget(pageRivista);
}

void MainWindow::on_buttonHome_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Home);
}
void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    if (arg1 != 0)
         ui->buttonHome->setDisabled(false);
    else
        ui->buttonHome->setDisabled(true);
}
