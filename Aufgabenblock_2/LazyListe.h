/*** LAZYLISTE.H ***/

//#ifndef __LazyListe_h
//#define __LazyListe_h

#pragma once
#include <list>
#include "LazyAktion.h"

template <class T>
class LazyListe
{
   public:
      // typedef fuer iterator
      typedef typename list<T>::iterator iterator;
      typedef typename list<T>::const_iterator const_iterator;

      // Konstruktor / Destruktor
      LazyListe() { bChanged = false; }
      virtual ~LazyListe()
      {
         if (bChanged)
         {
            // ggf. noch anstehende Aktionen löschen
            do
            {
               delete *(p_ListeAktionen.begin());
               p_ListeAktionen.pop_front();
            }
            while (p_ListeAktionen.size() > 0);
         }
      }

      // Lesefunktionen
      const_iterator begin() const { return p_ListeObjekte.begin(); }
	  const_iterator end() const { return p_ListeObjekte.end(); }
      iterator begin() { return p_ListeObjekte.begin(); }
	  iterator end() { return p_ListeObjekte.end(); }
	  bool empty() const { return p_ListeObjekte.empty(); }

      // Schreibfunktionen
      void push_back( const T einObjekt )
      {
      p_ListeAktionen.push_back(new LazyPushBack<T>(einObjekt, &p_ListeObjekte));
      bChanged = true;
      return;
      }

      void push_front( const T einObjekt )
      {
      p_ListeAktionen.push_back(new LazyPushFront<T>(einObjekt, &p_ListeObjekte));
      bChanged = true;
      return;
      }

      void erase( iterator itObjekt )
      {
      p_ListeAktionen.push_back(new LazyErase<T>(itObjekt, &p_ListeObjekte));
      bChanged = true;
      return;
      }

      // Änderungen auf Objektliste übertragen
      void vAktualisieren()
      {
         list <LazyAktion<T>*>::const_iterator itL;

         if ( bChanged )
         {
	         // ausstehende Aktionen durchfuehren
	         for (itL = p_ListeAktionen.begin(); itL != p_ListeAktionen.end(); ++itL )
	         {
	             // Aktion ausführen
				 (*itL)->vAusfuehren();
                 // Action-Element löschen
				 delete *itL;
	         }
	         // Liste der Aktionen leeren
             p_ListeAktionen.clear();

	         bChanged = false;
         }
      }

   private:
      list<T>				p_ListeObjekte;
      list<LazyAktion<T>*>	p_ListeAktionen;
      bool					bChanged;
};

//#endif