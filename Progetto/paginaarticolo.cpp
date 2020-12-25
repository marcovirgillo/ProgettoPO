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
#include <QtGlobal>
//#include <QCommonStyle> va incluso per le frecce sui PushButton
#include <QDebug>

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
// Inserimento e visualizzazione articolo
void paginaArticolo::clearCampiArticolo()
{
    ui->Titolo->clear();
    ui->Keywords->clear();
    ui->NumeroPagine->setValue(0);
    ui->Prezzo->setValue(0);
    ui->listAutori->clear();
    ui->listArticoliCorrelati->clear();
    ui->PubblicatoPer->clear();

    ui->buttonConferenze->setAutoExclusive(false);
    ui->buttonConferenze->setChecked(false);
    ui->buttonConferenze->setAutoExclusive(true);

    ui->buttonRiviste->setAutoExclusive(false);
    ui->buttonRiviste->setChecked(false);
    ui->buttonRiviste->setAutoExclusive(true);

    ui->stackedWidget->setCurrentWidget(ui->Home);
}

void paginaArticolo::showDialog(QString TipoClasse)
{
    int idx = ui->listArticoli->currentRow();
    Dialog dialog(gestore, TipoClasse, idx);
    dialog.setModal(true);
    dialog.exec();
}

void paginaArticolo::on_buttonAggiungi_clicked()
{
    bool checkAutoreSelezionato = false;
    for (int i = 0; i < ui->listAutori->count(); i++)
        if (ui->listAutori->item(i)->checkState() == Qt::Checked)
            checkAutoreSelezionato = true;

    if(ui->Titolo->text().isEmpty() || ui->NumeroPagine->value() == 0 || ui->Keywords->text().isEmpty()  || ui->Prezzo->value() == 0.0
             || checkAutoreSelezionato == false || (!ui->buttonConferenze->isChecked() && !ui->buttonRiviste->isChecked())
            || ((ui->buttonConferenze->isChecked() || ui->buttonRiviste->isChecked()) && ui->PubblicatoPer->count() == 0) )
        {
            QMessageBox errore(QMessageBox::Critical, "Error", "Uno o più campi obbligatori sono vuoti", QMessageBox::Ok, this);
            errore.exec();
            return;
        }
    int identificativo = gestore->getIdentificativoArticolo();
    QString titolo = ui->Titolo->text();

    QList<QString> lista_keywords;
    QString keywords = ui->Keywords->text();
    lista_keywords = keywords.split(",");

    int numeroPagine = ui->NumeroPagine->value();
    float prezzo = ui->Prezzo->value();

    QList<Autore> autori;
    for (int i = 0; i < ui->listAutori->count(); i++)
        if (ui->listAutori->item(i)->checkState() == Qt::Checked)
            autori.push_back(gestore->getAutori().at(i));

    QList<Articolo> articoliCorrelati;
    for (int i = 0; i < ui->listArticoliCorrelati->count(); i++)
        if (ui->listArticoliCorrelati->item(i)->checkState() == Qt::Checked)
            articoliCorrelati.push_back(gestore->getArticoli().at(i));

    Articolo articolo(identificativo, titolo, numeroPagine, prezzo, autori, lista_keywords, articoliCorrelati);

    if(gestore->aggiungiArticolo(articolo) == true)
    {
        if (ui->buttonConferenze->isChecked())
        {
            int idx = ui->PubblicatoPer->currentIndex();
            gestore->setArticoloInConferenza(idx, articolo);
            gestore->setArticoloPubblicatoPer(articolo, "Conferenza");
        }
        else if(ui->buttonRiviste->isChecked())
        {
            int idx = ui->PubblicatoPer->currentIndex();
            gestore->setArticoloInRivista(idx, articolo);
            gestore->setArticoloPubblicatoPer(articolo, "Rivista");
        }

        QMessageBox::information(this, "Success", "Aticolo aggiunto con successo!", QMessageBox::Ok);
        QString string_articolo = "ID: " + QString::number(identificativo) + " " + titolo;
        ui->listArticoli->addItem(string_articolo);
    }
    else
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Articolo già presente nella lista", QMessageBox::Ok, this);
        errore.exec();
        clearCampiArticolo();
        return;
    }
    clearCampiArticolo();
}

void paginaArticolo::on_buttonVisualizzaAutori_clicked()
{
    if(ui->listAutori->count() != 0)
        ui->listAutori->clear();

    int idx = 0;
    QList<Autore> autori = gestore->getAutori();
    for (auto it = autori.begin(); it != autori.end(); it++)
    {
        QString string_autore = "ID: " + QString::number(it->getIdentificativo()) + " " + it->getNome() + " " + it->getCognome();
        ui->listAutori->addItem(string_autore);
        ui->listAutori->item(idx)->setCheckState(Qt::Unchecked);
        idx++;
    }
}

void paginaArticolo::on_buttonVisualizzaArticoli_clicked()
{
    if(ui->listArticoliCorrelati->count() != 0)
        ui->listArticoliCorrelati->clear();

    int idx = 0;
    QList<Articolo> articoli = gestore->getArticoli();
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
        QString string_articolo = "ID: " + QString::number(it->getIdentificativo()) + " "  + it->getTitolo();
        ui->listArticoliCorrelati->addItem(string_articolo);
        ui->listArticoliCorrelati->item(idx)->setCheckState(Qt::Unchecked);
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
        QString string_conferenza = it->getNome() + " - " + "Data " + it->getData();
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
        QString string_rivista = it->getNome() + " - " + "Volume " + QString::number(it->getVolume());
        ui->PubblicatoPer->addItem(string_rivista);
    }
}

void paginaArticolo::on_listArticoli_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    showDialog("Articolo");
}

void paginaArticolo::disableRadioButton(QRadioButton* radioButton)
{
    radioButton->setAutoExclusive(false);
    radioButton->setChecked(false);
    radioButton->setAutoExclusive(true);
}

bool paginaArticolo::listArticoliVuota(QRadioButton* radioButton)
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

void paginaArticolo::visualizzaArticoliInLista(QList<Articolo> articoli, QListWidget* listArticoli)
{
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
        QString string_articolo = "ID: " + QString::number(it->getIdentificativo()) + " "  + it->getTitolo();
        listArticoli->addItem(string_articolo);
    }
}
//Fine inserimento e visualizzazione articolo

// Sezione B - Visualizzare tutti gli articoli di un autore
void paginaArticolo::clearPage2()
{
    ui->page2_NomeAutore->clear();
    ui->page2_CognomeAutore->clear();
    ui->page2_listArticoli->clear();
    ui->page2_listAutori->clear();
}

void paginaArticolo::on_buttonVisualizzaArticoliAutore_clicked()
{
    if (listArticoliVuota(ui->buttonVisualizzaArticoliAutore) == true)
        return;
    clearPage2();
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizzaArticoliAutore);
    disableRadioButton(ui->buttonVisualizzaArticoliAutore);
}

void paginaArticolo::on_page2_buttonIndietro_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Home);
    clearPage2();
}

void paginaArticolo::on_page2_buttonCerca_clicked()
{
    QString nomeAutore = ui->page2_NomeAutore->text();
    QString cognomeAutore = ui->page2_CognomeAutore->text();

    clearPage2();
    if(nomeAutore.isEmpty() == true || cognomeAutore.isEmpty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Inserisci il nome di un autore valido", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    QList<Autore> autori = gestore->getAutori();
    bool check = false;
    for (auto it = autori.begin(); it != autori.end(); it++)
    {
        if(nomeAutore == it->getNome() && cognomeAutore == it->getCognome())
        {
            check = true;
            QString string_autore = "ID: " + QString::number(it->getIdentificativo()) + " " + it->getNome() + " " + it->getCognome();
            ui->page2_listAutori->addItem(string_autore);
        }
    }
    if(check == false)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Nessun autore con questo nome trovato o l'autore non ha ancora scritto articoli", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
}

void paginaArticolo::on_page2_buttonSeleziona_clicked()
{
    if(ui->page2_listAutori->currentRow() == -1)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Devi prima selezionare un autore", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    int idxAutore = ui->page2_listAutori->currentRow();
    QList<Articolo> articoli;
    gestore->getArticoliDiUnAutore(articoli, gestore->getAutori().at(idxAutore));
    visualizzaArticoliInLista(articoli, ui->page2_listArticoli);
}
//Fine metodo

//Sezione B - Visualizzare tutti gli articoli pubblicati dai membri di una struttura
void paginaArticolo::clearPage3()
{
    ui->page3_Struttura->clear();
    ui->page3_listArticoli->clear();
}

void paginaArticolo::on_buttonVisualizzaArticoliStruttura_clicked()
{
    if(listArticoliVuota(ui->buttonVisualizzaArticoliStruttura) == true)
        return;
    clearPage3();
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizzaArticoliStruttura);
    disableRadioButton(ui->buttonVisualizzaArticoliStruttura);
}

void paginaArticolo::on_page3_buttonIndietro_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Home);
    clearPage3();
}

void paginaArticolo::on_page3_buttonCerca_clicked()
{
    QString struttura = ui->page3_Struttura->text();
    clearPage3();
    if(struttura.isEmpty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Inserisci il nome di una struttura valido", QMessageBox::Ok, this);
        errore.exec();
        return;
    }

    QList<Articolo> articoli;
    gestore->getArticoliDiUnaStruttura(articoli, struttura);
    if(articoli.isEmpty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Nessuna struttura con questo nome trovata", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    visualizzaArticoliInLista(articoli, ui->page3_listArticoli);
}
//Fine metodo

//Sezione B - Visualizzare tutti gli articoli relativi a una rivista
void paginaArticolo::clearPage4()
{
    ui->page4_NomeRivista->clear();
    ui->page4_VolumeRivista->setValue(0);
    ui->page4_Data->setCurrentPage(QDate::currentDate().year(), QDate::currentDate().month());
    ui->page4_listArticoli->clear();
}

void paginaArticolo::on_buttonVisualizzaArticoliRivista_clicked()
{
    if(listArticoliVuota(ui->buttonVisualizzaArticoliRivista) == true)
        return;
    clearPage4();
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizzaArticoliRivista);
    disableRadioButton(ui->buttonVisualizzaArticoliRivista);
}

void paginaArticolo::on_page4_buttonIndietro_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->Home);
   clearPage4();
}

void paginaArticolo::on_page4_buttonCerca_clicked()
{
    QString nomeRivista = ui->page4_NomeRivista->text();
    int volume = ui->page4_VolumeRivista->value();
    QDate data = ui->page4_Data->selectedDate();
    QString data_string = (data.toString(Qt::DateFormat::ISODate));

    clearPage4();
    if(nomeRivista.isEmpty() == true || volume == 0)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Inserisci una rivista valida", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    QList<Articolo> articoli;
    gestore->getArticoliDiUnaRivista(articoli, nomeRivista, volume, data_string);

    if(articoli.isEmpty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Nessuna rivista trovata o la rivista non ha articoli", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
     visualizzaArticoliInLista(articoli, ui->page4_listArticoli);
}
//Fine metodo
