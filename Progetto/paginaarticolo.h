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

    void on_listArticoli_itemDoubleClicked(QListWidgetItem *item);

    void on_buttonConferenze_clicked();

    void on_buttonRiviste_clicked();

private:
    Ui::paginaArticolo *ui;

    Gestore* gestore;
};

#endif // PAGINAARTICOLO_H
