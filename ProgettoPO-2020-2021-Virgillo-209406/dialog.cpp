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
        visualizzaArticolo();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::visualizzaAutore()
{
    QPixmap pix(":/img/Resources/Autore.png");
    int w = ui->Autore_labelLogo->width();
    int h = ui->Autore_labelLogo->height();
    ui->Autore_labelLogo->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    ui->stackedWidget->setCurrentWidget(ui->detailsAutore);
    Autore autore = gestore->getAutori().at(idx);
    ui->Autore_Identificativo->setText(QString::number(autore.getIdentificativo()));
    ui->Autore_Nome->setText(autore.getNome());
    ui->Autore_Cognome->setText(autore.getCognome());

    QVector<QString> afferenze = autore.getAfferenze();
    for (int i = 0; i < afferenze.size(); i++)
        ui->Autore_listAfferenze->addItem(afferenze[i]);
}

void Dialog::visualizzaConferenza()
{
    QPixmap pix(":/img/Resources/Conferenza.png");
    int w = ui->Conferenza_labelLogo->width();
    int h = ui->Conferenza_labelLogo->height();
    ui->Conferenza_labelLogo->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    ui->stackedWidget->setCurrentWidget(ui->detailsConferenza);
    Conferenza conferenza = gestore->getConferenze().at(idx);
    ui->Conferenza_Nome->setText(conferenza.getNome());
    ui->Conferenza_Acronimo->setText(conferenza.getAcronimo());
    ui->Conferenza_Luogo->setText(conferenza.getLuogo());

    QVector<QString> organizzatori = conferenza.getOrganizzatori();
    for (int i = 0; i < organizzatori.size(); i++)
        ui->Conferenza_listOrganizzatori->addItem(organizzatori[i]);

    ui->Conferenza_NumeroPartecipanti->setValue(conferenza.getNumeroPartecipanti());
    ui->Conferenza_Data->setText(conferenza.getData());
}

void Dialog::visualizzaRivista()
{
    QPixmap pix(":/img/Resources/Rivista.png");
    int w = ui->Rivista_labelLogo->width();
    int h = ui->Rivista_labelLogo->height();
    ui->Rivista_labelLogo->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    ui->stackedWidget->setCurrentWidget(ui->detailsRivista);
    Rivista rivista = gestore->getRiviste().at(idx);
    ui->Rivista_Nome->setText(rivista.getNome());
    ui->Rivista_Acronimo->setText(rivista.getAcronimo());
    ui->Rivista_Editore->setText(rivista.getEditore());
    ui->Rivista_Volume->setValue(rivista.getVolume());
    ui->Rivista_Data->setText(rivista.getData());
}

void Dialog::visualizzaArticolo()
{
    QPixmap pix(":/img/Resources/Articolo.png");
    int w = ui->Articolo_labelLogo->width();
    int h = ui->Articolo_labelLogo->height();
    ui->Articolo_labelLogo->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    ui->stackedWidget->setCurrentWidget(ui->detailsArticolo);
    Articolo articolo = gestore->getArticoli().at(idx);

    ui->Articolo_Identificativo->setText(QString::number(articolo.getIdentificativo()));
    ui->Articolo_Titolo->setText(articolo.getTitolo());
    QVector<QString> keywords = articolo.getKeywords();
    for (int i = 0; i < keywords.size(); i++)
        ui->Articolo_listKeywords->addItem(keywords[i]);
    ui->Articolo_NumeroPagine->setValue(articolo.getNumeroPagine());
    ui->Articolo_Prezzo->setValue(articolo.getPrezzo());

    if(articolo.getPubblicatoPer() == "Conferenza")
    {
        QList<Conferenza> conferenze = gestore->getConferenze();
        for (auto it = conferenze.begin(); it != conferenze.end(); it++)
        {
            QList<Articolo> articoliConferenza = it->getArticoliConferenza();
            for (auto it2 = articoliConferenza.begin(); it2 != articoliConferenza.end(); it2++)
            {
                if(articolo.getIdentificativo() == it2->getIdentificativo())
                {
                    QString string_conferenza =  it->getNome() + " - " + "Data " + it->getData();
                    ui->Articolo_PubblicatoPer->setText(string_conferenza);
                    break;
                }
            }
        }
    }
    else if(articolo.getPubblicatoPer() == "Rivista")
    {
        QList<Rivista> riviste = gestore->getRiviste();
        for (auto it = riviste.begin(); it != riviste.end(); it++)
        {
            QList<Articolo> articoliRivista = it->getArticoliRivista();
            for (auto it2 = articoliRivista.begin(); it2 != articoliRivista.end(); it2++)
            {
                if(articolo.getIdentificativo() == it2->getIdentificativo())
                {
                    QString string_rivista = it->getNome() + " - " + "Volume " + QString::number(it->getVolume());
                    ui->Articolo_PubblicatoPer->setText(string_rivista);
                    break;
                }
            }
        }
    }
    ui->AutoriArticoli->setItemData(0, 0, Qt::UserRole - 1);

}

void Dialog::on_AutoriArticoli_activated(const QString &arg1)
{
    if(ui->listAutoriArticoli->count() != 0)
        ui->listAutoriArticoli->clear();

    Articolo articolo = gestore->getArticoli().at(idx);
    if (arg1 == "Autori")
    {
        QList<Autore> autori = articolo.getAutori();

        for(auto it = autori.begin(); it != autori.end(); it++)
        {
            QString string_autore = "ID: " + QString::number(it->getIdentificativo()) + " " + it->getNome() + " " + it->getCognome();
            ui->listAutoriArticoli->addItem(string_autore);
        }
    }
    else if (arg1 == "Articoli correlati")
    {
        QList<Articolo> articoliCorrelati = articolo.getArticoliCorrelati();
        for (auto it = articoliCorrelati.begin(); it != articoliCorrelati.end(); it++)
        {
            QString string_articolo = "ID: " + QString::number(it->getIdentificativo()) + " " + it->getTitolo();
            ui->listAutoriArticoli->addItem(string_articolo);
        }
    }
}
