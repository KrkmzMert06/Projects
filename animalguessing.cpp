#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
//TAHMIN HAKKI SAYACI VE KELIME MI YOKSA HARF MI SOYLEYECEK ONU DA EKLE

void fillthestring(string*ptr,int size) {
	for (int i = 0; i < size; i++) {
		(*ptr) += '_';
	}
}


int main() {
	int size,counter=0;
	char letter;

	string word,newstring;
	string animals[18] = { "dog","cat","cow","hen","sheep","rabbit","duck","giraffe","goat","horse","donkey","crocodile","kangaroo","bird","shark","whale","dolphin","piranha"};
	srand(time(0));

	word = animals[rand() % 10];
	size = word.length();
	fillthestring(&newstring, size);
	cout << "Animal has " <<size<<" letters\n";
	while (counter<4) {
		bool correct = false;
		cout << "Enter a letter:";
		cin >> letter;
		for (int i = 0; i < size; i++) {
			if (word[i] == letter) {
				correct = true;
				newstring[i] = letter;
			
			}
		}
		if (correct != true) {
			cout << "NO!!\n";
			counter++;
			if(counter==4){
				break;
			}
			cout<<"You have "<<3-counter<<" rights left\n";
			
			
		}
		else{
			cout << "YESS !!\n";
		}
		cout << newstring<<"\n";
	

		if (newstring == word) {
			cout << "YOU WON THE GAME";
			return 0;
		}

		
	}
	cout << "YOU LOST THE GAME";

	




	return 0;
}