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

#ifndef CONFERENZA_H
#define CONFERENZA_H

#include "articolo.h"
#include <QString>
#include <QList>

class Conferenza
{
    private:
        QString nome;
        QString acronimo;
        QString luogo;
        QString data;
        int numeroPartecipanti;
        QList<QString> organizzatori;
        QList<Articolo> articoliConferenza;

    public:
        Conferenza();
        Conferenza(QString _nome, QString _acronimo, QString _luogo, QString _data, int _numeroPartecipanti, QList<QString> _organizzatori);

        QString getNome() const;
        QString getAcronimo() const;
        QString getLuogo() const;
        QString getData() const;
        int getNumeroPartecipanti() const;
        QList<QString> getOrganizzatori() const;
        QList<Articolo> getArticoliConferenza() const;

        void setNome(QString _nome);
        void setAcronimo(QString _acronimo);
        void setLuogo(QString _luogo);
        void setData(QString _data);
        void setNumeroPartecipanti(int _numeroPartecipanti);
        void setOrganizzatori(QList<QString> _organizzatori);
        void setArticoloInConferenza(Articolo articolo);

        bool operator==(const Conferenza& _conferenza) const;
};

#endif // CONFERENZA_H
