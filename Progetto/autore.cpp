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

#include "autore.h"

Autore::Autore() {}

Autore::Autore(int _identificativo, QString _nome, QString _cognome, QList<QString> _afferenze)
{
    identificativo = _identificativo;
    nome = _nome;
    cognome = _cognome;
    afferenze = _afferenze;
}

int Autore::getIdentificativo() const { return identificativo; }

QString Autore::getNome() const { return nome; }

QString Autore::getCognome() const { return cognome; }

QList<QString> Autore::getAfferenze() const { return afferenze; }

void Autore::setIdentificativo(int _identificativo) { identificativo = _identificativo; }

void Autore::setNome(QString _nome) { nome = _nome; }

void Autore::setCognome(QString _cognome) { cognome = _cognome; }

void Autore::setAfferenze(QList<QString> _afferenze) { afferenze = _afferenze; }

bool Autore::operator==(const Autore& _autore) const
{
    return nome == _autore.nome && cognome == _autore.cognome && afferenze == _autore.afferenze;
}
