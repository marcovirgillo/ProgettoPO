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

#ifndef PAGINARIVISTA_H
#define PAGINARIVISTA_H

#include "gestore.h"
#include "dialog.h"
#include <QWidget>
#include <QListWidgetItem>
#include <QRadioButton>

namespace Ui {
class paginaRivista;
}

class paginaRivista : public QWidget
{
    Q_OBJECT

public:
    explicit paginaRivista(Gestore* _gestore, QWidget *parent = nullptr);
    ~paginaRivista();

    void clearCampiRivista();

    void showDialogRivista();



private slots:
    void on_buttonAggiungi_clicked();
    void on_listRiviste_itemDoubleClicked(QListWidgetItem *item);
    void on_buttonLeggi_clicked();

    void disableRadioButton(QRadioButton* radioButton);
    bool listArticoliVuota(QRadioButton* radioButton);
    void visualizzaRivisteInLista(QList<Rivista> riviste, QListWidget* listRiviste);

    void on_buttonVisualizzaRivisteSpecialistiche_clicked();

    void on_page2_buttonIndietro_clicked();

private:
    Ui::paginaRivista *ui;
    Gestore* gestore;
};

#endif // PAGINARIVISTA_H
