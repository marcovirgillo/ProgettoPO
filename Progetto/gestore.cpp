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

#include "gestore.h"
#include <QDebug>

Gestore::Gestore()
{
    identificativoArticolo = 0;
    identificativoAutore = 0;
}

QList<Autore> Gestore::getAutori() const { return autori; }

QList<Conferenza> Gestore::getConferenze() const { return conferenze; }

QList<Rivista> Gestore::getRiviste() const { return riviste; }

QList<Articolo> Gestore::getArticoli() const { return articoli; }

int Gestore::getIdentificativoAutore()
{
    return identificativoAutore++;
}

int Gestore::getIdentificativoArticolo()
{
    return identificativoArticolo++;
}

bool Gestore::aggiungiAutore(Autore autore)
{
    for (auto it = autori.begin(); it != autori.end(); it++)
    {
        Autore tmp = *it;
        if (tmp == autore)
            return false;
    }
    autori.push_back(autore);
    return true;
}

bool Gestore::aggiungiConferenza(Conferenza conferenza)
{
    for (auto it = conferenze.begin(); it != conferenze.end(); it++)
    {
        Conferenza tmp = *it;
        if (tmp == conferenza)
            return false;
    }
    conferenze.push_back(conferenza);
    return true;
}

bool Gestore::aggiungiRivista(Rivista rivista)
{
    for (auto it = riviste.begin(); it != riviste.end(); it++)
        {
            Rivista tmp = *it;
            if (tmp == rivista)
                return false;
        }
        riviste.push_back(rivista);
        return true;
}

bool Gestore::aggiungiArticolo(Articolo articolo)
{
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
        Articolo tmp = *it;
        if (tmp == articolo)
            return false;
    }
    articoli.push_back(articolo);
    return true;
}

void Gestore::getArticoliDiUnAutore(QList<Articolo>& articoliAutore, Autore autore) const
{
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
       QList<Autore> autori = it->getAutori();
       int idxAutore = autori.indexOf(autore);

       if (idxAutore != -1)
       {
           Articolo tmpArticolo = *it;
           int idxArticolo = articoliAutore.indexOf(tmpArticolo);
           if(idxArticolo == -1)
               articoliAutore.push_back(tmpArticolo);
       }
    }
}

void Gestore::getArticoliDiUnaStruttura(QList<Articolo>& articoliStruttura, QString struttura) const
{
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
       QList<Autore> autori = it->getAutori();
       for (auto it2 = autori.begin(); it2 != autori.end(); it2++)
       {
           QList<QString> afferenze = it2->getAfferenze();
           int idxArticolo = afferenze.indexOf(struttura);
           if (idxArticolo != -1)
           {
               articoliStruttura.push_back(*it);
               break;
           }
       }
    }
}

void Gestore::getArticoliDiUnarivista(QList<Articolo>& articoliRivista, QString rivista)
{

}
