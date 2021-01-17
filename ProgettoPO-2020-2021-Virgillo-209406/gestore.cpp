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

int Gestore::getCurrentIdentificativoAutore() const { return identificativoAutore; }

int Gestore::getCurrentIdentificativoArticolo() const { return identificativoArticolo; }

void Gestore::increaseIdentificativoAutore() { identificativoAutore++; }

void Gestore::increaseIdentificativoArticolo() { identificativoArticolo++; }

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

void Gestore::setAnnoArticolo(int idx, int anno)
{
    int i = 0;
    for(auto it = articoli.begin(); it != articoli.end(); it++)
    {
        if (i == idx)
            it->setAnno(anno);
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

QList<Articolo> Gestore::getArticoliDiUnAutore(int idxAutore) const
{
    QList<Articolo> articoliAutore;
    Autore autore = autori.at(idxAutore);
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
       QList<Autore> autoriArticolo = it->getAutori();
       for (int i = 0; i < autoriArticolo.size(); i++)
       {
           if (autoriArticolo.at(i).getIdentificativo() == autore.getIdentificativo())
           {
               articoliAutore.push_back(*it);
               break;
           }
       }
    }
    return articoliAutore;
}

QVector<QString> Gestore::getStrutture() const
{
    QVector<QString> strutture;
    for (auto it = autori.begin(); it != autori.end(); it++)
    {
        QVector<QString> struttureAutore = it->getAfferenze();
        for (int i = 0; i < struttureAutore.size(); i++)
            if(strutture.indexOf(struttureAutore[i]) == -1)
                strutture.push_back(struttureAutore[i]);
    }
    return strutture;
}

QList<Articolo> Gestore::getArticoliDiUnaStruttura(QString struttura) const
{
    QList<Articolo> articoliStruttura;
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
       QList<Autore> autoriStruttura = it->getAutori();
       for (auto it2 = autoriStruttura.begin(); it2 != autoriStruttura.end(); it2++)
       {
           QVector<QString> afferenze = it2->getAfferenze();
           if (afferenze.indexOf(struttura) != -1)
           {
               articoliStruttura.push_back(*it);
               break;
           }
       }
    }
    return articoliStruttura;
}

QList<Articolo> Gestore::getArticoliDiUnaRivista(int idxRivista) const
{
    QList<Articolo> articoliRivista;
    Rivista rivista = riviste.at(idxRivista);
    articoliRivista = rivista.getArticoliRivista();

    return articoliRivista;
}

float Gestore::getArticoliCostosiAutore(QList<Articolo>& articoliCostosiAutore, int idxAutore) const
{
    QList<Articolo> articoliAutore = getArticoliDiUnAutore(idxAutore);

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

float Gestore::sommaPrezziArticoliStessaKeyword(QString keyword) const
{
    float sommaPrezzi = 0;
    for (auto it = articoli.begin(); it != articoli.end(); it++)
        if(it->getKeywords().indexOf(keyword) != -1)
            sommaPrezzi += it->getPrezzo();
    return sommaPrezzi;
}

float Gestore::getKeywordsCostose(QVector<QString>& keywordsCostose) const
{
    //calcolo il massimo guadagno che si può ottenere sommando le keywords
    float guadagnoMax = 0.0;
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
        QVector<QString> keywords = it->getKeywords();
        for (int i = 0; i < keywords.size(); i++)
        {
            float sommaPrezzi = sommaPrezziArticoliStessaKeyword(keywords[i]);
            if(sommaPrezzi > guadagnoMax)
                guadagnoMax = sommaPrezzi;
        }
    }

    //avendo il guadagno max che si può ottenere sommando i costi degli articoli di una keyword, cerco le keywords che producono quel guadagno
    for (auto it = articoli.begin(); it != articoli.end(); it++)
    {
        QVector<QString> keywords = it->getKeywords();
        for (int i = 0; i < keywords.size(); i++)
        {
            float sommaPrezzi = sommaPrezziArticoliStessaKeyword(keywords[i]);
            if(sommaPrezzi == guadagnoMax)
                if(keywordsCostose.indexOf(keywords[i]) == -1)
                    keywordsCostose.push_back(keywords[i]);
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

QList<Articolo> Gestore::getArticoliRivistaOrdinatiPerPrezzo(int idxRivista) const
{
    QList<Articolo> articoliOrdinati;

    articoliOrdinati = riviste.at(idxRivista).getArticoliRivista();
    std::sort(articoliOrdinati.begin(), articoliOrdinati.end(), ordinaArticoliPerPrezzo);

    return articoliOrdinati;
}

bool ordinaArticoliD6(Articolo articolo1, Articolo articolo2) // funzione compara da passare al sort per l'ordinamento richiesto nel metodo D 6
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

QList<Articolo> Gestore::getArticoliAutoreOrdinatiD6(int idxAutore) const
{
     QList<Articolo> articoliOrdinati = getArticoliDiUnAutore(idxAutore);
     std::sort(articoliOrdinati.begin(), articoliOrdinati.end(), ordinaArticoliD6);

     return articoliOrdinati;
}

QVector<QString> Gestore::getKeywordsArticoliRivista(Rivista rivista) const
{
    QVector<QString> keywordsRivista;
    QList<Articolo> articoliRivistaSpecificata = rivista.getArticoliRivista();

    for(auto it = articoliRivistaSpecificata.begin(); it != articoliRivistaSpecificata.end(); it++)
    {
        QVector<QString> keywordsArticoloInRivista = it->getKeywords();
        for (int i = 0; i < keywordsArticoloInRivista.size(); i++)
            if(keywordsRivista.indexOf(keywordsArticoloInRivista[i]) == -1)
                keywordsRivista.push_back(keywordsArticoloInRivista[i]);
    }
    return keywordsRivista;
}

QList<Rivista> Gestore::getRivisteSpecialistiche() const
{
    QList<Rivista> rivisteSpecialistiche;

    for (int i = 0; i < riviste.size(); i++)
    {
        QVector<QString> keywordsRivista1 = getKeywordsArticoliRivista(riviste.at(i));
        for(int j = 0; j < riviste.size(); j++)
        {
            if (j == i)
                continue;

            QVector<QString> keywordsRivista2 = getKeywordsArticoliRivista(riviste.at(j));
            bool check = true;
            for (int k = 0; k < keywordsRivista1.size(); k++)
            {
                if(keywordsRivista2.indexOf(keywordsRivista1[k]) == -1)
                {
                    check = false;
                    break;
                }
            }
            if(check == true)
            {
                for (int k = 0; k < keywordsRivista2.size(); k++)
                {
                    if(keywordsRivista1.indexOf(keywordsRivista2[k]) == -1)
                    {
                        if(rivisteSpecialistiche.indexOf(riviste.at(i)) == -1)
                        {
                            rivisteSpecialistiche.push_back(riviste.at(i));
                            break;
                        }
                    }
                }
            }
         }
    }
    return rivisteSpecialistiche;
}

QVector<QString> Gestore::getKeywordsArticoliConferenza(int idxConferenza) const
{
    QVector<QString> keywordsConferenza;
    QList<Articolo> articoliConferenzaSpecificata = conferenze.at(idxConferenza).getArticoliConferenza();

    for(auto it = articoliConferenzaSpecificata.begin(); it != articoliConferenzaSpecificata.end(); it++)
    {
        QVector<QString> keywordsArticoloInConferenza = it->getKeywords();
        for (int i = 0; i < keywordsArticoloInConferenza.size(); i++)
            if(keywordsConferenza.indexOf(keywordsArticoloInConferenza[i]) == -1)
                keywordsConferenza.push_back(keywordsArticoloInConferenza[i]);
    }
    return keywordsConferenza;
}

QList<Conferenza> Gestore::getConferenzeSimili(int idx) const
{
    QList<Conferenza> conferenzeSimili;
    QVector<QString> keywordsConferenzaSpecificata = getKeywordsArticoliConferenza(idx);
    QVector<QString> keywordsTotali;

    for(int i = 0; i < conferenze.size(); i++)
    {
        if(i == idx)
            continue;
        float contaKeywordsUguali = 0;

        keywordsTotali = keywordsConferenzaSpecificata;
        QVector<QString> keywordsArticoliInConferenza = getKeywordsArticoliConferenza(i);
        for (int j = 0; j < keywordsArticoliInConferenza.size(); j++)
            if(keywordsTotali.indexOf(keywordsArticoliInConferenza[j]) == -1)
                keywordsTotali.push_back(keywordsArticoliInConferenza[j]);

        for(int j = 0; j < keywordsTotali.size(); j++)
            if(keywordsConferenzaSpecificata.indexOf(keywordsTotali[j]) != -1 && keywordsArticoliInConferenza.indexOf(keywordsTotali[j]) != -1)
                contaKeywordsUguali++;

        if(((contaKeywordsUguali / keywordsTotali.size()) * 100) >= 80)
            conferenzeSimili.push_back(conferenze.at(i));

        keywordsTotali.clear();
    }
    return conferenzeSimili;
}

QList<Articolo> Gestore::getArticoliInfluenzati(int idxArticolo) const
{
    Articolo articolo = articoli.at(idxArticolo);
    QList<Articolo> articoliCorrelati;
    QList<Articolo> articoliInfluenzati;

    for (int i = 0; i < articoli.size(); i++)
    {
        if(i == idxArticolo)
            continue;

        articoliCorrelati = articoli.at(i).getArticoliCorrelati();

        for (auto it = articoliCorrelati.begin(); it != articoliCorrelati.end(); it++)
            if(articolo.getIdentificativo() == it->getIdentificativo() && articolo.getAnno() < articoli.at(i).getAnno())
                if(articoliInfluenzati.indexOf(articoli.at(i)) == -1)
                    articoliInfluenzati.push_back(articoli.at(i));

        articoliCorrelati.clear();
    }

    articoliCorrelati.clear();

    for(int i = 0; i < articoliInfluenzati.size(); i++)
    {
        for (auto it = articoli.begin(); it != articoli.end(); it++)
        {
            if(articoliInfluenzati.at(i).getIdentificativo() == it->getIdentificativo())
                continue;

            articoliCorrelati = it->getArticoliCorrelati();
            for (auto it2 = articoliCorrelati.begin(); it2 != articoliCorrelati.end(); it2++)
                if(articoliInfluenzati.at(i).getIdentificativo() == it2->getIdentificativo() && articoliInfluenzati.at(i).getAnno() < it->getAnno())
                    if(articoliInfluenzati.indexOf(*it) == -1)
                        articoliInfluenzati.push_back(*it);

            articoliCorrelati.clear();
        }
    }
    return articoliInfluenzati;
}
