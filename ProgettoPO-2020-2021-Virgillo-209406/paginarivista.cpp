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
#include <QDebug>
#include <cassert>

paginaRivista::paginaRivista(Gestore* _gestore, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paginaRivista)
{
    ui->setupUi(this);
    gestore = _gestore;

    ui->listRiviste->setToolTip("Fai doppio click su una rivista per visualizzarne le informazioni dettagliate");
    ui->stackedWidget->setCurrentWidget(ui->Home);
}

paginaRivista::~paginaRivista()
{
    delete ui;
}

// Inserimento e visualizzazione rivista
void paginaRivista::clearCampiRivista()
{
    ui->Nome->clear();
    ui->Acronimo->clear();
    ui->Editore->clear();
    ui->Volume->setValue(0);
    ui->Data->setCurrentPage(QDate::currentDate().year(), QDate::currentDate().month());

    ui->stackedWidget->setCurrentWidget(ui->Home);
}

void paginaRivista::disableRadioButton(QRadioButton* radioButton)
{
    radioButton->setAutoExclusive(false);
    radioButton->setChecked(false);
    radioButton->setAutoExclusive(true);
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

    QString nome = ui->Nome->text().trimmed();
    QString acronimo = ui->Acronimo->text().trimmed();
    QString editore = ui->Editore->text().trimmed();
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

void paginaRivista::on_buttonLeggi_clicked()
{
    QString pathFileRiviste = ui->Percorso->text();
    QFile fileRiviste(pathFileRiviste);

    if(!fileRiviste.open(QIODevice::ReadOnly))
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Il percorso specificato non è stato trovato", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    QTextStream stream(&fileRiviste);
    QString line = stream.readLine();
    QVector<QString> parametriRivista;
    while (!line.isNull())
    {
        if(line == "NOME" || line == "ACRONIMO" || line == "EDITORE" || line == "VOLUME" || line == "DATA")
        {
            line = stream.readLine();
            continue;
        }
        else if (line != "* * * * *")
            parametriRivista.push_back(line);
        else
        {
            QString nome = parametriRivista.at(0).trimmed();
            QString acronimo = parametriRivista.at(1).trimmed();
            QString editore = parametriRivista.at(2).trimmed();
            int volume = parametriRivista.at(3).trimmed().toInt();
            QString data = parametriRivista.at(4).trimmed();

            assert(!nome.isEmpty() && !editore.isEmpty() && volume > 0);

            Rivista rivista(nome, acronimo, editore, data, volume);
            if(gestore->aggiungiRivista(rivista) == true)
            {
                QString string_rivista = nome + " - " + "Volume " + QString::number(volume);
                ui->listRiviste->addItem(string_rivista);
            }
            parametriRivista.clear();
        }
        line = stream.readLine();
    }
    ui->Percorso->clear();
}

bool paginaRivista::listArticoliVuota(QRadioButton* radioButton)
{
    if(gestore->getArticoli().empty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Devi prima inserire almeno un articolo", QMessageBox::Ok, this);
        errore.exec();
        disableRadioButton(radioButton);
        return true;
    }
    return false;
}

void paginaRivista::visualizzaRivisteInLista(QList<Rivista> riviste, QListWidget* listRiviste)
{
    for (auto it = riviste.begin(); it != riviste.end(); it++)
    {
        QString string_rivista = it->getNome() + " - " + "Volume " + QString::number(it->getVolume());
        listRiviste->addItem(string_rivista);
    }
}
//Fine inserimento e visualizzazione conferenza

/*Sezione E - Visualizzare le riviste specialistiche. Una rivista R1 è considerata specialistica se esiste
un’altra rivista R2, tale che le keyword degli articoli di R1 sono un sottoinsieme proprio di tutte le keyword degli articoli di R2* */
void paginaRivista::on_buttonVisualizzaRivisteSpecialistiche_clicked()
{
    if(listArticoliVuota(ui->buttonVisualizzaRivisteSpecialistiche) == true)
        return;
    ui->page2_listRiviste->clear();
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizzaRivisteSpecialistiche);
    disableRadioButton(ui->buttonVisualizzaRivisteSpecialistiche);

    QList<Rivista> riviste = gestore->getRivisteSpecialistiche();
    visualizzaRivisteInLista(riviste, ui->page2_listRiviste);
}

void paginaRivista::on_page2_buttonIndietro_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Home);
    ui->page2_listRiviste->clear();
}
