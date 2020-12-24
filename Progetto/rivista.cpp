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

#include "rivista.h"

Rivista::Rivista() {}

Rivista::Rivista(QString _nome, QString _acronimo, QString _editore, QString _data, int _volume)
{
    nome = _nome;
    acronimo = _acronimo;
    editore = _editore;
    data = _data;
    volume = _volume;
}

QString Rivista::getNome() const { return nome; }

QString Rivista::getAcronimo() const { return acronimo; }

QString Rivista::getEditore() const { return editore; }

QString Rivista::getData() const { return data; }

int Rivista::getVolume() const { return volume; }

QList<Articolo> Rivista::getArticoliRivista() const { return articoliRivista; }

void Rivista::setNome(QString _nome) { nome = _nome; }

void Rivista::setAcronimo(QString _acronimo) { acronimo = _acronimo; }

void Rivista::setEditore(QString _editore) { editore = _editore; }

void Rivista::setData(QString _data) { data = _data; }

void Rivista::setVolume(int _volume) { volume = _volume; }

void Rivista::setArticoloIniRivista(Articolo articolo) { articoliRivista.push_back(articolo); }

bool Rivista::operator==(const Rivista& _rivista) const
{
    return nome == _rivista.nome && data == _rivista.data && volume == _rivista.volume;
}
