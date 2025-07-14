#include "set.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>
/**
	@brief Funtore di uguaglianza per interi

	Confronta se due interi sono uguali
*/
struct equals_int {
	bool operator() (int a, int b) const {
		return a==b;
	}
};

/**
  @brief Test dei metodi fondamentali

  Test dei metodi fondamentali

  @throw std::badalloc
*/
void test_metodi_fondamentali() {
	std::cout<<"---- Inizio test metodi fondamentali del Set ----"<<std::endl<<std::endl;

	Set<int, equals_int> s1; // costruttore default

	s1.add(8);
	s1.add(34);

	Set<int, equals_int> s2(s1); // costruttore di copia

	s1.add(17);
	s1.add(12);
	s1.add(17); // elemento duplicato

	Set<int, equals_int> s3;

	s3 = s1; // assegnamento

	std::cout<<"Set s1: "<< s1<<std::endl;
	std::cout<<"Set s2 creato con costruttore di copia da s1: "<<s2<<std::endl;
	std::cout<<"Set s3 creato con operatore di assegnamento: "<<s3<<std::endl;

	std::cout<<"s1==s2?"<<(s1==s2)<<std::endl; // operatore di uguaglianza

	std::cout<<"s1==s3?"<<(s1==s3)<<std::endl; //operatore di uguaglianza
}

/**
	@brief Test su creazione e utilizzo set di interi

	Test di creazione e utilizzo di un set di interi non costante

	@param set set da usare per i test

	@throw std::badalloc
*/
void test_set_int(Set<int, equals_int> &set) {
	std::cout<<"---- Test su Set di interi ----"<<std::endl;

	set.add(24);
	set.add(42);
	set.add(2);
	set.add(46);
	set.add(12);
	set.add(6);

	std::cout<<"Dimensione Set: "<<set.size()<<std::endl;
	std::cout<<"Contenuto Set: "<<set<<std::endl; 

	std::cout<<"Stampa con iteratori"<<std::endl;

	Set<int, equals_int>::const_iterator b, e;

	for (b=set.begin(), e=set.end(); b!=e; ++b)
		std::cout<<*b<<std::endl;

	int value = 12;

	std::cout<<"Eliminazione del valore "<<value<<std::endl;

	set.remove(value);
	
	if(set.find(value))
		std::cout<<"Elemento non rimosso"<<std::endl;
	else
		std::cout<<"Elemento rimosso"<<std::endl;

	std::cout<<"Set dopo elemeninazione: "<<set<<std::endl;

	set.clear();
	std::cout<<"Dimensione Set dopo clear(): "<<set.size()<<std::endl;
}

/**
	@brief Test utilizzo set di interi costante

	Test di utilizzo di un set di interi costante

	@param set set da usare per i test
*/
void test_const_set_int(const Set<int, equals_int> &set) {
	std::cout<<"---- Test sul Set costante di interi ----"<<std::endl;

	std::cout<<"Dimensione del Set: "<<set.size()<<std::endl;

	Set<int, equals_int>::const_iterator b, e;

	std::cout<<"Stampa con iteratori: "<<std::endl;

	for (b=set.begin(), e=set.end(); b!=e; ++b)
		std::cout<<*b<<std::endl;

	if(set.find(218))
		std::cout<<"'218' è presente nel Set"<<std::endl;
	else
		std::cout<<"'218' non è presente nel Set"<<std::endl;

	// operazioni di add, remove, clear non ammesse
} 

/**
	@brief Funtore di uguaglianza per stringhe

	Confronta se due stringhe sono uguali
*/
struct equals_string {
	bool operator() (const std::string a, const std::string b) const {
		return a==b;
	}
};

/**
	@brief Test su creazione e utilizzo set di stringhe

	Test di creazione e utilizzo di un set di stringhe non costante

	@throw std::badalloc
	@throw std::out_of_range
*/
void test_set_stringhe() {
	std::cout<<"---- Test su Set di stringhe ----"<<std::endl;

	Set<std::string, equals_string> strs;

	strs.add("acqua");
	strs.add("cioccolata");
	strs.add("fragole");
	strs.add("arance");
	strs.add("pasta");

	std::cout<<"Dimensione set strs="<<strs.size()<<std::endl;

	std::cout<<"Stampa con operatore<< "<<strs<<std::endl;

	std::cout<<"Ricerca 'acqua': "<<strs.find("fragole")<<std::endl;
	std::cout<<"Ricerca 'pane': "<<strs.find("pane")<<std::endl;

	std::cout<<"Set[1]="<<strs[1]<<std::endl;

	std::cout<<"Remove 'acqua'"<<std::endl;

	std::string value = "acqua";

	strs.remove(value);

	Set<std::string, equals_string>::const_iterator b, e;

	std::cout<<"Stampa set con iteratore"<<std::endl;

	for (b=strs.begin(),e=strs.end(); b!=e; ++b)
		std::cout<<*b<<std::endl;

	Set<std::string, equals_string> str2 = strs;

	str2.add("gelato");

	std::cout<<"Set strs= "<<str2<<std::endl;

	std::cout<<"Strs==str2? "<<(strs==str2)<<std::endl;
}


/**
	@brief Struct che implementa un punto 2D

	Struct point che implementa un punto 2D
*/
struct point {
	int x; ///< coordinata x del punto
	int y; ///< coordinata y del punto

	point(int x_value, int y_value) : x(x_value), y(y_value) {}
};

/** 
	Ridefinizione dell'operatore di stream << per un point.
	Necessario all'operatore di stream della classe set.
*/
std::ostream &operator<<(std::ostream &os, const point &p) {
	std::cout<<"("<<p.x<<","<<p.y<<")";
	return os;
}

/**
	@brief Funtore per l'uguaglianza tra due punti.

	Funtore per il controllo dell'uguaglianza tra due punti.
	Ritorna true se p1.x==p2.x e p1.y==p2.y.
*/
struct equals_point {
	bool operator()(const point &p1, const point &p2) const {
		return((p1.x==p2.x) && (p1.y==p2.y));
	}
};


/**
	@brief Test su creazione e utilizzo set di point

	Test su creazione e utilizzo set di point

	@throw std::badalloc
	@throw std::out_of_range
*/ 
void test_set_point() {
	std::cout<<"---- Test su Set di point ----"<<std::endl;

	Set<point, equals_point> ps;
	
	std::cout<<"Inserimento nel Set ps di (0,4), (1,4), (6,2), (3,2), (4,7)"<<std::endl;
	ps.add(point(0,4));
	ps.add(point(1,4));
	ps.add(point(6,2));
	ps.add(point(3,2));
	ps.add(point(4,7));

	std::cout<<"Dimensione del set ps: "<<ps.size()<<std::endl;

	std::cout<<"Stampa ps con operatore<< "<<ps<<std::endl;

	std::cout<<"ps[4]="<<ps[4]<<std::endl;

	std::cout<<"Creazione Set ps2 per assegnamento di ps."<<std::endl;

	Set<point, equals_point> ps2;

	ps2 = ps;

	std::cout<<"Stampa ps2 con iteratori"<<std::endl;

	Set<point, equals_point>::const_iterator b,e;

	for (b=ps2.begin(),e=ps2.end(); b!=e; ++b)
		std::cout<<*b<<std::endl;

	std::cout<<"Rimozione (6,2) da ps2."<<std::endl;

	ps2.remove(point(6,2));

	std::cout<<"Cerca in ps2 (6,2): "<<ps2.find(point(6,2))<<std::endl;

	std::cout<<"ps==ps2? "<<(ps==ps2)<<std::endl;
}

/**
	@brief Funtore per l'uguaglianza tra due std::vector<int>.

	Funtore per il controllo dell'uguaglianza tra std::vector<int>.
	Ritorna true se v1 e v2 sono uguali.
*/
struct equals_vector {
	bool operator() (const std::vector<int> &v1, const std::vector<int> &v2) const {
		return v1==v2;
	}
};

/** 
	Ridefinizione dell'operatore di stream << per la stampa del std::vector<int>.
	Necessario all'operatore di stream della classe set.
*/
std::ostream &operator<<(std::ostream &os, const std::vector<int> &v) {
	os<<"{";
	for (std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i)
		os<<*i<<" ";

	os<<"}";
	return os;
}

/**
	@brief Test su creazione e utilizzo set di std::vector<int>

	Test su creazione e utilizzo set di std::vector<int>

	@throw std::badalloc
*/
void test_set_vector_int() {
	std::cout<<"---- Test su set di vector<int> ----"<<std::endl;

	std::vector<int> v1{2,6,9};
	std::vector<int> v2{32,4,52};
	std::vector<int> v3{5,3,1,8,4};

	Set<std::vector<int>,equals_vector> sv;
	sv.add(v1);
	sv.add(v2);
	sv.add(v3);


	Set<std::vector<int>,equals_vector> sv2;
	sv2.add(v1);
	sv2.add(v3);
	
	std::cout<<"Dimensione set sv: "<<sv.size()<<std::endl;
	std::cout<<"Dimensione set sv2: "<<sv2.size()<<std::endl;

	std::cout<<"Stampa sv con operatore<< "<<sv<<std::endl;
	std::cout<<"Stampa sv2 con iteratori."<<std::endl;

	Set<std::vector<int>,equals_vector>::const_iterator b,e;

	for (b=sv2.begin(),e=sv2.end(); b!=e; ++b)
		std::cout<<*b<<std::endl;

	std::cout<<"sv[2]="<<sv[2]<<std::endl;

	std::vector<int> v{2,3,4,5};

	std::cout<<"Cerca vector{2,3,4,5} in sv= "<<sv.find(v)<<std::endl;
	std::cout<<"Cerca vector{32,4,52} in sv= "<<sv.find(v2)<<std::endl;

	std::cout<<"sv==sv2? "<<(sv==sv2)<<std::endl;

	std::cout<<"Rimozione di vector{32,4,52}."<<std::endl;

	sv.remove(v2);

	std::cout<<"Dimensione set sv: "<<sv.size()<<std::endl;

	std::cout<<"sv==sv2? "<<(sv==sv2)<<std::endl;

	std::cout<<"Eliminazione di tutti gli elementi dal set sv."<<std::endl;

	sv.clear();
	std::cout<<"Dimensione set sv: "<<sv.size()<<std::endl;
}

/**
	@brief Funtore per verificare se un intero è pari.

	 Funtore che controlla se un intero è pari.
*/
struct is_even {
	bool operator() (int a) const {
		return ((a % 2) == 0);
	}
};

/**
	@brief Test sulla funzione globale filter_out

	Test sulla funzione globale filter_out che crea un
	set a partire da un altro set che soddisfa un certo
	predicato.

	@throw std::badalloc
*/
void test_filter_out() {
	std::cout<<"---- Test filter_out ----"<<std::endl;

	int dati[6] = {3,2,5,7,9,8}; 

	Set<int, equals_int> is(dati, dati+6);

	std::cout<<"Stampa con operatore<< "<<is<<std::endl; //creazione set a partire da interatori

	is_even ie;

	std::cout<<"Chiama a filter_out con is_even"<<std::endl;
	Set<int, equals_int> result = filter_out(is, ie);

	std::cout<<"Result: "<<result<<std::endl;
}

/**
	@brief Test su operator+ e operator-

	Test su operator+ che crea un set a partire dalla somma
	di altri due e su operator- che crea un set a partire
	dai elementi comuni ad entrambi i set.

	@throw std::badalloc
*/
void test_global_operator() {
	std::cout<<"---- Test su operator+ e operator- ----"<<std::endl;

	Set<std::string, equals_string> s1;
	s1.add("lasagne");
	s1.add("pesto");
	s1.add("takoyaki");
	s1.add("insalata");
	s1.add("gamberi");

	Set<std::string, equals_string> s2;
	s2.add("lasagne");
	s2.add("pesto");
	s2.add("takoyaki");
	s2.add("ricotta");
	s2.add("sofficini");
	s2.add("torta");
	s2.add("pizza");

	std::cout<<"Stampa Set 1: "<<s1<<std::endl;
	std::cout<<"Stampa Set 2: "<<s2<<std::endl;

	std::cout<<"Chiamata a operator+"<<std::endl;

	Set<std::string, equals_string> result;

	result = s1+s2;

	std::cout<<"Result: "<<result<<std::endl;

	std::cout<<"Chiamata a operator-"<<std::endl;

	result = s1-s2;

	std::cout<<"Result: "<<result<<std::endl;

}

int main() {

	test_metodi_fondamentali();
	std::cout<<std::endl;

	Set<int, equals_int> set;

	test_const_set_int(set);
	std::cout<<std::endl;

	test_set_int(set);
	std::cout<<std::endl;

	test_set_stringhe();
	std::cout<<std::endl;

	test_set_point();
	std::cout<<std::endl;

	test_filter_out();
	std::cout<<std::endl;

	test_set_vector_int();
	std::cout<<std::endl;

	test_global_operator();

	return 0;
}