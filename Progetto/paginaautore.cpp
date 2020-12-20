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

#include "paginaautore.h"
#include "ui_paginaautore.h"

#include <QMessageBox>

paginaAutore::paginaAutore(Gestore* _gestore, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::paginaAutore)
{
    ui->setupUi(this); 
    gestore = _gestore;
    ui->stackedWidget->setCurrentWidget(ui->Home);
}

paginaAutore::~paginaAutore()
{
    delete ui;
}

void paginaAutore::on_buttonAggiungi_clicked()
{
    if(ui->Nome->text().isEmpty() || ui->Cognome->text().isEmpty())
    {
        QMessageBox errore(QMessageBox::Critical, "Errore", "Uno o più campi obbligatori sono vuoti", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    QString nome = ui->Nome->text();
    QString cognome = ui->Cognome->text();

    QList<QString> lista_afferenze;
    if (!ui->Afferenze->toPlainText().isEmpty())
    {
        QString afferenze = ui->Afferenze->toPlainText();
        lista_afferenze = afferenze.split("\n");
    }

    Autore autore(0, nome, cognome, lista_afferenze);

    if(gestore->aggiungiAutore(autore) == true)
        QMessageBox::information(this, "Success", "Autore aggiunto con successo!", QMessageBox::Ok);

    QString string_autore = nome + " " + cognome;
    ui->listAutori->addItem(string_autore);

    ui->Nome->clear();
    ui->Cognome->clear();
    ui->Afferenze->clear();
}

void paginaAutore::on_listAutori_itemDoubleClicked(QListWidgetItem *item)
{
    int idx = ui->listAutori->currentRow();
    Dialog dialog(gestore, "Autore", idx);
    dialog.setModal(true);
    dialog.exec();
}
