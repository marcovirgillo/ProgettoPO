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
    if(ui->Titolo->text().isEmpty() || ui->Keywords->toPlainText().isEmpty()
            || ui->NumeroPagine->value() == 0 || ui->Prezzo->value() == 0.0)
        {
            QMessageBox errore(QMessageBox::Critical, "Errore", "Uno o più campi obbligatori sono vuoti", QMessageBox::Ok, this);
            errore.exec();
            return;
        }

        Articolo articolo;

        QString titolo = ui->Titolo->text();
        articolo.setTitolo(titolo);

        QList<QString> lista_keywords;
        QString keywords = ui->Keywords->toPlainText();
        lista_keywords = keywords.split("\n");
        articolo.setKeywords(lista_keywords);

        int numeroPagine = ui->NumeroPagine->value();
        articolo.setNumeroPagine(numeroPagine);

        float prezzo = ui->Prezzo->value();
        articolo.setNumeroPagine(prezzo);

        if(gestore->aggiungiArticolo(articolo) == true)
            QMessageBox::information(this, "Success", "Articolo aggiunto con successo!", QMessageBox::Ok);


        ui->Titolo->clear();
        ui->Keywords->clear();
        ui->ArticoliCorrelati->clear();
        ui->NumeroPagine->setValue(0);
        ui->Prezzo->setValue(0);
        ui->Tipo->setCurrentIndex(0);
}

void paginaArticolo::on_buttonVisualizza_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizza);
}
