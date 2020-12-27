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
#include <QDebug>
#include <QFile>
#include <QTextStream>
//#include <QCommonStyle> va incluso per le frecce sui PushButton

//risolvere problema del seleziona premuto in maniera ossessiva nei metodi

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
//Inserimento e visualizzazione articolo
void paginaArticolo::clearCampiArticolo()
{
    ui->Titolo->clear();
    ui->Keywords->clear();
    ui->NumeroPagine->setValue(0);
    ui->Prezzo->setValue(0);
    ui->listAutori->clear();
    ui->listArticoliCorrelati->clear();
    ui->PubblicatoPer->clear();

    disableRadioButton(ui->buttonConferenze);
    disableRadioButton(ui->buttonRiviste);
    ui->stackedWidget->setCurrentWidget(ui->Home);
}

void paginaArticolo::disableRadioButton(QRadioButton* radioButton)
{
    radioButton->setAutoExclusive(false);
    radioButton->setChecked(false);
    radioButton->setAutoExclusive(true);
}

void paginaArticolo::showDialogArticolo()
{
    int idx = ui->listArticoli->currentRow();
    Dialog dialog(gestore, "Articolo", idx);
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
    int identificativo = gestore->getCurrentIdentificativoArticolo();
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
            int annoConferenza = gestore->getAnnoConferenza(idx);
            articolo.setAnno(annoConferenza);
        }
        else if(ui->buttonRiviste->isChecked())
        {
            int idx = ui->PubblicatoPer->currentIndex();
            gestore->setArticoloInRivista(idx, articolo);
            gestore->setArticoloPubblicatoPer(articolo, "Rivista");
            int annoRivista = gestore->getAnnoRivista(idx);
            articolo.setAnno(annoRivista);
        }
        gestore->increaseIdentificativoArticolo();
        QMessageBox::information(this, "Success", "Aticolo aggiunto con successo!", QMessageBox::Ok);
        QString string_articolo = "ID: " + QString::number(identificativo) + " " + titolo;
        ui->listArticoli->addItem(string_articolo);
    }
    else
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Articolo già presente nella lista", QMessageBox::Ok, this);
        errore.exec();
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
    showDialogArticolo();
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

void paginaArticolo::visualizzaAutoriInLista(QList<Autore> autori, QListWidget* listAutori)
{
    for (auto it = autori.begin(); it != autori.end(); it++)
    {
        QString string_autore = "ID: " + QString::number(it->getIdentificativo()) + " " + it->getNome() + " " + it->getCognome();
        listAutori->addItem(string_autore);
    }
}

void paginaArticolo::visualizzaArticoliInLista(QList<Articolo> articoli, QListWidget* listArticoli)
{
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
        QString string_articolo = "ID: " + QString::number(it->getIdentificativo()) + " "  + it->getTitolo();
        listArticoli->addItem(string_articolo);
    }
}

void paginaArticolo::visualizzaRivisteInLista(QList<Rivista> riviste, QListWidget* listRiviste)
{
    for (auto it = riviste.begin(); it != riviste.end(); it++)
    {
        QString string_rivista = it->getNome() + " - " + "Volume " + QString::number(it->getVolume());
        listRiviste->addItem(string_rivista);
    }
}
//Fine inserimento e visualizzazione articolo

//Sezione B - Visualizzare tutti gli articoli di un autore
void paginaArticolo::clearPage2()
{
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
    visualizzaAutoriInLista(gestore->getAutori(), ui->page2_listAutori);
}

void paginaArticolo::on_page2_buttonIndietro_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Home);
    clearPage2();
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
    gestore->getArticoliDiUnAutore(articoli, idxAutore);
    if(articoli.isEmpty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "L'autore non ha ancora pubblicato articoli", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    visualizzaArticoliInLista(articoli, ui->page2_listArticoli);
}
//Fine metodo

//Sezione B - Visualizzare tutti gli articoli pubblicati dai membri di una struttura
void paginaArticolo::clearPage3()
{
    ui->page3_listStrutture->clear();
    ui->page3_listArticoli->clear();
}

void paginaArticolo::on_buttonVisualizzaArticoliStruttura_clicked()
{
    if(listArticoliVuota(ui->buttonVisualizzaArticoliStruttura) == true)
        return;
    clearPage3();
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizzaArticoliStruttura);
    disableRadioButton(ui->buttonVisualizzaArticoliStruttura);
    QList<QString> strutture;
    gestore->getStrutture(strutture);
    for(auto it = strutture.begin(); it != strutture.end(); it++)
        ui->page3_listStrutture->addItem(*it);
}

void paginaArticolo::on_page3_buttonIndietro_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Home);
    clearPage3();
}

void paginaArticolo::on_page3_buttonSeleziona_clicked()
{
    if(ui->page3_listStrutture->currentRow() == -1)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Devi prima selezionare una struttura", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    int idxStruttura = ui->page3_listStrutture->currentRow();
    QListWidgetItem* itemStruttura = ui->page3_listStrutture->item(idxStruttura);
    QString struttura = itemStruttura->text();
    QList<Articolo> articoli;
    gestore->getArticoliDiUnaStruttura(articoli, struttura);
    if(articoli.isEmpty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "I membri di questa struttura non hanno ancora pubblicato articoli", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    visualizzaArticoliInLista(articoli, ui->page3_listArticoli);
}
//Fine metodo

//Sezione B - Visualizzare tutti gli articoli relativi a una rivista
void paginaArticolo::clearPage4()
{
    ui->page4_listRiviste->clear();
    ui->page4_listArticoli->clear();
}

void paginaArticolo::on_buttonVisualizzaArticoliRivista_clicked()
{
    if(listArticoliVuota(ui->buttonVisualizzaArticoliRivista) == true)
        return;
    clearPage4();
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizzaArticoliRivista);
    disableRadioButton(ui->buttonVisualizzaArticoliRivista);
    QList<Rivista> riviste = gestore->getRiviste();
    visualizzaRivisteInLista(riviste, ui->page4_listRiviste);
}

void paginaArticolo::on_page4_buttonIndietro_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->Home);
   clearPage4();
}

void paginaArticolo::on_page4_buttonSeleziona_clicked()
{
    if(ui->page4_listRiviste->currentRow() == -1)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Devi prima selezionare una rivista", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    int idxRivista = ui->page4_listRiviste->currentRow();
    QList<Articolo> articoli;
    gestore->getArticoliDiUnaRivista(articoli, idxRivista);
    if(articoli.isEmpty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Non sono stati ancora pubblicati articoli per questa rivista", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    visualizzaArticoliInLista(articoli, ui->page4_listArticoli);
}
//Fine metodo

//Sezione C - Visualizzare gli articoli con il prezzo più alto tra tutti gli articoli di un autore
void paginaArticolo::clearPage5()
{
    ui->page5_listArticoli->clear();
    ui->page5_listAutori->clear();
    ui->page5_PrezzoPiuAlto->clear();
}

void paginaArticolo::on_buttonVisualizzaArticoliCostosiAutore_clicked()
{
    if(listArticoliVuota(ui->buttonVisualizzaArticoliCostosiAutore) == true)
        return;
    clearPage5();
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizzaArticoliCostosiAutore);
    disableRadioButton(ui->buttonVisualizzaArticoliCostosiAutore);
    visualizzaAutoriInLista(gestore->getAutori(), ui->page5_listAutori);
}

void paginaArticolo::on_page5_buttonIndietro_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Home);
    clearPage5();
}

void paginaArticolo::on_page5_buttonSeleziona_clicked()
{
    if(ui->page5_listAutori->currentRow() == -1)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Devi prima selezionare un autore", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    int idxAutore = ui->page5_listAutori->currentRow();
    QList<Articolo> articoli;
    int prezzoPiuAlto = gestore->getArticoliCostosiAutore(articoli, idxAutore);
    if(articoli.isEmpty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "L'autore non ha ancora pubblicato articoli", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    visualizzaArticoliInLista(articoli, ui->page5_listArticoli);
    ui->page5_PrezzoPiuAlto->setText(QString::number(prezzoPiuAlto));
}
//Fine metodo

//Sezione C - Visualizzare le keyword la cui somma degli articoli porta al guadagno più alto*
void paginaArticolo::clearPage6()
{
    ui->page6_Guadagno->clear();
    ui->page6_listKeywords->clear();
}

void paginaArticolo::on_buttonVisualizzaKeywordsArticoliGuadagnoMax_clicked()
{
    if(listArticoliVuota(ui->buttonVisualizzaKeywordsArticoliGuadagnoMax) == true)
        return;
    clearPage6();
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizzaKeywordsArticoliGuadagnoMax);
    disableRadioButton(ui->buttonVisualizzaKeywordsArticoliGuadagnoMax);

    QList<QString> keywords;
    float guadagnoMax = gestore->getKeywordsCostose(keywords);
    ui->page6_Guadagno->setText(QString::number(guadagnoMax));
    for (auto it = keywords.begin(); it != keywords.end(); it++)
        ui->page6_listKeywords->addItem(*it);
}

void paginaArticolo::on_page6_buttonIndietro_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Home);
    clearPage6();
}
//Fine metodo

//Sezione D - Visualizzare gli articoli di una rivista ordinati per prezzo
void paginaArticolo::clearPage7()
{
    ui->page7_listRiviste->clear();
    ui->page7_listArticoli->clear();
}

void paginaArticolo::on_buttonVisualizzaArticoliRivistaOrdinatiPerPrezzo_clicked()
{
    if(listArticoliVuota(ui->buttonVisualizzaArticoliRivistaOrdinatiPerPrezzo) == true)
        return;
    clearPage7();
    ui->stackedWidget->setCurrentWidget(ui->pageVisualizzaArticoliRivistaOrdinatiPerPrezzo);
    disableRadioButton(ui->buttonVisualizzaArticoliRivistaOrdinatiPerPrezzo);
    QList<Rivista> riviste = gestore->getRiviste();
    visualizzaRivisteInLista(riviste, ui->page7_listRiviste);
}

void paginaArticolo::on_page7_buttonIndietro_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Home);
    clearPage7();
}

void paginaArticolo::on_page7_buttonSeleziona_clicked()
{
    if(ui->page7_listRiviste->currentRow() == -1)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Devi prima selezionare una rivista", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    int idxRivista = ui->page7_listRiviste->currentRow();
    QList<Articolo> articoli;
    gestore->getArticoliRivistaOrdinatiPerPrezzo(articoli, idxRivista);
    if(articoli.isEmpty() == true)
    {
        QMessageBox errore(QMessageBox::Critical, "Error", "Non sono stati ancora pubblicati articoli per questa rivista", QMessageBox::Ok, this);
        errore.exec();
        return;
    }
    visualizzaArticoliInLista(articoli, ui->page7_listArticoli);
}
//Fine metodo

/* Sezione D - Visualizzare gli articoli relativi a un autore, ordinati per anno crescente, a parità di anno,
ordinati per prezzo decrescente e a parità di prezzo ordinati in ordine alfabetico per la prima keyword nella lista* */

//Fine metodo


