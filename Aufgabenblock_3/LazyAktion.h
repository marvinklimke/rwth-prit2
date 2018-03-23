/*** LAZYAKTION.H ***/

//#ifndef __LazyAktion_h
//#define __LazyAktion_h

#pragma once
#include <list>
using namespace std;

// Oberklasse LazyAktion
template <class T>
class LazyAktion
{
   public:
      LazyAktion( list<T>* ptListe )
                   : p_ptListe( ptListe ) {}
      virtual ~LazyAktion() {}
      virtual void vAusfuehren() = 0;
   protected:
      list<T>*	p_ptListe;	// Zeiger auf Liste der Objekte
};


// LazyPushFront
template <class T>
class LazyPushFront : public LazyAktion<T>
{
   public:
      LazyPushFront(const T& anObjekt, list<T>* ptListe)
                      : LazyAktion<T>(ptListe)
                      , p_tObjekt(anObjekt) {}
      virtual ~LazyPushFront() {}
      void vAusfuehren() { p_ptListe->push_front(p_tObjekt); }
   private:
      T	p_tObjekt;
};


// LazyPushBack
template <class T>
class LazyPushBack : public LazyAktion<T>
{
	public:
		LazyPushBack(const T& anObjekt, list<T>* ptListe)
						: LazyAktion<T>(ptListe)
						, p_tObjekt(anObjekt) {}
		virtual ~LazyPushBack() {}
		void vAusfuehren() { p_ptListe->push_back(p_tObjekt); }
	private:
		T p_tObjekt;
};


// LazyErase
template <class T>
class LazyErase : public LazyAktion<T>
{
   // typedef fuer iterator
   typedef typename list<T>::iterator iterator;
   typedef typename list<T>::const_iterator const_iterator;

   public:
      LazyErase(const iterator& itObjekt, list<T>* ptListe )
					: LazyAktion(ptListe)
					, p_itObjekt(itObjekt) {}
      virtual ~LazyErase() {}
	  void vAusfuehren() { p_ptListe->erase(p_itObjekt); }
   private:
      iterator	p_itObjekt;	// bei erase Iterator speichern
};


//#endif