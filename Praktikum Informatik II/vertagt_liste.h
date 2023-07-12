#pragma once

#include "vertagt_aktion.h"
#include <list>

namespace vertagt
{
	template <class T>
	class VListe
	{
	private:
		std::list<T> p_objekte;
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;

		// Konstruktoren
		VListe() = default;
		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
			
		}

		void clear()
		{
			p_objekte.clear();
			//Definition von std::List::clear() in cpp-referenz: 
			//Removes all elements from the list container (which are destroyed), 
			//and leaving the container with a size of 0.
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin(); //begin() ist in std::list enthalten
		}
		const_iterator end() const
		{
			return p_objekte.end(); //end() ist in std::list enthalten
		}
		iterator begin()
		{
			return p_objekte.begin(); //begin() ist in std::list enthalten
		}
		iterator end()
		{
			return p_objekte.end(); //end() ist in std::list enthalten
		}
		bool empty() const
		{
			return p_objekte.empty(); //empty() ist in std::list enthalten
			//Definition von std::List::empty() in cpp-referenz:
			//Returns whether the list container is empty (i.e. whether its size is 0).
		}

		
		int size() const
		{
			return p_objekte.size();
		}
		

		// Schreibfunktionen
		void push_back(T obj)
		{
			// Aktionselement für PushBack auf Liste erzeugen
			p_aktionen.push_back(std::make_unique<VPushBack<T>>(p_objekte, std::move(obj)));
		}

		void push_front(T obj)
		{
			// Aktionselement für PushFront auf Liste erzeugen
			p_aktionen.push_front(std::make_unique<VPushFront<T>>(p_objekte, std::move(obj)));
		}

		void erase(iterator it)
		{
			// Aktionselement für Erase auf Liste erzeugen (hier Iterator statt Objekt !)
			p_aktionen.push_back(std::make_unique<VErase<T>>(p_objekte, it));
			//push_back (oder auch push_front) und nicht erase, da wir ein Element ERZEUGEN moechten, 
			//das loeschen erfolgt dann innerhalb der inneren Implemetierung bei der Ausfuehrung von vAktualisieren()
		}

		// Aenderungen auf Objektliste übertragen
		void vAktualisieren()
		{
			while (!p_aktionen.empty()) //ergibt am Anfang immer true: da p_aktionen mit Aktionselementen befuellt ist,
										// bis alle Aktionen ausgefuehrt worden sind.
			{
				// Aktionszeiger auf 1. Element bestimmen
				std::unique_ptr <VAktion<T>> p_aktion = std::move(p_aktionen.front());
				//p_aktionen.front() = erstes element in p_aktionen: (VPushFront, VPushBack oder VErase)

				// Aktion ausführen
				p_aktion->vAusfuehren(); //die Aktion in der Liste (Pushback, pushfront oder erase) wird ausgefuehrt.
				p_aktionen.pop_front(); //element (jetzt vorne) wird nach der Ausfeuhrung geloescht, 
									  //damit das naechste Element das 1. wird.
				p_aktion.reset();
			}

			// Liste leeren
			p_aktionen.clear();
		}
	};
} // namespace vertagt
