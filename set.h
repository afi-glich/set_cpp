#ifndef SET_H
#define SET_H

#include <ostream>
#include <iostream>
#include <stdexcept>
#include <cstddef>

/**
 	@brief classe Set 

 	La classe implementa un Set di elementi T che non
 	contiene duplicati. 
 	Due dati vengono confrontati tramite il funtore 
 	Eql che ha come parametri due elementi a e b e 
 	ritorna TRUE se i due elementi sono uguali.
*/
template <typename T, typename Eql>
class Set {

	/**
		@brief struttura nodo

		Struttura dati interna utilizzata per creare
		il Set. 
	*/
	struct nodo {
		T value; ///< valore da memorizzare
		nodo *next; ///< puntatore al prossimo nodo del Set

		/**
			Costruttore di default

			@post next == nullptr
		*/
		nodo() : next(nullptr) {}

		/**
			Costruttore secondario

			@param v valore da copiare
			@param n puntatore a next

			@post value == v
			@post next == n
		*/
		nodo(const T &v, nodo* n) : value(v), next(n) {}

		/**
			Costruttore secondario

			@param v valore da copire

			@post value == v
			@post next == nullptr
		*/	
		explicit nodo(const T &v) : value(v), next(nullptr) {}

		/**
			Costruttore secondario

			@param n puntatore al prossimo nodo

			@post next == n
		*/
		explicit nodo(nodo *n) : next(n) {}

		/**
			Copy constructor. 
			Copia i dati menmbro a membro.
			In questo caso, essendo una struttura dati interna
			al Set è accettata la condivisione dei dati.

			@param other nodo da copiare
		*/
		nodo(const nodo &other) : value(other.value), next(other.next) {}

		/**
			Operatore di assegnamento.

			@param other nodo da copiare
			@return reference al nodo this
		*/
		nodo &operator=(const nodo &other) {
			value = other.value;
			next = other.next;

			return *this;
		}

		/**
			Distruttore.
		*/
		~nodo() {}
	};

	nodo *_head; ///< puntatore al primo elemento del Set
	unsigned int _size; ///< numero di elementi nel Set
	Eql _equals; ///< funtore per l'uguagianza tra dati T

public:

	/**
	 	Costruttore di default.

	 	@post _head == nullptr
	 	@post _size == 0
	*/
	Set() : _head(nullptr), _size(0) { }

	/**
	 	Copy constructor.

	 	@param other Set da copiare

	 	@post _size = other._size

	 	@throw eccezione in caso l'aggiunta di un elmeneto genera un eccezione
	*/
	Set(const Set &other) : _head(nullptr), _size(0) {
		nodo *curr = other._head;
		try {
			while(curr != nullptr) {
				add(curr->value);
				curr = curr->next;
			}
		}catch(...) {
			clear();
			throw;
		}
	}

	/**
	 	Operatore di assegnamento.

	 	@param other Set da copiare

	 	@return reference al Set this

	 	@post _size = other._size
	*/
	Set &operator=(const Set &other)  {
		if(this != &other) {
			Set tmp(other);
			std::swap(_head, tmp._head);
			std::swap(_size, tmp._size);
		}

		return *this;
	}

	/**
		Distruttore.

		@post _head == nullptr
		@post _size == 0
	*/
	~Set() {
		clear();
	} 


	/**
		Funzione che implementa l'operatore [] in sola
		lettura.

		@param index posizione del valore da ritornare
		@return reference costante al valore index-esimo

		@throw std::out_of_range possibile eccezione di index non valido
	*/ 
	const T &operator[](unsigned int index) const {

		if(index-1>_size)
				throw std::out_of_range("Range is not valid.");

		nodo *curr = _head;

		for (unsigned int i = 0; i<index-1; ++i)
				curr = curr->next;	

			return curr->value;

	}

	/**
		Funzione che implementa l'operatore ==.
		Per definizione, due Set sono uguali quando 
		contengono gli stessi elementi, anche se in 
		diverse posizioni.

		@param other Set a cui confrontare this
		@return TRUE se i due Set sono uguali
	*/ 
	bool operator==(const Set &other) const {
		if(_size!=other._size)
			return false;

		nodo *curr = other._head;
		while(curr != nullptr) {
			if(!find(curr->value))
				return false;

			curr = curr->next;
		}

		return true;
	}

	/**
		Elimina tutti gli elementi del Set.

		@post _head == nullptr;
		@post _size == 0
	*/ 
	void clear() {
		nodo *curr = _head;

	    while (curr!=nullptr) {
	    	nodo *cnext = curr->next;
			delete curr;
			curr = cnext;
	    }

	    _size = 0;
	    _head = nullptr;
	}

	/**
		Funzione che verifica se un elemento è già presente
		nel Set, con l''ausilio del funtore _equals.

		@param value elemento da cercare
		@return TRUE se l'elemento è presente nel Set
	*/ 
	bool find(const T &value) const {
		nodo *curr = _head;
		while(curr != nullptr) {
			if(_equals(value, curr->value)) {
				return true;
			}
			curr = curr->next;
		}

		return false;
	}

	/**
		Funzione che recupera il numero di elementi del Set
	
		@return numero di elementi del Set
	*/ 
	unsigned int size() const {
		return _size;
	}

	/**
		Aggiunge un elemento in testa al Set, se non già presente. 

		@param value elemento da inserire nel Set

		@post _size = _size+1

		@throw std::bad_alloc possibile eccezione nell'allocazione di spazio
	*/ 
	void add(const T &value) {
		if(find(value))
			return;

		nodo *tmp = new nodo(value);

		if(_head == nullptr) {
			_head = tmp;
			_size = 1;
		}else {
			tmp->next = _head;
			_head = tmp;
			_size++;
		}


	}

	/**
		Funzione che elimina un dato elemento dal Set.

		@param value elemento da togliere dal Set

		@post _size = _size-1
	*/ 
	void remove(const T &value) {
		if(_equals(_head->value, value)) {
			nodo *next = _head->next;
			delete _head;
			_head = next;
			_size = _size-1;
			return;
		}

		nodo *curr = _head;
		nodo *prev = _head;

		while(curr != nullptr) {
			if(_equals(value, curr->value)) {
				prev->next = curr->next;
				delete curr;
				curr = nullptr;
				_size = _size-1;
				return;
			}

			prev = curr;
			curr = curr->next;

		}
	}

	/**
		Costruttore che crea un Set a partire da un iteratore
		di inizio e uno di fine per una sequenza di
		dati di tipo Q.

		@param b iteratore di inizio sequenza
		@param e iteratore di fine sequenza

		@throw std::bad_alloc eventuale eccezione di allocaizone
	*/ 
	template <typename Iter>
	Set(Iter b, Iter e) : _head(nullptr), _size(0) {
		try {
			for (; b!=e; ++b)
				add(static_cast<T>(*b));
		}catch(...) {
			clear();
			throw;
		}
	}

	/**
		Funzione globale che implementa l'operatore di stream.
		È una funzione friend, templata sul Set di modo da
		permettere l'accesso ai dati di Set.

		@param os stream di output
		@param set Set da inviare sullo stream

		@return os stream di output
	*/ 
	friend std::ostream &operator<<(std::ostream &os,
		const Set &set) {

		nodo *curr = set._head;
		os << "[";
		while(curr != nullptr) {
			os << " " << curr->value << " ";
			curr = curr->next;
		}
		os << "]";

		return os;
	}

	/**
    Gli iteratori devono iterare sui dati inseriti nella classe
    principale. Siccome nella ordered_list mettiamo dei dati di 
    tipo T, l'iteratore deve iterare sui dati di tipo T. NON sui
    nodi della lista che sono un dettaglio implementativo interno.
  */
  class const_iterator {

  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T                         value_type;
    typedef ptrdiff_t                 difference_type;
    typedef const T*                  pointer;
    typedef const T&                  reference;
  
    const_iterator() : ptr(nullptr) {
    }
    
    const_iterator(const const_iterator &other) : ptr(other.ptr) {
    }

    const_iterator& operator=(const const_iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    ~const_iterator() { }

    // Ritorna il dato riferito dall'iteratore (dereferenziamento)
    reference operator*() const {
      return ptr->value;
    }

    // Ritorna il puntatore al dato riferito dall'iteratore
    pointer operator->() const {
      return &(ptr->value);
    }
    
    // Operatore di iterazione post-incremento
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      ptr = ptr->next;
      return tmp;
    }

    // Operatore di iterazione pre-incremento
    const_iterator& operator++() {
      ptr = ptr->next;
      return *this;
    }

    // Uguaglianza
    bool operator==(const const_iterator &other) const {
      return (ptr == other.ptr);
    }
    
    // Diversita'
    bool operator!=(const const_iterator &other) const {
      return !(other == *this);
    }

  private:
    // La classe container deve essere messa friend dell'iteratore per poter
    // usare il costruttore di inizializzazione.
    friend class Set; 

    // Costruttore privato di inizializzazione usato dalla classe container
    // tipicamente nei metodi begin e end
    const_iterator(const nodo *p) : ptr(p) { }
    
    const nodo * ptr;

    // !!! Eventuali altri metodi privati
    
  }; // classe const_iterator
  
  // Ritorna l'iteratore all'inizio della sequenza dati
  const_iterator begin() const {
    return const_iterator(_head);
  }
  
  // Ritorna l'iteratore alla fine della sequenza dati
  const_iterator end() const {
    return const_iterator(nullptr);
  }

};

/**
	Funzione globale che dato crea un nuovo Set a partire
	da tutti quei e soli quei elementi che soddisfano un 
	predicato generico P. 

	@param set Set sorgente
	@param pred predicato

	@return out Set con soli elementi che soddisfano P

	@throw eccezione in caso l'aggiunta di un elmeneto genera un eccezione
*/

template <typename T, typename E, typename P>
Set<T,E> filter_out(const Set<T,E> &set, P pred) {
	Set<T,E> out;
	typename Set<T,E>::const_iterator b, e;

	for (b = set.begin(), e = set.end(); b!=e; ++b)
	{
		if(pred(*b))
			out.add(*b);
	}

	return out;
}

/**
	Funzione globale che crea un nuovo Set con tutti
	gli elementi presenti in entrambi i Set.

	@param s1 primo Set sorgente
	@param s2 secondo Set sorgente

	@return out Set contenente gli elementi di s1 e s2

	@throw eccezione in caso l'aggiunta di un elmeneto genera un eccezione
*/ 
template <typename T, typename E>
Set<T,E> operator+(const Set<T,E> &s1, const Set<T,E> &s2) {
	Set<T,E> out = s1;
	typename Set<T,E>::const_iterator b, e;

	for (b = s2.begin(), e = s2.end(); b!=e; ++b)
		out.add(*b);

	return out;
}

/**
	Funzione globale che crea un nuovo Set con solo
	gli elementi comuni a entrambi i Set.

	@param s1 primo Set sorgente
	@param s2 secondo Set sorgente

	@return out Set contenente gli elementi comuni a s1 e s2

	@throw eccezione in caso l'aggiunta di un elmeneto genera un eccezione
*/ 
template <typename T, typename E>
Set<T,E> operator-(const Set<T,E> &s1, const Set<T,E> &s2) {
	Set<T,E> out;
	typename Set<T,E>::const_iterator b, e;

	for (b = s1.begin(), e = s1.end(); b!=e; ++b) {
		if(s2.find(*b))
			out.add(*b);
	}

	for (b = s2.begin(), e = s2.end(); b!=e; ++b) {
		if(s1.find(*b))
			out.add(*b);
	}

	return out;
}


#endif