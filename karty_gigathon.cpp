#include <iostream>
#include <vector>
#include <string>
#include <locale.h>
#include <time.h>
#include <cstdlib>
#include <algorithm>


using std::cout;
using std::string;

struct pojedynczaKarta {
	short kolor;
	short wartosc;
};

void wyrownaj(int rozmiar, int rozmiar_txt=0);
void tworzenieTaliKart(std::vector<pojedynczaKarta>& taliaKart,int ileKolorow=4);
void tasowanieKart(std::vector<pojedynczaKarta>& taliaKart,int ileRazy);
void wyswietlanieKart(std::vector<pojedynczaKarta>& taliaKart);

int main() {
	setlocale(LC_CTYPE, "Polish");

	std::vector<pojedynczaKarta> taliaKart;

	tworzenieTaliKart(taliaKart, 4);

	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	tasowanieKart(taliaKart,taliaKart.size());

	wyswietlanieKart(taliaKart);


	return 0;
}



void tworzenieTaliKart(std::vector<pojedynczaKarta>& taliaKart, int ileKolorow) {
	int kolor{ 1 };
	for (int i{ 2 }; i <= (52 + 4) / 4; i++) {
		for (int j{ 1 }; j <= 4; j++) {
			taliaKart.push_back({ (short)j,(short)(i) });
			kolor < ileKolorow ? kolor++ : kolor = 1;
		}
	}
}

void tasowanieKart(std::vector<pojedynczaKarta>& taliaKart, int ileRazy) {
	try {
		for (int i{ 0 }; i < ileRazy; i++) {
			int los_1 = std::rand() % taliaKart.size();
			int los_2 = std::rand() % taliaKart.size();
			std::swap(taliaKart.at(los_1), taliaKart.at(los_2));
		}
	}
	catch (const std::out_of_range blod) {
		std::cerr << "Los poza indeksem " << blod.what() << "\n";
	}
}


void wyswietlanieKart(std::vector<pojedynczaKarta>& taliaKart) {
	const string kolory[] = { "pik","trefl","karo","kier" };
	const std::string obrazkowe[] = { "Walet","Dama","Król","As" };
	for (auto karta : taliaKart) {
		if (karta.kolor == 3 || karta.kolor == 4) cout << "\033[91m";
		else cout << "\033[97m";
		cout << " ------\n";
		cout << "|";
		if (karta.wartosc <= 10) {
			cout << karta.wartosc;
			wyrownaj(karta.wartosc);
		}
		else {
			cout << obrazkowe[(int)karta.wartosc - 11];
			wyrownaj(karta.wartosc, obrazkowe[(int)karta.wartosc - 11].length());
		}

		std::cout << "| \n|      |\n|" << kolory[(int)--karta.kolor];
		wyrownaj(10, kolory[(int)karta.kolor].length());
		cout << "|\n ------\n\033[0m";
		//	Sleep(1000);
	}
}



void wyrownaj(int rozmiar, int rozmiar_txt) {
	int ile = 4 - (rozmiar_txt);
	if (rozmiar_txt > 0) ile += 2;
	if (rozmiar >= 10) ile--;
	for (int i = 0; i <= ile; i++) cout << " ";
}
