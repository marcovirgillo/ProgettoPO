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

#ifndef ARTICOLO_H
#define ARTICOLO_H

#include "autore.h"
#include <QString>
#include <QList>
#include <QVector>
#include <iostream>
using namespace std;

class Articolo
{
    private:
        int identificativo;
        QString titolo;
        int numeroPagine;
        float prezzo;
        QList<Autore> autori;
        QVector<QString> keywords;
        QList<Articolo> articoliCorrelati;
        QString pubblicatoPer;
        int anno;

    public:
        Articolo();
        Articolo(int _identificativo, QString _titolo, int _numeroPagine, float _prezzo, QList<Autore> _autori, QVector<QString> _keywords, QList<Articolo> _articoliCorrelati);

        int getIdentificativo() const;
        QString getTitolo() const;
        int getNumeroPagine() const;
        float getPrezzo() const;
        QList<Autore> getAutori() const;
        QVector<QString> getKeywords() const;
        QList<Articolo> getArticoliCorrelati() const;
        QString getPubblicatoPer() const;
        int getAnno() const;
        QString getPrimaKeyword() const;

        void setIdentificativo(int _identificativo);
        void setTitolo(QString _titolo);
        void setNumeroPagine(int _numeroPagine);
        void setPrezzo(float _prezzo);
        void setAutori(QList<Autore> _autori);
        void setArticoliCorrelati(QList<Articolo> _articoliCorrelati);
        void setKeywords(QVector<QString> _keywords);
        void setPubblicatoPer(QString _pubblicatoPer);
        void setAnno(int _anno);

        bool operator==(const Articolo& _articolo) const;
};

#endif // ARTICOLO_H
