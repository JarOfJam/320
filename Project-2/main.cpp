//Jordan Welch - Cosc 320 - Project 2 - 11/10/19

#include <iostream>
#include <iomanip>
#include <math.h>
#include <string.h>
#include <fstream>
#include <chrono>

int bucksize[10000]; //global array used for stats, keeps track of how many are in each bucket
int misspelled = 0; //global tracker of misspelled words
int suggestions = 0; //global tracker of suggestions

struct Node {
	std::string data;
	int hashVal;
	Node* prev;
	Node* next;
};

Node* poss = new Node; //global linked list that holds alledit possibilities
Node* oed = new Node; //global linked list that holds edit possibilities from one edit distance
Node* words = new Node; //global linked list that holds all words out of edit possibilities

class Dictionary {
	private:
		int buck;
		
		Node** LList;
	public:
		Dictionary(int);
		void insertNode(std::string);
		bool searchNode(std::string);
		void wordCheck(std::string);
		
};

size_t hash(size_t x) {
	int w = 31;
	int p = 13;
	int a = 7;
	return (((a*x) & ((1 << w) - 1)) >> (w - p));
}

size_t shash(std::string a) {
	int sum = 0;
	int i = 0;
	while(a[i] != '\0') {
		sum = sum * 10 +a[i] - '\0';
		i++;
	}
	return hash(sum);
}

void fixWord(std::string key) { //one edit distance call
	char tmp;
	for(int i = 0; i < key.length(); i++) { //replacing one char
		for(int j = 'a'; j <= 'z'; j++) { //lowercase
			tmp = key[i];
			key[i] = (char) j;
			poss->data = key;
			poss->next = new Node;
			poss->next->prev = poss;
			poss = poss->next;
			oed->data = key;
                        oed->next = new Node;
                        oed->next->prev = oed;
                        oed = oed->next;
			key[i] = tmp;
		}
		for(int j = 'A'; j <= 'Z'; j++) { //uppercase
                        tmp = key[i];
                        key[i] = (char) j;
                        poss->data = key;
                        poss->next = new Node;
			poss->next->prev = poss;
			poss = poss->next;
			oed->data = key;
                        oed->next = new Node;
                        oed->next->prev = oed;
                        oed = oed->next;
                        key[i] = tmp;
                }
	}
	for(int i = 0; i < key.length() - 1; i++) { //swapping adj chars
		tmp = key[i];
		key[i] = key[i+1];
		key[i+1] = tmp;
		poss->data = key;
		poss->next = new Node;
		poss->next->prev = poss;
		poss = poss->next;
		oed->data = key;
                oed->next = new Node;
                oed->next->prev = oed;
                oed = oed->next;
		key[i+1] = key[i];
		key[i] = tmp;
	}
	std::string word;
	for(int i = 0; i < key.length(); i++) { //delete one char
		word = key;
		word.erase(word.begin() + i);
		poss->data = word;
                poss->next = new Node;
                poss->next->prev = poss;
                poss = poss->next;
                oed->data = word;
                oed->next = new Node;
                oed->next->prev = oed;
                oed = oed->next;
	}
	for(int i = 0; i <= key.length(); i++) { //insert one char
		for(int j = 'a'; j <= 'z'; j++) {
			word = key;
			word.insert(word.begin() + i, (char) j);
			poss->data = word;
                	poss->next = new Node;
                	poss->next->prev = poss;
                	poss = poss->next;
                	oed->data = word;
                	oed->next = new Node;
                	oed->next->prev = oed;
                	oed = oed->next;
		}
		for(int j = 'A'; j <= 'Z'; j++) {
                        word = key;
                        word.insert(word.begin() + i, (char) j);
                        poss->data = word;
                        poss->next = new Node;
                        poss->next->prev = poss;
                        poss = poss->next;
                        oed->data = word;
                        oed->next = new Node;
                        oed->next->prev = oed;
                        oed = oed->next;
                }
	}
}

void fixWord2(std::string key) { //two edit distance call
  char tmp;
	for(int i = 0; i < key.length(); i++) { //replacing one char
		for(int j = 'a'; j <= 'z'; j++) { //lowercase
			tmp = key[i];
			key[i] = (char) j;
			poss->data = key;
			poss->next = new Node;
			poss->next->prev = poss;
			poss = poss->next;
			key[i] = tmp;
		}
		for(int j = 'A'; j <= 'Z'; j++) { //uppercase
                        tmp = key[i];
                        key[i] = (char) j;
                        poss->data = key;
                        poss->next = new Node;
			poss->next->prev = poss;
			poss = poss->next;
			key[i] = tmp;
                }
	}
	for(int i = 0; i < key.length() - 1; i++) { //swapping adj chars
		tmp = key[i];
		key[i] = key[i+1];
		key[i+1] = tmp;
		poss->data = key;
		poss->next = new Node;
		poss->next->prev = poss;
		poss = poss->next;
		key[i+1] = key[i];
		key[i] = tmp;
	}
	std::string word;
        for(int i = 0; i < key.length(); i++) { //delete one char
                word = key;
                word.erase(word.begin() + i);
                poss->data = word;
                poss->next = new Node;
                poss->next->prev = poss;
                poss = poss->next;
        }
	for(int i = 0; i <= key.length(); i++) { //insert one char
                for(int j = 'a'; j <= 'z'; j++) {
                        word = key;
                        word.insert(word.begin() + i, (char) j);
                        poss->data = word;
                        poss->next = new Node;
                        poss->next->prev = poss;
                        poss = poss->next;
                }
                for(int j = 'A'; j <= 'Z'; j++) {
                        word = key;
                        word.insert(word.begin() + i, (char) j);
                        poss->data = word;
                        poss->next = new Node;
                        poss->next->prev = poss;
                        poss = poss->next;
                }
        }
}

Dictionary::Dictionary(int a) { //constructer
	buck = a;
	LList = new Node*[buck];
	for(int i = 0; i < buck; i++) {
		LList[i] = NULL;
	}
}

void Dictionary::insertNode(std::string key) { //inserts the node in link list index of hash value of key
	int h = shash(key);
	bucksize[h]++;
	Node* newNode = new Node;
	newNode->data = key;
	newNode->hashVal = h;
	newNode->prev = NULL;
	newNode->next = NULL;
	if(LList[h] != NULL) {
		newNode->next = LList[h];
		newNode->next->prev = newNode;
	}
	LList[h] = newNode;
	
}

bool Dictionary::searchNode(std::string key) { //compares to strings at link list index of hash value of key
	int h = shash(key);
	Node* findNode = LList[h];
	bool found = false;
	if(findNode != NULL) {
		while(findNode != NULL) {
			if(findNode->data == key) {
				found = true;
			}
			if(found) {
				return true;
			}
			findNode = findNode->next;
		}
	}
	return false;
}

void Dictionary::wordCheck(std::string key) { //handler that searches for each word and runs one and two edit distance checks
	bool found = searchNode(key);
	if(!found) {
		misspelled++;
		fixWord(key);
		while(oed->prev != NULL) {
			oed = oed->prev;
		}
		while(oed->next != NULL) {
			fixWord2(oed->data);
			oed = oed->next;
		}
		while(poss->prev != NULL) {
			poss = poss->prev;
		}
		while(poss->next != NULL) {
			if(searchNode(poss->data)) {
				words->data = poss->data;
				words->next = new Node;
				words->next->prev = words;
				words = words->next;
				suggestions++;
			}
			poss = poss->next;
		}
		while(words->prev != NULL) {
			words = words->prev;
		}
		std::cout << "Misspelled word: " << "\033[0;31m" << key << "\033[0m" << std::endl << "Suggestions:" << std::endl;
		bool sugg = false;
		for(int i = 1; i < 20 && !((words->data).empty()); i++) { //prints up to 20 suggested corrections
			
			std::cout << words->data << std::endl;
			words = words->next;
			sugg = true;
		}
		if(!sugg) {
			std::cout << "No suggestions available" << std::endl;
		}
		oed->next = NULL;
		oed->prev = NULL;
		poss->next = NULL;
		poss->prev = NULL;
	}
}

int main() {
	for(int i = 0; i < 10000; i++) {
		bucksize[i] = 0;
	}
	Dictionary dict(10000);
	std::ifstream engl ("english.txt");
	std::string in;
	int i = 0;
	auto begin = std::chrono::system_clock::now();
	while(!engl.eof()) { //reads in the file
		getline(engl, in);
		dict.insertNode(in);
		i++;
	}
	auto finish = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = finish-begin;
	engl.close();
	std::cout << "Total words: " << i << std::endl; //stats below
	int max = 0;
	int min = 0;
	int used = 0;
	while(bucksize[min] == 0) {
		min++;
	}
	for(int j = 0; j < 10000; j++) {
		if(bucksize[max] < bucksize[j]) {
			max = j;
		}
		if(bucksize[min] > bucksize[j] && bucksize[j] != 0) {
			min = j;
		}
		if(bucksize[j] != 0) {
			used++;
		}
	}
	std::cout << "Biggest bucket size: " << bucksize[max] << std::endl;
	std::cout << "Smallest bucket size: " << bucksize[min] << std::endl;
	std::cout << "Total number of buckets: 10000" << std::endl;
	std::cout << "Number of used buckets: " << used << std::endl;
	std::cout << "Average number of nodes in each bucket: " << (double) i/used << std::endl;
	std::cout << "Total time taken: " << elapsed_seconds.count() << std::endl;
	std::cout << "Enter words to spellcheck: "; //spell check begins
	std::string check;
	getline(std::cin, check);
	begin = std::chrono::system_clock::now();
	std::string checking;
	checking = check[0];
	for(int j = 1; j < check.length(); j++) { //checks each word in the user input
		if(!isspace(check[j])) {
			checking = checking + check[j];
		}
		else {
			dict.wordCheck(checking);
			words->next = NULL;
			words->prev = NULL;
			checking = check[j+1];
			j++;
		}
	}
	dict.wordCheck(checking);
	finish = std::chrono::system_clock::now();
	elapsed_seconds = finish-begin;
	std::cout << "Number of misspelled words: " << misspelled << std::endl;
	std::cout << "Number of suggestions: " << suggestions << std::endl;
	std::cout << "Time required to find suggestions: " << elapsed_seconds.count() << std::endl;
	checking = check[0];
        for(int j = 1; j < check.length(); j++) { //prints sentence with highlighted misspelled words
                if(!isspace(check[j])) {
                        checking = checking + check[j];
                }
                else {
			if(dict.searchNode(checking)) {
				std::cout << checking << " ";
			}
			else {
				std::cout << "\033[0;31m" << checking << "\033[0m ";
			}
			checking = check[j+1];
			j++;
                }
        }
	if(dict.searchNode(checking)) {
        	std::cout << checking << " ";
        }
        else {
        	std::cout << "\033[0;31m" << checking << "\033[0m ";
        }
	std::cout << std::endl;
	checking = check[0];
	for(int j = 1; j < check.length(); j++) { //asks if you want to add misspelled words to dictionary
                if(!isspace(check[j])) {
                        checking = checking + check[j];
                }
                else {
                        if(!dict.searchNode(checking)) {
                                std::cout << "\033[0;31m" << checking << "\033[0m" << std::endl;
				std::cout << "Save word to dictionary? Y/N" << std::endl;
                		std::string save;
                		std::cin >> save;
                		if(save.compare("Y") == 0) {
                        		std::ofstream sav ("english.txt", std::ios_base::app);
                        		sav << checking << "\n";
                		}
			}
			checking = check[j+1];
			j++;
                }
        }
	if(!dict.searchNode(checking)) {
        	std::cout << "\033[0;31m" << checking << "\033[0m" << std::endl;
                std::cout << "Save word to dictionary? Y/N" << std::endl;
                std::string save;
                std::cin >> save;
                if(save.compare("Y") == 0) {
                	std::ofstream sav ("english.txt", std::ios_base::app);
                        sav << checking << "\n";
                }
	}
	return 0;
}
