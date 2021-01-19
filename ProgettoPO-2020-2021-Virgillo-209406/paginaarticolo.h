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

#ifndef PAGINAARTICOLO_H
#define PAGINAARTICOLO_H

#include "gestore.h"
#include "dialog.h"
#include <QWidget>
#include <QListWidgetItem>
#include <QRadioButton>

namespace Ui {
class paginaArticolo;
}

class paginaArticolo : public QWidget
{
    Q_OBJECT

public:
    explicit paginaArticolo(Gestore* _gestore, QWidget *parent = nullptr);
    ~paginaArticolo();

    void clearCampiArticolo(); //pulisce i campi di paginaArticolo
    void showDialogArticolo(); //mostra i dettagli di un articolo facendo doppio click su di esso nella QListWidget contenente tutti gli articoli

private slots:
    void on_buttonAggiungi_clicked();
    void on_buttonVisualizzaAutori_clicked();
    void on_buttonVisualizzaArticoli_clicked();
    void on_buttonConferenze_clicked();
    void on_buttonRiviste_clicked();
    void on_listArticoli_itemDoubleClicked(QListWidgetItem *item);
    void on_buttonLeggi_clicked();

    void disableRadioButton(QRadioButton* radioButton); //consente di disattivare un Radio Button senza che rimanga selezionato
    bool listArticoliVuota(QRadioButton* radioButton); //verifica se la lista di Articoli è vuota e richiama la funzione disableRadioButton
    void visualizzaAutoriInLista(QList<Autore> articoli, QListWidget* listAutori); //mostra una lista specificata di autori in una QListWidget
    void visualizzaArticoliInLista(QList<Articolo> articoli, QListWidget* listArticoli); //mostra una lista specificata di articoli in una QListWidget
    void visualizzaRivisteInLista(QList<Rivista> riviste, QListWidget* listRiviste); //mostra una lista specificata di riviste in una QListWidget

    void on_buttonVisualizzaArticoliAutore_clicked();
    void clearPage2();
    void on_page2_buttonIndietro_clicked();
    void on_page2_buttonSeleziona_clicked();

    void on_buttonVisualizzaArticoliStruttura_clicked();
    void clearPage3();
    void on_page3_buttonIndietro_clicked();
    void on_page3_buttonSeleziona_clicked();

    void on_buttonVisualizzaArticoliRivista_clicked();
    void clearPage4();
    void on_page4_buttonIndietro_clicked();
    void on_page4_buttonSeleziona_clicked();

    void on_buttonVisualizzaArticoliCostosiAutore_clicked();
    void clearPage5();
    void on_page5_buttonIndietro_clicked();
    void on_page5_buttonSeleziona_clicked();

    void on_buttonVisualizzaKeywordsArticoliGuadagnoMax_clicked();
    void clearPage6();
    void on_page6_buttonIndietro_clicked();

    void on_buttonVisualizzaArticoliRivistaOrdinatiPerPrezzo_clicked();
    void clearPage7();
    void on_page7_buttonIndietro_clicked();
    void on_page7_buttonSeleziona_clicked();

    void on_buttonVisualizzaArticoliAutoreOrdinatiD6_clicked();
    void clearPage8();
    void on_page8_buttonIndietro_clicked();
    void on_page8_buttonSeleziona_clicked();

    void on_buttonVisualizzaArticoliInfluenzati_clicked();
    void clearPage9();
    void on_page9_buttonIndietro_clicked();
    void on_page9_buttonSeleziona_clicked();

private:
    Ui::paginaArticolo *ui;
    Gestore* gestore;
};

#endif // PAGINAARTICOLO_H
