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

#include "articolo.h"

Articolo::Articolo() {}

Articolo::Articolo(int _identificativo, QString _titolo, int _numeroPagine, float _prezzo, QList<Autore> _autori, QList<QString> _keywords, QList<Articolo> _articoliCorrelati)
{
    identificativo = _identificativo;
    titolo = _titolo;
    numeroPagine = _numeroPagine;
    prezzo = _prezzo;
    autori = _autori;
    keywords = _keywords;
    articoliCorrelati = _articoliCorrelati;
}

int Articolo::getIdentificativo() const { return identificativo; }

QString Articolo::getTitolo() const { return titolo; }

int Articolo::getNumeroPagine() const { return numeroPagine; }

float Articolo::getPrezzo() const { return prezzo; }

QList<QString> Articolo::getKeywords() const { return keywords; }

QList<Articolo> Articolo::getArticoliCorrelati() const { return articoliCorrelati; }

void Articolo::setIdentificativo(int _identificativo) { identificativo = _identificativo; }

void Articolo::setTitolo(QString _titolo) { titolo = _titolo; }

void Articolo::setNumeroPagine(int _numeroPagine) { numeroPagine = _numeroPagine; }

void Articolo::setPrezzo(float _prezzo) { prezzo = _prezzo; }

void Articolo::setKeywords(QList<QString> _keywords) { keywords = _keywords; }

bool Articolo::operator==(const Articolo& _articolo) const
{
    return titolo == _articolo.titolo && numeroPagine == _articolo.numeroPagine && autori == _articolo.autori && prezzo == _articolo.prezzo;
}
