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

#include "conferenza.h"

Conferenza::Conferenza() {}

Conferenza::Conferenza(QString _nome, QString _acronimo, QString _luogo, QString _data, int _numeroPartecipanti, QVector<QString> _organizzatori)
{
    nome = _nome;
    acronimo = _acronimo;
    luogo = _luogo;
    data = _data;
    numeroPartecipanti = _numeroPartecipanti;
    organizzatori = _organizzatori;
}

QString Conferenza::getNome() const { return nome; }

QString Conferenza::getAcronimo() const { return acronimo; }

QString Conferenza::getLuogo() const { return luogo; }

QString Conferenza::getData() const{ return data; }

int Conferenza::getNumeroPartecipanti() const { return numeroPartecipanti; }

QVector<QString> Conferenza::getOrganizzatori() const { return organizzatori; }

QList<Articolo> Conferenza::getArticoliConferenza() const { return articoliConferenza; }

void Conferenza::setNome(QString _nome) { nome = _nome; }

void Conferenza::setAcronimo(QString _acronimo) { acronimo = _acronimo; }

void Conferenza::setLuogo(QString _luogo) { luogo = _luogo; }

void Conferenza::setData(QString _data) { data = _data; }

void Conferenza::setNumeroPartecipanti(int _numeroPartecipanti) { numeroPartecipanti = _numeroPartecipanti; }

void Conferenza::setOrganizzatori(QVector<QString> _organizzatori) { organizzatori = _organizzatori; }

void Conferenza::setArticoloInConferenza(Articolo articolo) { articoliConferenza.push_back(articolo); }

bool Conferenza::operator==(const Conferenza& _conferenza) const
{
    return nome == _conferenza.nome && luogo == _conferenza.luogo && data == _conferenza.data;
}
