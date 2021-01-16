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
#include <QtGlobal>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <cassert>

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

void paginaAutore::clearCampiAutore()
{
    ui->Nome->clear();
    ui->Cognome->clear();
    ui->Afferenze->clear();
}

void paginaAutore::showDialogAutore()
{
    int idx = ui->listAutori->currentRow();
    Dialog dialog(gestore, "Autore", idx);
    dialog.setModal(true);
    dialog.exec();
}

void paginaAutore::on_buttonAggiungi_clicked()
{
    if(ui->Nome->text().isEmpty() || ui->Cognome->text().isEmpty())
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Uno o più campi obbligatori sono vuoti", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    int identificativo = gestore->getCurrentIdentificativoAutore();
    QString nome = ui->Nome->text();
    QString cognome = ui->Cognome->text();

    QList<QString> lista_afferenze;
    if (!ui->Afferenze->toPlainText().isEmpty())
    {
        QString afferenze = ui->Afferenze->toPlainText();
        lista_afferenze = afferenze.split("\n");
        lista_afferenze.sort();
    }

    Autore autore(identificativo, nome, cognome, lista_afferenze.toVector());

    if(gestore->aggiungiAutore(autore) == true)
    {
        gestore->increaseIdentificativoAutore();
        QMessageBox::information(this, "Success", "Autore aggiunto con successo!", QMessageBox::Ok);
        QString string_autore = "ID: " + QString::number(identificativo) + " " + nome + " " + cognome;
        ui->listAutori->addItem(string_autore);
    }
    else
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Autore già presente nella lista", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    clearCampiAutore();
}

void paginaAutore::on_listAutori_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    showDialogAutore();
}

void paginaAutore::on_buttonLeggi_clicked()
{
    QString pathFileAutori = ui->Percorso->text();
    QFile fileAutori(pathFileAutori);

    if(!fileAutori.open(QIODevice::ReadOnly))
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Il percorso specificato non è stato trovato", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    QTextStream stream(&fileAutori);
    QString line = stream.readLine();
    QVector<QString> parametriAutore;
    while (!line.isNull())
    {
        if (line != "* * * * *")
            parametriAutore.push_back(line);
        else if(line == "NOME" || line == "COGNOME" || line == "AFFERENZE")
            continue;
        else
        {
            int identificativo = gestore->getCurrentIdentificativoAutore();
            QString nome = parametriAutore.at(0);
            QString cognome = parametriAutore.at(1);  
            assert(!nome.isEmpty() && !cognome.isEmpty());

            QList<QString> lista_afferenze;
            if (!parametriAutore.at(2).isEmpty())
            {
                QString afferenze = parametriAutore.at(2);
                lista_afferenze = afferenze.split(",");
                lista_afferenze.sort();
            }
            assert(!nome.isEmpty() && !nome.isEmpty());

            Autore autore(identificativo, nome, cognome, lista_afferenze.toVector());
            if(gestore->aggiungiAutore(autore) == true)
            {
                gestore->increaseIdentificativoAutore();
                QString string_autore = "ID: " + QString::number(identificativo) + " " + nome + " " + cognome;
                ui->listAutori->addItem(string_autore);
            }
            parametriAutore.clear();
        }
        line = stream.readLine();
    }
    ui->Percorso->clear();
}
