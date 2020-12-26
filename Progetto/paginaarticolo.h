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

    void clearCampiArticolo();
    void showDialogArticolo();

private slots:
    void on_buttonAggiungi_clicked();
    void on_buttonVisualizzaAutori_clicked();
    void on_buttonVisualizzaArticoli_clicked();
    void on_buttonConferenze_clicked();
    void on_buttonRiviste_clicked();
    void on_listArticoli_itemDoubleClicked(QListWidgetItem *item);

    void disableRadioButton(QRadioButton* radioButton);
    bool listArticoliVuota(QRadioButton* radioButton);
    void visualizzaArticoliInLista(QList<Articolo> articoli, QListWidget* listArticoli);

    void on_buttonVisualizzaArticoliAutore_clicked();
    void clearPage2();
    void on_page2_buttonIndietro_clicked();
    void on_page2_buttonCerca_clicked();
    void on_page2_buttonSeleziona_clicked();

    void on_buttonVisualizzaArticoliStruttura_clicked();
    void clearPage3();
    void on_page3_buttonIndietro_clicked();
    void on_page3_buttonCerca_clicked();

    void on_buttonVisualizzaArticoliRivista_clicked();
    void clearPage4();
    void on_page4_buttonIndietro_clicked();
    void on_page4_buttonCerca_clicked();

    void on_buttonVisualizzaArticoliCostosiAutore_clicked();
    void clearPage5();
    void on_page5_buttonIndietro_clicked();
    void on_page5_buttonCerca_clicked();
    void on_page5_buttonSeleziona_clicked();

    void on_buttonVisualizzaKeywordsArticoliGuadagnoMax_clicked();
    void clearPage6();
    void on_page6_buttonIndietro_clicked();

private:
    Ui::paginaArticolo *ui;
    Gestore* gestore;
    QVector<int> idListAutori;
};

#endif // PAGINAARTICOLO_H
