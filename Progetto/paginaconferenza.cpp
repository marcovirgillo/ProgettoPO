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

#include "paginaconferenza.h"
#include "ui_paginaconferenza.h"
#include <QMessageBox>
#include <QtGlobal>

paginaConferenza::paginaConferenza(Gestore* _gestore, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paginaConferenza)
{
    ui->setupUi(this);
    gestore = _gestore;
    ui->stackedWidget->setCurrentWidget(ui->Home);
}

paginaConferenza::~paginaConferenza()
{
    delete ui;
}

void paginaConferenza::clearCampiConferenza()
{
    ui->Nome->clear();
    ui->Acronimo->clear();
    ui->Luogo->clear();
    ui->Organizzatori->clear();
    ui->NumeroPartecipanti->setValue(0);
    ui->Data->setCurrentPage(QDate::currentDate().year(), QDate::currentDate().month());
}

void paginaConferenza::showDialogConferenza()
{
    int idx = ui->listConferenze->currentRow();
    Dialog dialog(gestore, "Conferenza", idx);
    dialog.setModal(true);
    dialog.exec();
}

void paginaConferenza::on_buttonAggiungi_clicked()
{
    if(ui->Nome->text().isEmpty() || ui->Luogo->text().isEmpty() || ui->Organizzatori->toPlainText().isEmpty() || ui->NumeroPartecipanti->value() == 0)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Uno o più campi obbligatori sono vuoti", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    QString nome = ui->Nome->text();
    QString acronimo = ui->Acronimo->text();
    QString luogo = ui->Luogo->text();

    QList<QString> lista_organizzatori;
    QString organizzatori = ui->Organizzatori->toPlainText();
    lista_organizzatori = organizzatori.split("\n");

    int numeroPartecipanti = ui->NumeroPartecipanti->value();

    QDate data = ui->Data->selectedDate();
    QString data_string = (data.toString(Qt::DateFormat::ISODate));

    Conferenza conferenza(nome, acronimo, luogo, data_string, numeroPartecipanti, lista_organizzatori);

    if(gestore->aggiungiConferenza(conferenza) == true)
    {
        QMessageBox::information(this, "Success", "Conferenza aggiunta con successo!", QMessageBox::Ok);
        QString string_conferenza = nome + " - " + "Data " + data_string;
        ui->listConferenze->addItem(string_conferenza);
    }
    else
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Conferenza già presente nella lista", QMessageBox::Ok, this);
        errore.exec();
        clearCampiConferenza();
        return;
    }
    clearCampiConferenza();
}

void paginaConferenza::on_listConferenze_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    showDialogConferenza();
}
