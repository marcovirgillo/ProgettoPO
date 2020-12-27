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

#include "paginarivista.h"
#include "ui_paginarivista.h"
#include <QMessageBox>
#include <QtGlobal>
#include <QFile>
#include <QTextStream>

paginaRivista::paginaRivista(Gestore* _gestore, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paginaRivista)
{
    ui->setupUi(this);
    gestore = _gestore;
    ui->stackedWidget->setCurrentWidget(ui->Home);
}

paginaRivista::~paginaRivista()
{
    delete ui;
}

void paginaRivista::clearCampiRivista()
{
    ui->Nome->clear();
    ui->Acronimo->clear();
    ui->Editore->clear();
    ui->Volume->setValue(0);
    ui->Data->setCurrentPage(QDate::currentDate().year(), QDate::currentDate().month());
}

void paginaRivista::showDialogRivista()
{
    int idx = ui->listRiviste->currentRow();
    Dialog dialog(gestore, "Rivista", idx);
    dialog.setModal(true);
    dialog.exec();
}

void paginaRivista::on_buttonAggiungi_clicked()
{
    if(ui->Nome->text().isEmpty() || ui->Editore->text().isEmpty() || ui->Volume->value() == 0)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Uno o più campi obbligatori sono vuoti", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    QString nome = ui->Nome->text();
    QString acronimo = ui->Acronimo->text();
    QString editore = ui->Editore->text();
    int volume = ui->Volume->value();
    QDate data = ui->Data->selectedDate();
    QString data_string = (data.toString(Qt::DateFormat::ISODate));

    Rivista rivista(nome, acronimo, editore, data_string, volume);

    if(gestore->aggiungiRivista(rivista) == true)
    {
        QMessageBox::information(this, "Success", "Rivista aggiunta con successo!", QMessageBox::Ok);
        QString string_rivista = nome + " - " + "Volume " + QString::number(volume);
        ui->listRiviste->addItem(string_rivista);
    }
    else
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Rivista già presente nella lista", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    clearCampiRivista();
}

void paginaRivista::on_listRiviste_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    showDialogRivista();
}
