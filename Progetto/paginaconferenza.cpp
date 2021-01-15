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
#include <QFile>
#include <QTextStream>
#include <QtGlobal>
#include <cassert>

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

// Inserimento e visualizzazione conferenza
void paginaConferenza::clearCampiConferenza()
{
    ui->Nome->clear();
    ui->Acronimo->clear();
    ui->Luogo->clear();
    ui->Organizzatori->clear();
    ui->NumeroPartecipanti->setValue(0);
    ui->Data->setCurrentPage(QDate::currentDate().year(), QDate::currentDate().month());

    ui->stackedWidget->setCurrentWidget(ui->Home);
}

void paginaConferenza::disableRadioButton(QRadioButton* radioButton)
{
    radioButton->setAutoExclusive(false);
    radioButton->setChecked(false);
    radioButton->setAutoExclusive(true);
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

    Conferenza conferenza(nome, acronimo, luogo, data_string, numeroPartecipanti, lista_organizzatori.toVector());

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
        return;
    }
    clearCampiConferenza();
}

void paginaConferenza::on_listConferenze_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    showDialogConferenza();
}

void paginaConferenza::on_buttonLeggi_clicked()
{
    QString pathFileConferenze = ui->Percorso->text();
    QFile fileConferenze(pathFileConferenze);

    if(!fileConferenze.open(QIODevice::ReadOnly))
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Il percorso specificato non è stato trovato", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    QTextStream stream(&fileConferenze);
    QString line = stream.readLine();
    QVector<QString> parametriConferenza;
    while (!line.isNull())
    {
        if (line != "* * * * *")
            parametriConferenza.push_back(line);
        else if(line == "NOME" || "ACRONIMO" || line == "LUOGO" || line == "ORGANIZZATORI" || line == "NUMERO PARTEICPANTI" || line == "DATA")
            continue;
        else
        {

            QString nome = parametriConferenza.at(0);
            QString acronimo = parametriConferenza.at(1);
            QString luogo = parametriConferenza.at(2);

            QList<QString> lista_organizzatori;
            QString organizzatori = parametriConferenza.at(3);
            lista_organizzatori = organizzatori.split(",");

            int numeroPartecipanti = parametriConferenza.at(4).toInt();
            QString data = parametriConferenza.at(5);

            assert(!nome.isEmpty() && !luogo.isEmpty() && !organizzatori.isEmpty() && numeroPartecipanti > 0);

            Conferenza conferenza(nome, acronimo, luogo, data, numeroPartecipanti, lista_organizzatori.toVector());
            if(gestore->aggiungiConferenza(conferenza) == true)
            {
                QString string_conferenza = nome + " - " + "Data " + data;
                ui->listConferenze->addItem(string_conferenza);
            }
            parametriConferenza.clear();
        }
        line = stream.readLine();
    }
    ui->Percorso->clear();
}


bool paginaConferenza::listArticoliVuota(QRadioButton* radioButton)
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

void paginaConferenza::visualizzaArticoliInLista(QList<Articolo> articoli, QListWidget* listArticoli)
{
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
        QString string_articolo = "ID: " + QString::number(it->getIdentificativo()) + " "  + it->getTitolo();
        listArticoli->addItem(string_articolo);
    }
}

void paginaConferenza::visualizzaConferenzeInLista(QList<Conferenza> conferenze, QListWidget* listConferenze)
{
    for (auto it = conferenze.begin(); it != conferenze.end(); it++)
    {
        QString string_conferenza = it->getNome() + " - " + "Data " + it->getData();
        listConferenze->addItem(string_conferenza);
    }
}

//Fine inserimento e visualizzazione conferenza

//Sezione C - Visualizzare il guadagno annuale di una conferenza calcolato come la somma dei prezzi degli articoli presentati per quella rivista in un anno
void paginaConferenza::clearPage2()
{
    ui->page2_listConferenze->clear();
    ui->page2_listArticoli->clear();
    ui->page2_GuadagnoTotale->clear();
}

void paginaConferenza::on_buttonVisualizzaGuadagnoAnnualeConferenza_clicked()
{
    if(listArticoliVuota(ui->buttonVisualizzaGuadagnoAnnualeConferenza) == true)
        return;
    clearPage2();
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizzaGuadagnoAnnualeConferenza);
    disableRadioButton(ui->buttonVisualizzaGuadagnoAnnualeConferenza);

    QList<Conferenza> conferenze = gestore->getConferenze();
    visualizzaConferenzeInLista(conferenze, ui->page2_listConferenze);
}

void paginaConferenza::on_page2_buttonIndietro_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Home);
    clearPage2();
}

void paginaConferenza::on_page2_buttonSeleziona_clicked()
{
    if(ui->page2_listConferenze->currentRow() == -1)
    {
        ui->page2_listArticoli->clear();
        ui->page2_GuadagnoTotale->clear();
        QMessageBox errore(QMessageBox::Critical, "Error", "Devi prima selezionare una conferenza", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    int idxConferenza = ui->page2_listConferenze->currentRow();
    QList<Articolo> articoli;
    float GuadagnoTotale = gestore->getGuadagnoAnnualeConferenza(articoli, idxConferenza);
    if(articoli.isEmpty() == true)
    {
        ui->page2_listArticoli->clear();
        ui->page2_GuadagnoTotale->clear();
        QMessageBox errore(QMessageBox::Critical, "Error", "Non sono stati ancora pubblicati articoli per questa conferenza", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    ui->page2_listArticoli->clear();
    visualizzaArticoliInLista(articoli, ui->page2_listArticoli);
    ui->page2_GuadagnoTotale->setText(QString::number(GuadagnoTotale));
}
//Fine metodo

//Sezione F - Visualizzare le conferenze simili ad una specificata dall’utente. Una conferenza è simile a un’altra conferenza se hanno almeno l’80% delle keyword in comune**
void paginaConferenza::clearPage3()
{
    ui->page3_listConferenze->clear();
    ui->page3_listConferenzeSimili->clear();
}

void paginaConferenza::on_buttonVisualizzaConferenzeSimili_clicked()
{
    if(listArticoliVuota(ui->buttonVisualizzaConferenzeSimili) == true)
        return;
    clearPage3();
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizzaConferenzeSimili);
    disableRadioButton(ui->buttonVisualizzaConferenzeSimili);

    QList<Conferenza> conferenze = gestore->getConferenze();
    visualizzaConferenzeInLista(conferenze, ui->page3_listConferenze);
}

void paginaConferenza::on_page3_buttonIndietro_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Home);
    clearPage3();
}

void paginaConferenza::on_page3_buttonSeleziona_clicked()
{
    if(ui->page3_listConferenze->currentRow() == -1)
    {
        ui->page3_listConferenzeSimili->clear();
        QMessageBox errore(QMessageBox::Critical, "Error", "Devi prima selezionare una conferenza", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    int idxConferenza = ui->page3_listConferenze->currentRow();
    QList<Conferenza> conferenze = gestore->getConferenzeSimili(idxConferenza);
    if(conferenze.isEmpty() == true)
    {
        ui->page3_listConferenzeSimili->clear();
        QMessageBox errore(QMessageBox::Critical, "Error", "Non sono state trovate conferenze simili a quella selezionata", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    ui->page3_listConferenzeSimili->clear();
    visualizzaConferenzeInLista(conferenze, ui->page3_listConferenzeSimili);
}
//Fine metodo
