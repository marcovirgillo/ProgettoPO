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
    for (auto it = articoli.begin(); it != articoli.end(); it++) //scorro gli articoli
        if(it->getIdentificativo() == articolo.getIdentificativo()) //cerco l'articolo presente tra i parametri nella lista di articoli
            it->setPubblicatoPer(pubblicatoPer); //quando lo trovo setto il suo campo pubblicatoPer con "Conferenza" o "Rivista", in base a ciò che viene passato
}

void Gestore::setArticoloInConferenza(int idx, Articolo articolo)
{
    int i = 0;
    for(auto it = conferenze.begin(); it != conferenze.end(); it++) //scorro le conferenze
    {
        if (i == idx) //cerco la conferenza, il cui indice viene passato tra i parametri
            it->setArticoloInConferenza(articolo); //aggiungo l'articolo alla lista di articoli di quella conferenza
        i++;
    }
}

void Gestore::setArticoloInRivista(int idx, Articolo articolo)
{
    int i = 0;
    for(auto it = riviste.begin(); it != riviste.end(); it++) //scorro le riviste
    {
        if (i == idx) //cerco la rivista, il cui indice viene passato tra i parametri
            it->setArticoloIniRivista(articolo); //aggiungo l'articolo alla lista di articoli di quella rivista
        i++;
    }
}

void Gestore::setAnnoArticolo(int idx, int anno)
{
    int i = 0;
    for(auto it = articoli.begin(); it != articoli.end(); it++) //scorro tutti gli articoli
    {
        if (i == idx) //cerco l'articolo, il cui indice viene passato tra i parametri
            it->setAnno(anno); //setto il suo anno con l'anno della conferenza o della rivista per cui è stato pubblicato
        i++;
    }
}

int Gestore::getAnnoConferenza(int idx) const
{
    QString data = conferenze.at(idx).getData(); //prendo la data della conferenza il cui indice è specificato tra i paramentri
    QList<QString> data_split = data.split("-"); //uso la funzione split di QList per separare anno-mese-giorno
    int annoConferenza = data_split.at(0).toInt(); //prendo l'anno della conferenza, che si trova sempre in posizione 0 della lista "data_split"
                                                   //(in posizione 1 e 2 ho rispettivamente mese e giorno della conferenza)
    return annoConferenza;
}

int Gestore::getAnnoRivista(int idx) const
{
    QString data = riviste.at(idx).getData(); //prendo la data della rivista il cui indice è specificato tra i paramentri
    QList<QString> data_split = data.split("-"); //uso la funzione split di QList per separare anno-mese-giorno
    int annoRivista = data_split.at(0).toInt(); //prendo l'anno della rivista, che si trova sempre in posizione 0 della lista "data_split"
                                                //(in posizione 1 e 2 ho rispettivamente mese e giorno della rivista)
    return annoRivista;
}

bool Gestore::aggiungiAutore(Autore autore)
{
    for (auto it = autori.begin(); it != autori.end(); it++) //scorro gli autori
    {
        Autore tmp = *it;
        if (tmp == autore) //se l'autore è gia presente, non viene aggiunto alla lista (operatore == di Autore implementato)
            return false;
    }
    autori.push_back(autore); //se l'autore non è stato ancora inserito, viene aggiunto alla lista di autori del gestore
    return true;
}

bool Gestore::aggiungiConferenza(Conferenza conferenza)
{
    for (auto it = conferenze.begin(); it != conferenze.end(); it++) //scorro le conferenze
    {
        Conferenza tmp = *it;
        if (tmp == conferenza) //se la conferenza è gia presente, non viene aggiunta alla lista (operatore == di Conferenza implementato)
            return false;
    }
    conferenze.push_back(conferenza); //se la conferenza non è stata ancora inserita, viene aggiunta alla lista di conferenze del gestore
    return true;
}

bool Gestore::aggiungiRivista(Rivista rivista)
{
    for (auto it = riviste.begin(); it != riviste.end(); it++) //scorro le riviste
    {
        Rivista tmp = *it;
        if (tmp == rivista) //se la rivista è gia presente, non viene aggiunta alla lista (operatore == di Rivista implementato)
            return false;
    }
        riviste.push_back(rivista); //se la rivista non è stata ancora inserita, viene aggiunta alla lista di riviste del gestore
        return true;
}

bool Gestore::aggiungiArticolo(Articolo articolo)
{
    for (auto it = articoli.begin(); it != articoli.end(); it++) //scorro gli articoli
    {
        Articolo tmp = *it;
        if (tmp == articolo) //se l'articolo è gia presente, non viene aggiunto alla lista (operatore == di Articolo implementato)
            return false;
    }
    articoli.push_back(articolo); //se l'articolo non è stato ancora inserito, viene aggiunto alla lista di articoli del gestore
    return true;
}

QList<Articolo> Gestore::getArticoliDiUnAutore(int idxAutore) const
{
    QList<Articolo> articoliAutore; //creo una lista in cui inserirò gli articoli dell'autore specificato
    Autore autore = autori.at(idxAutore); //prendo l'autore di cui ho l'indice è specificato tra i paramentri
    for (auto it = articoli.begin(); it != articoli.end(); it++) //scorro la lista di articoli presente in gestore
    {
       QList<Autore> autoriArticolo = it->getAutori(); //creo una lista locale di autori dell'articolo corrente
       for (int i = 0; i < autoriArticolo.size(); i++) //scorro questa lista di autori dell'articolo corrente
       {
           if (autoriArticolo.at(i).getIdentificativo() == autore.getIdentificativo()) //se tra gli autori dell'articolo è presente l'autore specificato
           {
               articoliAutore.push_back(*it); //aggiuno l'articolo corrente alla lista di articoli da ritornare all'utente
               break;
           }
       }
    }
    return articoliAutore;
}

QVector<QString> Gestore::getStrutture() const
{
    QVector<QString> strutture; //creo un vector in cui inserirò le strutture (afferenze) presenti nel sistema
    for (auto it = autori.begin(); it != autori.end(); it++) // scorro gli autori
    {
        QVector<QString> struttureAutore = it->getAfferenze(); //per ogni autore prendo le sue afferenze
        for (int i = 0; i < struttureAutore.size(); i++) //scorro le afferenze dell'autore corrente
            if(strutture.indexOf(struttureAutore[i]) == -1) //se una afferenza dell'autore corrente non è ancora presente nella lista di strutture
                strutture.push_back(struttureAutore[i]); //aggiungo l'afferenza alla lista di strutture da ritornare all'utente
    }
    return strutture;
}

QList<Articolo> Gestore::getArticoliDiUnaStruttura(QString struttura) const
{
    QList<Articolo> articoliStruttura; //creo una lista di articoli in cui inserirò gli articoli della struttura presente tra i parametri
    for (auto it = articoli.begin(); it != articoli.end(); it++) //scorro gli articoli
    {
       QList<Autore> autoriStruttura = it->getAutori(); //per ogni articolo prendo i suoi autori
       for (auto it2 = autoriStruttura.begin(); it2 != autoriStruttura.end(); it2++) //scorro gli autori dell'articolo corrente
       {
           QVector<QString> afferenze = it2->getAfferenze(); //prendo le afferenze dell'autore dell'articolo corrente
           if (afferenze.indexOf(struttura) != -1) //se l'afferenza specificata tra i parametri è presente nella lista di afferenze dell'autore dell'articolo corrente
           {
               articoliStruttura.push_back(*it); //aggiungo l'articolo alla lista degli articoli della struttura selezionata
               break;
           }
       }
    }
    return articoliStruttura;
}

QList<Articolo> Gestore::getArticoliDiUnaRivista(int idxRivista) const
{
    QList<Articolo> articoliRivista; //creo una lista di articoli in cui inserirò gli articoli della rivista il cui indice è specificato tra i paramentri
    Rivista rivista = riviste.at(idxRivista); //prendo la rivista il cui indice è specificato tra i parametri
    articoliRivista = rivista.getArticoliRivista(); //uso il metodo presente in rivista per farmi ritornare gli articoli pubblicati per quella rivista

    return articoliRivista;
}

float Gestore::getArticoliCostosiAutore(QList<Articolo>& articoliCostosiAutore, int idxAutore) const
{
    QList<Articolo> articoliAutore = getArticoliDiUnAutore(idxAutore); //creo una lista in cui inserisco subito gli articoli dell'autore specificato tramite un metodo

    float prezzoMax = INT_MIN;
    for (auto it = articoliAutore.begin(); it != articoliAutore.end(); it++) //scorro gli articoli dell'autore specificato
        if(it->getPrezzo() > prezzoMax) //se il prezzo dell'articolo dell'autore corrente è > max, aggiorno la variabile prezzoMax
            prezzoMax = it->getPrezzo();

    for (auto it = articoliAutore.begin(); it != articoliAutore.end(); it++) //scorro nuovamente gli articoli dell'autore specificato
        if(prezzoMax == it->getPrezzo()) //cerco tutti gli articoli di quell'autore con il prezzo max
            articoliCostosiAutore.push_back(*it); //agiungo questi articoli alla lista passata per riferimento tra i paramentri

    return prezzoMax;
}

float Gestore::getGuadagnoAnnualeConferenza(QList<Articolo>& articoliConferenza, int idxConferenza) const
{
    Conferenza conferenza = conferenze.at(idxConferenza); //prendo la conferenza il cui indice è specificato tra i parametri
    articoliConferenza = conferenza.getArticoliConferenza(); //prendo gli articoli di quella conferenza e li aggiungo alla lista di articoli passata tra i parametri
                                                             //che verrà ritornata per riferimento
    float guadagnoTotale = 0.0;
    for (auto it = articoliConferenza.begin(); it != articoliConferenza.end(); it++) //scorro la lista degli articoli di quella conferenza
        guadagnoTotale += it->getPrezzo(); //sommo il prezzo di ogni articolo presente in quella conferenza
    return guadagnoTotale;
}

float Gestore::sommaPrezziArticoliStessaKeyword(QString keyword) const
{
    float sommaPrezzi = 0;
    for (auto it = articoli.begin(); it != articoli.end(); it++) //scorro tutti gli articoli
        if(it->getKeywords().indexOf(keyword) != -1) //se tra le keyword dell'articolo corrente è presente la keyword specificata tra i paramentri
            sommaPrezzi += it->getPrezzo(); //sommo il prezzo di quegli articoli
    return sommaPrezzi;
}

float Gestore::getKeywordsCostose(QVector<QString>& keywordsCostose) const
{
    //calcolo il massimo guadagno che si può ottenere sommando le keywords:
    float guadagnoMax = 0.0;
    for (auto it = articoli.begin(); it != articoli.end(); it++) //scorro gli articoli
    {
        QVector<QString> keywords = it->getKeywords(); //prendo le keywords dell'articolo corrente
        for (int i = 0; i < keywords.size(); i++) //scorro le keywords dell'articolo corrente
        {
            float sommaPrezzi = sommaPrezziArticoliStessaKeyword(keywords[i]); //calcolo la somma dei prezzi degli articoli con la keyword corrente
            if(sommaPrezzi > guadagnoMax) //se il prezzo degli articoli con la keyword corrente è maggiore del prezzo massimo che si può ottenere
                guadagnoMax = sommaPrezzi; //aggiorno il prezzo massimo che si può ottenere
        }
    }

    //avendo il guadagno max che si può ottenere sommando i costi degli articoli di una keyword, cerco le keywords che producono quel guadagno:
    for (auto it = articoli.begin(); it != articoli.end(); it++) //scorro tutti gli articoli
    {
        QVector<QString> keywords = it->getKeywords(); //prendo le keywords dell'articolo corrente
        for (int i = 0; i < keywords.size(); i++) //scorro le keywords dell'articolo corrente
        {
            float sommaPrezzi = sommaPrezziArticoliStessaKeyword(keywords[i]); //calcolo la somma dei prezzi degli articoli con la keyword corrente
            if(sommaPrezzi == guadagnoMax) //se il prezzo degli articoli con la keyword corrente è uguale al prezzo massimo che si può ottenere
                if(keywordsCostose.indexOf(keywords[i]) == -1) //e se nella lista delle keywords da ritornare non è stata ancora inserita la keyword corrente
                    keywordsCostose.push_back(keywords[i]); //aggiungo la keyword corrente alla lista di keywords da ritornare
                                                            //cioè quelle che sommate danno il guadagno maggiore
        }
    }
    return guadagnoMax;
}

bool ordinaArticoliPerPrezzo(Articolo articolo1, Articolo articolo2) //funzione compara che specifica quando un articolo precede un altro
{
    if(articolo1.getPrezzo() < articolo2.getPrezzo())
        return true;
    return false;
}

QList<Articolo> Gestore::getArticoliRivistaOrdinatiPerPrezzo(int idxRivista) const
{
    QList<Articolo> articoliOrdinati; //creo una lista di articoli in cui inserirò gli articoli ordinati per prezzo

    articoliOrdinati = riviste.at(idxRivista).getArticoliRivista(); //prendo gli articoli della rivista il cui indice è specificato tra i parametri
    std::sort(articoliOrdinati.begin(), articoliOrdinati.end(), ordinaArticoliPerPrezzo); //chiamo il metodo sort di std su una QList per ordinare gli articoli
                                                                                          //della rivista per prezzo

    return articoliOrdinati;
}

bool ordinaArticoliD6(Articolo articolo1, Articolo articolo2) //funzione compara da passare al sort per l'ordinamento richiesto nel metodo D - 6
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
     QList<Articolo> articoliOrdinati = getArticoliDiUnAutore(idxAutore); //prendo gli articoli dell'autore il cui indice è specificato tra i parametri
     std::sort(articoliOrdinati.begin(), articoliOrdinati.end(), ordinaArticoliD6); //chiamo il metodo sort di std su una QList per ordinare gli articoli
                                                                                    //secondo il criterio richiesto dal metodo D - 6
     return articoliOrdinati;
}

QVector<QString> Gestore::getKeywordsArticoliRivista(Rivista rivista) const
{
    QVector<QString> keywordsRivista; //creo un vector in cui inserirò le keywords della rivista specificata tra i paramentri
    QList<Articolo> articoliRivistaSpecificata = rivista.getArticoliRivista(); //prendo gli articoli della rivista specificata tra i paramentri

    for(auto it = articoliRivistaSpecificata.begin(); it != articoliRivistaSpecificata.end(); it++) //scorro gli articoli della rivista specificata
    {
        QVector<QString> keywordsArticoloInRivista = it->getKeywords(); //per ogni articolo della rivista prendo le sue keywords
        for (int i = 0; i < keywordsArticoloInRivista.size(); i++) //scorro le keywords dell'articolo pubblicato per la rivista corrente
            if(keywordsRivista.indexOf(keywordsArticoloInRivista[i]) == -1) //se nel vector da ritornare non è stata ancora inserita la keyword corrente
                keywordsRivista.push_back(keywordsArticoloInRivista[i]); //inserisco la keyword corrente nel vector di keywords da ritornare
    }
    return keywordsRivista;
}

QList<Rivista> Gestore::getRivisteSpecialistiche() const
{
    QList<Rivista> rivisteSpecialistiche; //creo una lista in cui inserirò le riviste specialistiche

    for (int i = 0; i < riviste.size(); i++) //scorro le riviste
    {
        QVector<QString> keywordsRivista1 = getKeywordsArticoliRivista(riviste.at(i)); //prendo le keywords di una rivista (rivista 1)
        for(int j = 0; j < riviste.size(); j++) //scorro nuovamente le riviste
        {
            if (j == i) //se sto confrontando la stessa rivista in entrambi i for, salto l'iterazione perchè una rivista non è specialistica per se stessa
                continue;

            QVector<QString> keywordsRivista2 = getKeywordsArticoliRivista(riviste.at(j)); //prendo le keywords di un'altra rivista (rivista 2)
            bool check = true;
            for (int k = 0; k < keywordsRivista1.size(); k++) //scorro le keywords della rivista 1
            {
                if(keywordsRivista2.indexOf(keywordsRivista1[k]) == -1) //se almeno una keyword della rivista 1 non viene trovata tra le keywords della rivista 2
                                                                        //mi fermo e confronto la rivista 1 con le rimanenti riviste
                {
                    check = false;
                    break;
                }
            }
            if(check == true) //se tutte le keyword della rivista 1 sono presenti tra le keywords della rivista 2
            {
                for (int k = 0; k < keywordsRivista2.size(); k++) //scorro le keywords della rivista 2
                {
                    if(keywordsRivista1.indexOf(keywordsRivista2[k]) == -1) //controllo che ci sia almeno una keyword della rivista 2 non presente tra le
                                                                            //keywords della rivista 1
                    {
                        if(rivisteSpecialistiche.indexOf(riviste.at(i)) == -1) //se la precedente condizione è verificata e la rivista non è stata ancora inserita
                                                                               //tra le riviste specialistiche, la aggiungo
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
    QVector<QString> keywordsConferenza; //creo un vector in cui inserirò le keywords degli articoli pubblicati per una conferenza il cui indice è specificato nei paramentri
    QList<Articolo> articoliConferenzaSpecificata = conferenze.at(idxConferenza).getArticoliConferenza(); //prendo gli articoli della conferenza specificata

    for(auto it = articoliConferenzaSpecificata.begin(); it != articoliConferenzaSpecificata.end(); it++) //scorro gli articoli della conferenza specificata
    {
        QVector<QString> keywordsArticoloInConferenza = it->getKeywords(); //prendo le keywords dell'articolo corrente pubblicato per la conferenza specificata
        for (int i = 0; i < keywordsArticoloInConferenza.size(); i++) //scorro le keywords dell'articolo corrente
            if(keywordsConferenza.indexOf(keywordsArticoloInConferenza[i]) == -1) //se la keyword corrente non è stata inserita tra le keywords della conferenza
                keywordsConferenza.push_back(keywordsArticoloInConferenza[i]);   //la aggiungo
    }
    return keywordsConferenza;
}

QList<Conferenza> Gestore::getConferenzeSimili(int idx) const
{
    QList<Conferenza> conferenzeSimili; //creo una lista di conferenze in cui inserirò le conferenze simili
    QVector<QString> keywordsConferenzaSpecificata = getKeywordsArticoliConferenza(idx); //prendo le keywords della conferenza il cui indice è tra i parametri (conferenza 1)
    QVector<QString> keywordsTotali; //creo un vector che conterrà le keywords della conferenza 1 e della conferenza 2 senza duplicati

    for(int i = 0; i < conferenze.size(); i++) //scorro le conferenze
    {
        if(i == idx) //se la conferenza 1 (corrente) è quella il cui indice è presente tra i parametri salto l'iterazione (una conferenza non è simile con se stessa)
            continue;
        float contaKeywordsUguali = 0;

        keywordsTotali = keywordsConferenzaSpecificata; //aggiungo al vector delle keywords complessive, quelle della conferenza 1 (già pulite dai duplicati)
        QVector<QString> keywordsArticoliInConferenza = getKeywordsArticoliConferenza(i); //prendo le keywords di conferenza 2 cioè di un'altra conferenza
                                                                                           //diversa da quella specificata (già pulite dai duplicati)

        for (int j = 0; j < keywordsArticoliInConferenza.size(); j++) //scorro le keywords della conferenza 2
            if(keywordsTotali.indexOf(keywordsArticoliInConferenza[j]) == -1) //se la keyword corrente della conferenza 2 non è presente tra le keyword complessive
                keywordsTotali.push_back(keywordsArticoliInConferenza[j]);    //aggiungo la keyword al vector di keywords totali

        //avendo le keywords di entrambe le conferenze senza duplicati:
        for(int j = 0; j < keywordsTotali.size(); j++) //scorro le keywords totali
            if(keywordsConferenzaSpecificata.indexOf(keywordsTotali[j]) != -1 && keywordsArticoliInConferenza.indexOf(keywordsTotali[j]) != -1)
                contaKeywordsUguali++; //se tra le keywords della conferenza 1 e tra le keywords della conferenza 2 è presente una stessa keyword aumento il contatore

        if(((contaKeywordsUguali / keywordsTotali.size()) * 100) >= 80) //se le keywords uguali sono l'80% delle keywords totali, aggiungo la conferenza 1 tra le simili
            conferenzeSimili.push_back(conferenze.at(i));

        keywordsTotali.clear();
    }
    return conferenzeSimili;
}

QList<Articolo> Gestore::getArticoliInfluenzati(int idxArticolo) const
{
    Articolo articolo = articoli.at(idxArticolo); //prendo l'articolo il cui indice è presente tra i paramentri
    QList<Articolo> articoliCorrelati; //creo una lista che conterrà gli articoli correlati di un determinato articolo
    QList<Articolo> articoliInfluenzati; //creo una lista in cui inserirò gli articoli influenzati dall'articolo il cui indice è presente tra i parametri

    for (int i = 0; i < articoli.size(); i++) //scorro gli articoli
    {
        if(i == idxArticolo) //se l'indice dell'articolo è uguale a quello presente tra i parametri salto l'iterazione (un articolo non influenza se stesso)
            continue;

        articoliCorrelati = articoli.at(i).getArticoliCorrelati(); //prendo gli articoli correlati dell'articolo corrente

        for (auto it = articoliCorrelati.begin(); it != articoliCorrelati.end(); it++) //scorro gli articoli correlati dell'articolo corrente
        {
            //se la condizione affinchè un articolo influenzi direttamente un altro articolo è soddisfatta
            if(articolo.getIdentificativo() == it->getIdentificativo() && articolo.getAnno() < articoli.at(i).getAnno())
                if(articoliInfluenzati.indexOf(articoli.at(i)) == -1) //e se l'articolo non è gia stato inserito tra gli articoli influenzati
                    articoliInfluenzati.push_back(articoli.at(i));//aggiungo l'articolo alla lista di influenzati

        }
        articoliCorrelati.clear();
    }

    articoliCorrelati.clear();

    for(int i = 0; i < articoliInfluenzati.size(); i++) //scorro gli articoli influenzati dall'articolo il cui indice è presente tra i paramentri
    {
        for (auto it = articoli.begin(); it != articoli.end(); it++) //scorro la lista del gestore che contiene tutti gli articoli
        {
            if(articoliInfluenzati.at(i).getIdentificativo() == it->getIdentificativo()) //salto l'iterazione perchè un articolo non influenza se stesso
                continue;

            articoliCorrelati = it->getArticoliCorrelati(); //prendo i correlati dell'articolo articolo corrente presente nella lista di articoli del gestore
            for (auto it2 = articoliCorrelati.begin(); it2 != articoliCorrelati.end(); it2++) //scorro questi correlati
            {
                //se tra i correlati è presente l'articolo influenzato corrente
                if(articoliInfluenzati.at(i).getIdentificativo() == it2->getIdentificativo() && articoliInfluenzati.at(i).getAnno() < it->getAnno())
                    if(articoliInfluenzati.indexOf(*it) == -1) //e questo articolo non è già presente tra gli influenzati
                        articoliInfluenzati.push_back(*it); //aggiungo questo articolo alla lista di articoli influenzati dall'articolo il cui indice
                                                            //è specificato tra i parametri (influenza indiretta)
            }

            articoliCorrelati.clear();
        }
    }
    return articoliInfluenzati;
}
