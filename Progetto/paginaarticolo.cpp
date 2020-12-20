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

#include "paginaarticolo.h"
#include "ui_paginaarticolo.h"

#include <QMessageBox>

paginaArticolo::paginaArticolo(Gestore* _gestore, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paginaArticolo)
{
    ui->setupUi(this);
    gestore = _gestore;

    ui->stackedWidget->setCurrentWidget(ui->Home);

}

paginaArticolo::~paginaArticolo()
{
    delete ui;
}

void paginaArticolo::on_buttonAggiungi_clicked()
{
    if(ui->Titolo->text().isEmpty() || ui->NumeroPagine->value() == 0 || ui->Keywords->text().isEmpty()  || ui->Prezzo->value() == 0.0)
        {
            QMessageBox errore(QMessageBox::Critical, "Errore", "Uno o più campi obbligatori sono vuoti", QMessageBox::Ok, this);
            errore.exec();
            return;
        }

        QString titolo = ui->Titolo->text();

        QList<QString> lista_keywords;
        QString keywords = ui->Keywords->text();
        lista_keywords = keywords.split(",");

        int numeroPagine = ui->NumeroPagine->value();
        float prezzo = ui->Prezzo->value();

        QList<Autore> autori;
        for (int i = 0; i < ui->listAutori->count(); i++)
            if (ui->listAutori->item(i)->checkState() == true)
                autori.push_back(gestore->getAutori().at(i));

        QList<Articolo> articoliCorrelati;
        for (int i = 0; i < ui->listArticoliCorrelati->count(); i++)
            if (ui->listArticoli->item(i)->checkState() == true)
                articoliCorrelati.push_back(gestore->getArticoli().at(i));

        QString editore;
        if (ui->buttonConferenze->isChecked())
        {
            int idx = ui->PubblicatoPer->currentIndex();
            editore = gestore->getConferenze().at(idx).getNome();
        }
        else if(ui->buttonRiviste->isChecked())
        {
            int idx = ui->PubblicatoPer->currentIndex();
            editore = gestore->getRiviste().at(idx).getNome();
        }


        Articolo articolo(0, titolo, numeroPagine, prezzo, autori, lista_keywords, articoliCorrelati, editore);

        if(gestore->aggiungiArticolo(articolo) == true)
            QMessageBox::information(this, "Success", "Articolo aggiunto con successo!", QMessageBox::Ok);

        QString string_articolo = titolo;
        ui->listArticoli->addItem(string_articolo);

        ui->Titolo->clear();
        ui->Keywords->clear();
        ui->NumeroPagine->setValue(0);
        ui->Prezzo->setValue(0);
        ui->listAutori->clear();
        ui->listArticoli->clear();
        ui->PubblicatoPer->clear();
        ui->buttonVisualizzaArticoli->setChecked(false);
         ui->buttonVisualizzaAutori->setChecked(true);
}

void paginaArticolo::on_buttonVisualizzaAutori_clicked()
{
    if(ui->listAutori->count() != 0)
        ui->listAutori->clear();

    int idx = 0;
    QList<Autore> autori = gestore->getAutori();
    for (auto it = autori.begin(); it != autori.end(); it++)
    {
        QString string_autore = it->getNome() + " " + it->getCongome();
        ui->listAutori->addItem(string_autore);

        ui->listAutori->item(idx)->setCheckState(Qt::Unchecked);
        idx++;
    }
}

void paginaArticolo::on_buttonVisualizzaArticoli_clicked()
{
    if(ui->listArticoli->count() != 0)
        ui->listArticoli->clear();

    int idx = 0;
    QList<Articolo> articoli = gestore->getArticoli();
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
        ui->listArticoli->addItem(it->getTitolo());

        ui->listArticoli->item(idx)->setCheckState(Qt::Unchecked);
        idx++;
    }
}
void paginaArticolo::on_buttonConferenze_clicked()
{
    if(ui->PubblicatoPer->count() != 0)
        ui->PubblicatoPer->clear();

    QList<Conferenza> conferenze = gestore->getConferenze();
    for (auto it = conferenze.begin(); it != conferenze.end(); it++)
    {
        QString string_conferenza = it->getNome();
        ui->PubblicatoPer->addItem(string_conferenza);
    }
}

void paginaArticolo::on_buttonRiviste_clicked()
{
    if(ui->PubblicatoPer->count() != 0)
        ui->PubblicatoPer->clear();

    QList<Rivista> riviste = gestore->getRiviste();
    for (auto it = riviste.begin(); it != riviste.end(); it++)
    {
        QString string_rivista = it->getNome();
        ui->PubblicatoPer->addItem(string_rivista);
    }

}

void paginaArticolo::on_listArticoli_itemDoubleClicked(QListWidgetItem *item)
{
    int idx = ui->listArticoli->currentRow();
    Dialog dialog(gestore, "Articolo", idx);
    dialog.setModal(true);
    dialog.exec();
}

