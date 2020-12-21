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

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "gestore.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Gestore* _gestore, QString TipoClasse, int _idx, QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void on_AutoriArticoli_activated(const QString &arg1);

    void visualizzaAutore();
    void visualizzaConferenza();
    void visualizzaRivista();
    void VisualizzaArticolo();

private:
    Ui::Dialog *ui;
    Gestore* gestore;
    int idx;
    Articolo _articolo;
};

#endif // DIALOG_H
