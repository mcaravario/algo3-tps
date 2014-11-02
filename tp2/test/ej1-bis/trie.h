/***********:*****************************************************************
* Name: main.cpp
* Author: Carlos F. Perea
* Description: Trie data structure
* Copyright: OPEN
****************************************************************************/

/***********************************************************************
 * Modificado para el Ejercicio 1 del TP2 de AED3.
 * Autores: Federico Hosen,  Martín J. Caravario.
 * Se agrega un "significado" ID entero, para representar a una palabra
 * con un entero de manera unívoca. Las palabras son numeradas 
 * consecutivamente desde 0.
 * 
 ************************************************************************/

#include <vector>
#include <string>
#include <assert.h>
 
using namespace std;
 
/**
* Class: Node
* Represents a node within a trie tree
*/
class Node
{
public:
    char value;             // the character value (a-z)
    bool end;               // indicates whether this node completes a word
    Node * children[26];    // represents the 26 letters in the alphabet
    int id;					// represents the ID of the string. Only matters when end is true.
    Node(char value);
    ~Node();
};
 
/**
* Constructor method
*/
Node::Node(char value)
{
    this->value = value;
    // Initializes all of the children with NULL value
    for (int i = 0; i < 26; ++i)
        children[i] = NULL;
}
 
/**
* Destructor method
*/
Node::~Node()
{
    // free resources
}
 
/**
* Class: Trie
* Represents a trie tree data structure
*/
class Trie
{
public:
    Trie();
    ~Trie();
    void addWord(string word);
    bool searchForWord(string word);
    void deleteWord(string word);
    Node * getRoot();
    int get_id(string);
		int size();
private:
    Node * root;
    int free_id;
		int elem_count;
};
 
/**
* Constructor method
*/
Trie::Trie()
{
    // Initialize the trie
    root = new Node(' ');
    root->end = true;
    free_id = 0;
}
 
/**
* Destructor method
*/
Trie::~Trie()
{
    // Free resources
}
 
/**
* Gets the root of the trie
* @return Node *    Pointer to the root node
*/
Node * Trie::getRoot()
{
    return root;
}
 
/**
* Add a word to the trie
* @param string Word to add to the trie
* @return void
*/
void Trie::addWord(string word)
{
	/* Si la palabra ya está no la agrego.
	 **/
	if (searchForWord(word)) return;
    Node * currentNode = root;
 
    for (int i = 0; i < word.size(); ++i)
    {
        char currentChar = tolower(word.at(i));
        int index = currentChar - 'a';
        assert(index >= 0);     // Makes sure the character is between a-z
        if (currentNode->children[index] != NULL)
        {
            // check if the current node has the current character as one of its decendants
            currentNode = currentNode->children[index];
        }
        else
        {
            // the current node doesn't have the current character as one of its decendants
            Node * newNode = new Node(currentChar);
            currentNode->children[index] = newNode;
            currentNode = newNode;
        }
        if (i == word.size() - 1)
        {
            // the last character of the word has been reached
            currentNode->end = true;
            currentNode->id = free_id;
            free_id++;
						elem_count++;
        }
    }
}
 
/**
* Searches for a word in the trie
* @param string The word to search in the trie
* @return bool  True if it's found, false otherwise
*/
bool Trie::searchForWord(string word)
{
    Node * currentNode = root;
    for (int i = 0; i < word.size(); ++i)
    {
        char currentChar = tolower(word.at(i));
        int index = currentChar - 'a';
        assert(index >= 0);
        // if the current node has the current character as one of its decendants
        if (currentNode->children[index] != NULL)
            currentNode = currentNode->children[index];
        else
            return false;
        // makes sure the last node is marked as an end for a word
        if (i == word.size() - 1 && !currentNode->end)
            return false;
    }
    return true;
}
 
/**
* Deletes a word from the trie
* @param string The word to be deleted from the trie
* @return void
*/
void Trie::deleteWord(string word)
{
    Node * currentNode = root;
    Node * lastWord = root;
    for (int i = 0; i < word.size(); ++i)
    {
        char currentChar = tolower(word.at(i));
        int index = currentChar - 'a';
        assert(index >= 0);
        // if the current node has the current character as one of its decendants
        if (currentNode->children[index] != NULL)
            currentNode = currentNode->children[index];
        // the current node doesn't have the current character which means the word is not in the trie
        else
            return;
        if (i == word.size() - 1 && currentNode->end)
            currentNode->end = false;
    }
}
 
/**
* Traverse the trie in-order fashion to print the words in lexicographical order
*/
void alphabetize(Node * node, string prefix = "")
{

    for (int i = 0; i < 26; ++i)
    {
        if (node->children[i] != NULL)
        {
            string currentString = prefix + node->children[i]->value;
            alphabetize(node->children[i], currentString);
        }
    }
}


/**
* Devuelve el ID asociado a la clave buscada.
* Si la clave no existe como palabra se devuelve -1.
*/
int Trie::get_id(string word){
	Node * currentNode = root;
	for (int i = 0; i < word.size(); ++i)
	{
		char currentChar = tolower(word.at(i));
		int index = currentChar - 'a';
		assert(index >= 0);
		// if the current node has the current character as one of its decendants
		if (currentNode->children[index] != NULL)
			currentNode = currentNode->children[index];
		else
			return -1;
		// makes sure the last node is marked as an end for a word
		if (i == word.size() - 1 && !currentNode->end)
			return -1;
	}
	return currentNode->id;
}


/**
 *	Devuelve la cantidad de palabras que hay en el Trie.
 **/

int Trie::size(){
	return elem_count;
}
void borrar_recursivo(Node* nodo){
	if(nodo != NULL){
		for(int i = 0; i<26; i++){
			borrar_recursivo(nodo->children[i]);
		}
		delete nodo;
	}
}


void borrar_trie(Trie * t){
	Node * raiz = t->getRoot();
	borrar_recursivo(raiz);
}




