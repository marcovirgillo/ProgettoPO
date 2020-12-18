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

#ifndef RIVISTA_H
#define RIVISTA_H

#include <QString>
#include <QList>

class Rivista
{
    private:
        QString nome;
        QString acronimo;
        QString editore;
        QString data;
        int volume;
    public:
        Rivista();
        Rivista(QString _nome, QString _acronimo, QString _editore, QString _data, int _volume);

        QString getNome() const;
        QString getAcronimo() const;
        QString getEditore() const;
        QString getData() const;
        int getVolume() const;

        void setNome(QString _nome);
        void setAcronimo(QString _acronimo);
        void setEditore(QString _editore);
        void setData(QString _data);
        void setVolume(int _volume);

        bool operator==(const Rivista& _rivista) const;
};

#endif // RIVISTA_H
