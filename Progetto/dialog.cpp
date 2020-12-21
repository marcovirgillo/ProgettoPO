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

#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>

Dialog::Dialog(Gestore* _gestore, QString TipoClasse, int _idx, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->Articolo_Indietro, &QPushButton::clicked, this, &Dialog::close);
    connect(ui->Autore_Indietro, &QPushButton::clicked, this, &Dialog::close);
    connect(ui->Conferenza_Indietro, &QPushButton::clicked, this, &Dialog::close);
    connect(ui->Rivista_Indietro, &QPushButton::clicked, this, &Dialog::close);

    idx = _idx;
    gestore = _gestore;

    if (TipoClasse == "Autore")
        visualizzaAutore();
    if (TipoClasse == "Conferenza")
        visualizzaConferenza();
    if(TipoClasse == "Rivista")
        visualizzaRivista();
    if(TipoClasse == "Articolo")
    {
        _articolo = gestore->getArticoli().at(idx);
        VisualizzaArticolo();
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::visualizzaAutore()
{
    ui->stackedWidget->setCurrentWidget(ui->detailsAutore);
    Autore autore = gestore->getAutori().at(idx);
    ui->Autore_Identificativo->setText(QString::number(autore.getIdentificativo()));
    ui->Autore_Nome->setText(autore.getNome());
    ui->Autore_Cognome->setText(autore.getCongome());

    QList<QString> afferenze = autore.getAfferenze();
    for (auto it = afferenze.begin(); it != afferenze.end(); it++)
        ui->Autore_listAfferenze->addItem(*it);
}

void Dialog::visualizzaConferenza()
{
    ui->stackedWidget->setCurrentWidget(ui->detailsConferenza);
    Conferenza conferenza = gestore->getConferenze().at(idx);
    ui->Conferenza_Nome->setText(conferenza.getNome());
    ui->Conferenza_Acronimo->setText(conferenza.getAcronimo());
    ui->Conferenza_Luogo->setText(conferenza.getLuogo());

    QList<QString> organizzatori = conferenza.getOrganizzatori();
    for (auto it = organizzatori.begin(); it != organizzatori.end(); it++)
        ui->Conferenza_listOrganizzatori->addItem(*it);

    ui->Conferenza_NumeroPartecipanti->setValue(conferenza.getNumeroPartecipanti());
    ui->Conferenza_Data->setText(conferenza.getData());
}

void Dialog::visualizzaRivista()
{
    ui->stackedWidget->setCurrentWidget(ui->detailsRivista);
    Rivista rivista = gestore->getRiviste().at(idx);
    ui->Rivista_Nome->setText(rivista.getNome());
    ui->Rivista_Acronimo->setText(rivista.getAcronimo());
    ui->Rivista_Editore->setText(rivista.getEditore());
    ui->Rivista_Volume->setValue(rivista.getVolume());
    ui->Rivista_Data->setText(rivista.getData());
}

void Dialog::VisualizzaArticolo()
{
    ui->stackedWidget->setCurrentWidget(ui->detailsArticolo);
    Articolo articolo = gestore->getArticoli().at(idx);

    ui->Articolo_Identificativo->setText(QString::number(articolo.getIdentificativo()));
    ui->Articolo_Titolo->setText(articolo.getTitolo());
    QList<QString> keywords = articolo.getKeywords();
    for (auto it = keywords.begin(); it != keywords.end(); it++)
        ui->Articolo_listKeywords->addItem(*it);
    ui->Articolo_NumeroPagine->setValue(articolo.getNumeroPagine());
    ui->Articolo_Prezzo->setValue(articolo.getPrezzo());
    ui->Articolo_PubblicatoPer->setText(articolo.getEditore());

}

void Dialog::on_AutoriArticoli_activated(const QString &arg1)
{
    if (arg1 == "Autori")
    {
        QList<Autore> autori = _articolo.getAutori();

        for(auto it = autori.begin(); it != autori.end(); it++)
        {
            QString string_autore = it ->getNome();
            ui->listAutoriArticoli->addItem(string_autore);
        }
    }
    else if (arg1 == "Articoli correlati")
    {
        QList<Articolo> articoliCorrelati = _articolo.getArticoliCorrelati();
        for (auto it = articoliCorrelati.begin(); it != articoliCorrelati.end(); it++)
        {
            QString string_articolo = it->getTitolo();
            ui->listAutoriArticoli->addItem(string_articolo);
        }
    }
}
