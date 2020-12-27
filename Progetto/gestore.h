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
#include <climits>

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

        int getCurrentIdentificativoAutore() const;
        int getCurrentIdentificativoArticolo() const;
        void increaseIdentificativoAutore();
        void increaseIdentificativoArticolo();

        void setArticoloPubblicatoPer(Articolo articolo, QString pubblicatoPer);
        void setArticoloInConferenza(int idx, Articolo articolo);
        void setArticoloInRivista(int idx, Articolo articolo);

        int getAnnoConferenza(int idx) const;
        int getAnnoRivista(int idx) const;

        bool aggiungiAutore(Autore autore);
        bool aggiungiConferenza(Conferenza conferenza);
        bool aggiungiRivista(Rivista rivista);
        bool aggiungiArticolo(Articolo articolo);

        void getArticoliDiUnAutore(QList<Articolo>& articoliAutore, int idxAutore) const;
        void getStrutture(QList<QString>& strutture) const;
        void getArticoliDiUnaStruttura(QList<Articolo>& articoliStruttura, QString struttura) const;
        void getArticoliDiUnaRivista(QList<Articolo>& articoliRivista, int idxRivista) const;
        int getArticoliCostosiAutore(QList<Articolo>& articoliAutore, int idxAutore) const;
        float getGuadagnoAnnualeConferenza(QList<Articolo>& articoliConferenza, int idxConferenza) const;
        float getKeywordsCostose(QList<QString>& keywordsCostose) const;
        float sommaPrezziArticoliStessaKeyword(QString keyword) const;
        void getArticoliRivistaOrdinatiPerPrezzo(QList<Articolo>& articoliOrdinati, int idxRivista) const;
        void getArticoliAutoreOrdinatiD6(QList<Articolo>& articoliOrdinati, int idxAutore) const;
        void getRivisteSpecialistiche(QList<Rivista>& rivisteSpecialistiche) const;

};

#endif // GESTORE_H
