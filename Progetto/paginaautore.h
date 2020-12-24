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

#ifndef PAGINAAUTORE_H
#define PAGINAAUTORE_H

#include "gestore.h"
#include "dialog.h"
#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class paginaAutore;
}

class paginaAutore : public QWidget
{
    Q_OBJECT

public:
    explicit paginaAutore(Gestore* _gestore, QWidget *parent = nullptr);
    ~paginaAutore();

    void clearCampiAutore();
    void showDialogAutore();

private slots:
    void on_buttonAggiungi_clicked();

    void on_listAutori_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::paginaAutore *ui;
    Gestore* gestore;
};

#endif // PAGINAAUTORE_H
