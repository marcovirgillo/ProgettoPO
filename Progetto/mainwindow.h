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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paginaarticolo.h"
#include "paginaautore.h"
#include "paginaconferenza.h"
#include "paginarivista.h"
#include "gestore.h"

#include <QMainWindow>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonAutore_clicked();

    void on_buttonArticolo_clicked();

    void on_buttonConferenza_clicked();

    void on_buttonRivista_clicked();

    void on_buttonHome_clicked();

    void on_stackedWidget_currentChanged(int arg1);

private:
    Ui::MainWindow *ui;

    Gestore* gestore;

    paginaArticolo* pageArticolo;
    paginaAutore* pageAutore;
    paginaConferenza* pageConferenza;
    paginaRivista* pageRivista;
};
#endif // MAINWINDOW_H
