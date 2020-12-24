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

#ifndef GESTORE_H
#define GESTORE_H

#include "autore.h"
#include "conferenza.h"
#include "rivista.h"
#include "articolo.h"
#include <QString>
#include <QList>

class Gestore
{
    private:
        QList<Autore> autori;
        QList<Conferenza> conferenze;
        QList<Rivista> riviste;
        QList<Articolo> articoli;
        int identificativoAutore;
        int identificativoArticolo;

    public:
        Gestore();

        QList<Autore> getAutori() const;
        QList<Conferenza> getConferenze() const;
        QList<Rivista> getRiviste() const;
        QList<Articolo> getArticoli() const;

        int getIdentificativoAutore();
        int getIdentificativoArticolo();

        void setArticoloPubblicatoPer(Articolo articolo, QString pubblicatoPer);

        void setArticoloInConferenza(int idx, Articolo articolo);
        void setArticoloInRivista(int idx, Articolo articolo);

        bool aggiungiAutore(Autore autore);
        bool aggiungiConferenza(Conferenza conferenza);
        bool aggiungiRivista(Rivista rivista);
        bool aggiungiArticolo(Articolo articolo);

        void getArticoliDiUnAutore(QList<Articolo>& articoliAutore, Autore autore) const;
        void getArticoliDiUnaStruttura(QList<Articolo>& articoliStruttura, QString struttura) const;
        void getArticoliDiUnaRivista(QList<Articolo>& articoliRivista, QString nomeRivista, int volume, QString data);
};

#endif // GESTORE_H
