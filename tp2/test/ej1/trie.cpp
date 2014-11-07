#include "trie.h"
#include <iostream>

int main(int argc, char** argv){
	Trie* t = new Trie();
	t->addWord("BuenosAires");
	t->addWord("Bogota");
	t->addWord("SanFrancisco");
	t->addWord("RiodeJaneiro");
	t->addWord("Kingston");
	t->addWord("TuVieja");
	t->addWord("BuenosAires");
	
	cout << t->get_id("BuenosAires") << endl;
	cout << t->get_id("Bogota") << endl;
	cout << t->get_id("SanFrancisco") << endl;
	cout << t->get_id("RiodeJaneiro") << endl;
	cout << t->get_id("Kingston") << endl;
	cout << t->get_id("TuVieja") << endl;
	cout << t->get_id("ASlkghlsgdj") << endl;
	cout << t->size() << endl;
	borrar_trie(t);
	delete t;

	return 0;
}
