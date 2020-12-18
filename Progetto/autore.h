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

#ifndef AUTORE_H
#define AUTORE_H

#include <QString>
#include <QList>

class Autore
{
    private:
        int identificativo;
        QString nome;
        QString cognome;
        QList<QString> afferenze;

    public:
        Autore();
        Autore(int _identificativo, QString _nome, QString _cognome, QList<QString> _afferenze);

        int getIdentificativo() const;
        QString getNome() const;
        QString getCongome() const;
        QList<QString> getAfferenze() const;

        void setIdentificativo(int _identificativo);
        void setNome(QString _nome);
        void setCognome(QString _cognome);
        void setAfferenze(QList<QString> _afferenze);

        bool operator==(const Autore& _autore) const;
};

#endif // AUTORE_H
