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

#ifndef PAGINACONFERENZA_H
#define PAGINACONFERENZA_H

#include "gestore.h"
#include "dialog.h"
#include <QWidget>
#include <QListWidgetItem>
#include <QRadioButton>

namespace Ui {
class paginaConferenza;
}

class paginaConferenza : public QWidget
{
    Q_OBJECT

public:
    explicit paginaConferenza(Gestore* _gestore, QWidget *parent = nullptr);
    ~paginaConferenza();

    void showDialogConferenza();
    void clearCampiConferenza();

private slots:
    void on_buttonAggiungi_clicked();
    void on_listConferenze_itemDoubleClicked(QListWidgetItem *item);

    void disableRadioButton(QRadioButton* radioButton);
    bool listArticoliVuota(QRadioButton* radioButton);
    void visualizzaArticoliInLista(QList<Articolo> articoli, QListWidget* listArticoli);

    void on_buttonVisualizzaGuadagnoAnnualeConferenza_clicked();
    void clearPage2();
    void on_page2_buttonIndietro_clicked();
    void on_page2_buttonSeleziona_clicked();

private:
    Ui::paginaConferenza *ui;
    Gestore* gestore;
};

#endif // PAGINACONFERENZA_H
