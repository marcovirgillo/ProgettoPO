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

void Gestore::setArticoloPubblicatoPer(Articolo articolo, QString pubblicatoPer)
{
    for (auto it = articoli.begin(); it != articoli.end(); it++)
        if(it->getIdentificativo() == articolo.getIdentificativo())
            it->setPubblicatoPer(pubblicatoPer);
}

void Gestore::setArticoloInConferenza(int idx, Articolo articolo)
{
    int i = 0;
    for(auto it = conferenze.begin(); it != conferenze.end(); it++)
    {
        if (i == idx)
            it->setArticoloInConferenza(articolo);
        i++;
    }
}

void Gestore::setArticoloInRivista(int idx, Articolo articolo)
{
    int i = 0;
    for(auto it = riviste.begin(); it != riviste.end(); it++)
    {
        if (i == idx)
            it->setArticoloIniRivista(articolo);
        i++;
    }
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

void Gestore::getArticoliDiUnAutore(QList<Articolo>& articoliAutore, int idAutore) const
{
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
       QList<Autore> autoriArticolo = it->getAutori();
       for (auto it2 = autoriArticolo.begin(); it2 != autoriArticolo.end(); it2++)
       {
           if (it2->getIdentificativo() == idAutore)
           {
               articoliAutore.push_back(*it);
               break;
           }
       }
    }
}

void Gestore::getArticoliDiUnaStruttura(QList<Articolo>& articoliStruttura, QString struttura) const
{
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
       QList<Autore> autoriStruttura = it->getAutori();
       for (auto it2 = autoriStruttura.begin(); it2 != autoriStruttura.end(); it2++)
       {
           QList<QString> afferenze = it2->getAfferenze();
           if (afferenze.indexOf(struttura) != -1)
           {
               articoliStruttura.push_back(*it);
               break;
           }
       }
    }
}

void Gestore::getArticoliDiUnaRivista(QList<Articolo>& articoliRivista, QString nomeRivista, int volume, QString data) const
{
    for (auto it = riviste.begin(); it != riviste.end(); it++)
    {
        if(it->getNome() == nomeRivista && it->getVolume() == volume && it->getData() == data)
        {
            articoliRivista = it->getArticoliRivista();
            break;
        }
    }
}

void Gestore::getArticoliCostosiAutore(QList<Articolo>& articoliCostosiAutore, int idAutore) const
{
    QList<Articolo> articoliAutore;
    getArticoliDiUnAutore(articoliAutore, idAutore);

    int prezzoMax = INT_MIN;
    for (auto it = articoliAutore.begin(); it != articoliAutore.end(); it++)
        if(it->getPrezzo() > prezzoMax)
            prezzoMax = it->getPrezzo();

    for (auto it = articoliAutore.begin(); it != articoliAutore.end(); it++)
        if(prezzoMax == it->getPrezzo())
            articoliCostosiAutore.push_back(*it);
}

float Gestore::getGuadagnoAnnualeConferenza(QList<Articolo>& articoliConferenza, QString nomeConferenza, QString luogo, QString data) const
{
    for (auto it = conferenze.begin(); it != conferenze.end(); it++)
    {
        if(it->getNome() == nomeConferenza && it->getLuogo() == luogo && it->getData() == data)
        {
            articoliConferenza = it->getArticoliConferenza();
            break;
        }
    }

    float guadagnoTotale = 0;
    for (auto it = articoliConferenza.begin(); it != articoliConferenza.end(); it++)
        guadagnoTotale += it->getPrezzo();

    return guadagnoTotale;
}

//data una keyword, restituisce la somma dei prezzi degli articoli con quella keyword
int Gestore::sommaPrezziArticoliStessaKeyword(QString keyword) const
{
    int sommaPrezzi = 0;
    for (auto it = articoli.begin(); it != articoli.end(); it++)
        if(it->getKeywords().indexOf(keyword) != -1)
            sommaPrezzi += it->getPrezzo();
    return sommaPrezzi;
}


int Gestore::getKeywordsCostose(QList<QString>& keywordsCostose) const
{
    //calcolo il massimo guadagno che si può ottenere sommando le keywords
    int guadagnoMax = 0;
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
        QList<QString> keywords = it->getKeywords();
        for (auto it2 = keywords.begin(); it2 != keywords.end(); it2++)
        {
            int sommaPrezzi = sommaPrezziArticoliStessaKeyword(*it2);
            if(sommaPrezzi > guadagnoMax)
                guadagnoMax = sommaPrezzi;
        }
    }

    //avendo il guadagno max che si può ottenere sommando i costi degli articoli di una keyword, cerco le keywords che producono quel guadagno
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
        QList<QString> keywords = it->getKeywords();
        for (auto it2 = keywords.begin(); it2 != keywords.end(); it2++)
        {
            int sommaPrezzi = sommaPrezziArticoliStessaKeyword(*it2);
            if(sommaPrezzi == guadagnoMax)
                if(keywordsCostose.indexOf(*it2) == -1)
                    keywordsCostose.push_back(*it2);
        }
    }
    return guadagnoMax;
}
