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

int Gestore::getCurrentIdentificativoAutore() const
{
    return identificativoAutore;
}

int Gestore::getCurrentIdentificativoArticolo() const
{
    return identificativoArticolo;
}

void Gestore::increaseIdentificativoAutore()
{
    identificativoAutore++;
}

void Gestore::increaseIdentificativoArticolo()
{
    identificativoArticolo++;
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

int Gestore::getAnnoConferenza(int idx) const
{
    QString data = conferenze.at(idx).getData();
    QList<QString> data_split = data.split("-");
    int annoConferenza = data_split.at(0).toInt();
    return annoConferenza;

}

int Gestore::getAnnoRivista(int idx) const
{
    QString data = riviste.at(idx).getData();
    QList<QString> data_split = data.split("-");
    int annoRivista = data_split.at(0).toInt();
    return annoRivista;
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

void Gestore::getArticoliDiUnAutore(QList<Articolo>& articoliAutore, int idxAutore) const
{
    Autore autore = autori.at(idxAutore);
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
       QList<Autore> autoriArticolo = it->getAutori();
       for (auto it2 = autoriArticolo.begin(); it2 != autoriArticolo.end(); it2++)
       {
           if (it2->getIdentificativo() == autore.getIdentificativo())
           {
               articoliAutore.push_back(*it);
               break;
           }
       }
    }
}

void Gestore::getStrutture(QList<QString>& strutture) const
{
    for (auto it = autori.begin(); it != autori.end(); it++)
    {
        QList<QString> struttureAutore = it->getAfferenze();
        for (auto it2 = struttureAutore.begin(); it2 != struttureAutore.end(); it2++)
            if(strutture.indexOf(*it2) == -1)
                strutture.push_back(*it2);
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

void Gestore::getArticoliDiUnaRivista(QList<Articolo>& articoliRivista, int idxRivista) const
{
    Rivista rivista = riviste.at(idxRivista);
    articoliRivista = rivista.getArticoliRivista();
}

int Gestore::getArticoliCostosiAutore(QList<Articolo>& articoliCostosiAutore, int idxAutore) const
{
    QList<Articolo> articoliAutore;
    getArticoliDiUnAutore(articoliAutore, idxAutore);

    float prezzoMax = INT_MIN;
    for (auto it = articoliAutore.begin(); it != articoliAutore.end(); it++)
        if(it->getPrezzo() > prezzoMax)
            prezzoMax = it->getPrezzo();

    for (auto it = articoliAutore.begin(); it != articoliAutore.end(); it++)
        if(prezzoMax == it->getPrezzo())
            articoliCostosiAutore.push_back(*it);

    return prezzoMax;
}

float Gestore::getGuadagnoAnnualeConferenza(QList<Articolo>& articoliConferenza, int idxConferenza) const
{
    Conferenza conferenza = conferenze.at(idxConferenza);
    articoliConferenza = conferenza.getArticoliConferenza();
    float guadagnoTotale = 0.0;
    for (auto it = articoliConferenza.begin(); it != articoliConferenza.end(); it++)
        guadagnoTotale += it->getPrezzo();

    return guadagnoTotale;
}

//data una keyword, restituisce la somma dei prezzi degli articoli con quella keyword
float Gestore::sommaPrezziArticoliStessaKeyword(QString keyword) const
{
    float sommaPrezzi = 0;
    for (auto it = articoli.begin(); it != articoli.end(); it++)
        if(it->getKeywords().indexOf(keyword) != -1)
            sommaPrezzi += it->getPrezzo();
    return sommaPrezzi;
}


float Gestore::getKeywordsCostose(QList<QString>& keywordsCostose) const
{
    //calcolo il massimo guadagno che si può ottenere sommando le keywords
    float guadagnoMax = 0.0;
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
        QList<QString> keywords = it->getKeywords();
        for (auto it2 = keywords.begin(); it2 != keywords.end(); it2++)
        {
            float sommaPrezzi = sommaPrezziArticoliStessaKeyword(*it2);
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
            float sommaPrezzi = sommaPrezziArticoliStessaKeyword(*it2);
            if(sommaPrezzi == guadagnoMax)
                if(keywordsCostose.indexOf(*it2) == -1)
                    keywordsCostose.push_back(*it2);
        }
    }
    return guadagnoMax;
}

bool ordinaArticoliPerPrezzo(Articolo articolo1, Articolo articolo2)
{
    if(articolo1.getPrezzo() < articolo2.getPrezzo())
        return true;
    return false;
}

void Gestore::getArticoliRivistaOrdinatiPerPrezzo(QList<Articolo>& articoliOrdinati, int idxRivista) const
{
    articoliOrdinati = riviste.at(idxRivista).getArticoliRivista();
    std::sort(articoliOrdinati.begin(), articoliOrdinati.end(), ordinaArticoliPerPrezzo);
}

bool ordinaArticoliD6(Articolo articolo1, Articolo articolo2)
{
    if(articolo1.getAnno() < articolo2.getAnno())
        return true;
    if(articolo2.getAnno() == articolo1.getAnno())
    {
        if(articolo1.getPrezzo() > articolo2.getPrezzo())
            return true;
        if(articolo1.getPrezzo() == articolo2.getPrezzo())
            return articolo1.getPrimaKeyword() < articolo2.getPrimaKeyword();
    }
    return false;
}

void Gestore::getArticoliAutoreOrdinatiD6(QList<Articolo>& articoliOrdinati, int idxAutore) const
{
     getArticoliDiUnAutore(articoliOrdinati, idxAutore);
     std::sort(articoliOrdinati.begin(), articoliOrdinati.end(), ordinaArticoliD6);
}

//dato l'indice di una conferenza, restituisce le keywords relative agli articoli di quella conferenza
void Gestore::getKeywordsArticoloDaArticoliRivista(Rivista rivista, QList<QString>& keywordsRivista) const
{
    QList<Articolo> articoliRivistaSpecificata = rivista.getArticoliRivista();
    if(articoliRivistaSpecificata.size() == 0)
        return;

    for(auto it = articoliRivistaSpecificata.begin(); it != articoliRivistaSpecificata.end(); it++)
    {
        QList<QString> keywordsArticoloInRivista = it->getKeywords();
        for (auto it2 = keywordsArticoloInRivista.begin(); it2 != keywordsArticoloInRivista.end(); it2++)
            if(keywordsRivista.indexOf(*it2) == -1)
                keywordsRivista.push_back(*it2);
    }
}

void Gestore::getRivisteSpecialistiche(QList<Rivista>& rivisteSpecialistiche) const
{
    for (int i = 0; i < riviste.size(); i++)
    {
        QList<QString> keywordsRivista1;
        getKeywordsArticoloDaArticoliRivista(riviste.at(i), keywordsRivista1);
        for(int j = 0; j < riviste.size(); j++)
        {
            if(j != i)
            {
                QList<QString> keywordsRivista2;
                getKeywordsArticoloDaArticoliRivista(riviste.at(i), keywordsRivista2);
                bool check = true;
                for (auto it = keywordsRivista1.begin(); it != keywordsRivista1.end(); it++)
                {
                    if(keywordsRivista2.indexOf(*it) != -1)
                    {
                        check = false;
                        break;
                    }
                }
                if(check == true)
                {
                    for (auto it = keywordsRivista2.begin(); it != keywordsRivista2.end(); it++)
                    {
                        if(keywordsRivista1.indexOf(*it) == -1)
                        {
                            rivisteSpecialistiche.push_back(riviste.at(i));
                            break;
                        }
                    }
                }
             }
        }
    }
}


//dato l'indice di una conferenza, restituisce le keywords relative agli articoli di quella conferenza
void Gestore::getKeywordsArticoloDaArticoliConferenza(int idxConferenza, QList<QString>& keywordsConferenza) const
{
    QList<Articolo> articoliConferenzaSpecificata = conferenze.at(idxConferenza).getArticoliConferenza();
    if(articoliConferenzaSpecificata.size() == 0)
        return;

    for(auto it = articoliConferenzaSpecificata.begin(); it != articoliConferenzaSpecificata.end(); it++)
    {
        QList<QString> keywordsArticoloInConferenza = it->getKeywords();
        for (auto it2 = keywordsArticoloInConferenza.begin(); it2 != keywordsArticoloInConferenza.end(); it2++)
            if(keywordsConferenza.indexOf(*it2) == -1)
                keywordsConferenza.push_back(*it2);
    }
}

void Gestore::getConferenzeSimili(QList<Conferenza>& conferenzeSimili, int idx) const
{
    QList<QString> keywordsConferenzaSpecificata;
    getKeywordsArticoloDaArticoliConferenza(idx, keywordsConferenzaSpecificata);
    if(keywordsConferenzaSpecificata.size() == 0)
        return;

    int percentuale = (keywordsConferenzaSpecificata.size() * 80) / 100;

    for(int i = 0; i < conferenze.size(); i++)
    {
        if(i == idx)
            continue;
         int contaKeywordsUguali = 0;
         QList<QString> keywordsArticoliInConferenza;
         getKeywordsArticoloDaArticoliConferenza(i, keywordsArticoliInConferenza);

         for (auto it = keywordsArticoliInConferenza.begin(); it != keywordsArticoliInConferenza.end(); it++)
             for (auto it2 = keywordsConferenzaSpecificata.begin(); it2 != keywordsConferenzaSpecificata.end(); it2++)
                 if(*it == *it2)
                     contaKeywordsUguali++;

         if(contaKeywordsUguali >= percentuale)
             conferenzeSimili.push_back(conferenze.at(i));

         keywordsArticoliInConferenza.clear();
    }
}
