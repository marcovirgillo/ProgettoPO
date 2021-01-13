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
#include <QVector>
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
        void increaseIdentificativoAutore(); //incrementa l'ID di un autore dopo l'inserimento
        void increaseIdentificativoArticolo(); //incrementa l'ID di un articolo dopo l'inserimento

        void setArticoloPubblicatoPer(Articolo articolo, QString pubblicatoPer);
        void setArticoloInConferenza(int idx, Articolo articolo);
        void setArticoloInRivista(int idx, Articolo articolo);
        void setAnnoArticolo(int idx, int anno);

        int getAnnoConferenza(int idx) const; //metodo che ritorna l'anno di una conferenza specificata
        int getAnnoRivista(int idx) const; //metodo che ritorna l'anno di una rivista specificata

        // Metodi per l'aggiunta dei dati:
        bool aggiungiAutore(Autore autore);
        bool aggiungiConferenza(Conferenza conferenza);
        bool aggiungiRivista(Rivista rivista);
        bool aggiungiArticolo(Articolo articolo);

        QList<Articolo> getArticoliDiUnAutore(int idxAutore) const; // Sezione B - 1
        QVector<QString> getStrutture() const; // metodo ausiliario che ritorna le strutture (afferenze) caricate
        QList<Articolo> getArticoliDiUnaStruttura(QString struttura) const; // Sezione B - 3
        QList<Articolo> getArticoliDiUnaRivista(int idxRivista) const; // Sezione B - 5
        float getArticoliCostosiAutore(QList<Articolo>& articoliAutore, int idxAutore) const; // Sezione C - 2
        float getGuadagnoAnnualeConferenza(QList<Articolo>& articoliConferenza, int idxConferenza) const; // Sezione C - 4
        float getKeywordsCostose(QVector<QString>& keywordsCostose) const; // Sezione C - 6 *
        float sommaPrezziArticoliStessaKeyword(QString keyword) const; // metodo ausiliario che data una keyword, restituisce la somma dei prezzi degli articoli con quella keyword
        QList<Articolo> getArticoliRivistaOrdinatiPerPrezzo(int idxRivista) const; // Sezione D - 4
        QList<Articolo> getArticoliAutoreOrdinatiD6(int idxAutore) const; // Sezione D - 6 *
        QVector<QString> getKeywordsArticoliRivista(Rivista rivista) const; // metodo ausiliario che ritorna le keywords degli articoli di una rivista specificata
        QList<Rivista> getRivisteSpecialistiche() const; // Sezione E - 6 *
        QVector<QString> getKeywordsArticoliConferenza(int idxConferenza) const; // metodo ausiliario che ritorna le keywords degli articoli di una conferenza specificata
        QList<Conferenza> getConferenzeSimili(int idx) const; // Sezione F - 5 **
        QList<Articolo> getArticoliInfluenzati(int idxArticolo) const;

};
#endif // GESTORE_H
