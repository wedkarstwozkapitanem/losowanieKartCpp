//Dominik Łempicki (Kapitan)
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <random>


using std::cout;
using std::string;

struct pojedynczaKarta {
	short kolor;
	short wartosc;
};

void wyrownaj(const int rozmiar,int rozmiar_txt=0);
void tworzenieTaliKart(std::vector<pojedynczaKarta>& taliaKart,const int ileKolorow=4);
void tasowanieKart(std::vector<pojedynczaKarta>& taliaKart,const int ileRazy);
void wyswietlanieKart(const std::vector<pojedynczaKarta>& taliaKart);

int main() {
	setlocale(LC_CTYPE, "Polish");


	std::vector<pojedynczaKarta> taliaKart;

	tworzenieTaliKart(taliaKart, 4);

	//std::srand(static_cast<unsigned int>(std::time(nullptr)));
	tasowanieKart(taliaKart,taliaKart.size());

	cout << "Karty po losowaniu: \n";
	wyswietlanieKart(taliaKart);


	return 0;
}



void tworzenieTaliKart(std::vector<pojedynczaKarta>& taliaKart, const int ileKolorow) {
	for (int i{ 2 }; i <= (52 + 4) / 4; i++) {
		int kolor{ 1 };
		for (int j{ 1 }; j <= 4; j++) {
			taliaKart.push_back({ static_cast<short>(j),static_cast<short>(i) });
			kolor < ileKolorow ? kolor++ : kolor = 1;
		}
	}
}

void tasowanieKart(std::vector<pojedynczaKarta>& taliaKart,const int ileRazy) {
	try {
		std::random_device generator_losujocy;
		std::mt19937 los(generator_losujocy());
		for (int i{ 0 }; i < ileRazy; i++) {
			const int los_1 = los() % taliaKart.size();
			const int los_2 = los () % taliaKart.size();
			std::swap(taliaKart.at(los_1), taliaKart.at(los_2));
			//std::shuffle(taliaKart.begin(), taliaKart.end(), los);
		}
	}
	catch (const std::out_of_range blod) {
		std::cerr << "Los poza indeksem " << blod.what() << "\n";
	}
}


void wyswietlanieKart(const std::vector<pojedynczaKarta>& taliaKart) {
	const string kolory[] = { "pik","trefl","karo","kier" };
	const std::string obrazkowe[] = { "Walet","Dama","Król","As" };


	for (auto karta : taliaKart) {
		
		if (karta.kolor == 3 || karta.kolor == 4) cout << "\033[91m";
		else cout << "\033[97m";
		cout << " ------\n|";
		if (karta.wartosc <= 10) {
			cout << karta.wartosc;
			wyrownaj(karta.wartosc);
		}
		else {
			cout << obrazkowe[(int)karta.wartosc - 11];
			wyrownaj(karta.wartosc, obrazkowe[(int)karta.wartosc - 11].length());
		}
		std::cout << "| \n|      |\n|" << kolory[(int)karta.kolor-1];
		wyrownaj(10, kolory[(int)karta.kolor-1].length());
		cout << "|\n ------\n\033[0m";
		//	Sleep(1000);
		
	}
}



void wyrownaj(const int rozmiar,int rozmiar_txt) {
	int ile = 4 - (rozmiar_txt);
	if (rozmiar_txt > 0) ile += 2;
	if (rozmiar >= 10) ile--;
	for (int i = 0; i <= ile; i++) cout << " ";
}
