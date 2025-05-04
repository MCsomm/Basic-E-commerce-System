#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class Produkt {
private:
	string name;
	string vyrobca;
	int ID;
	int pocet;
	int cena;

public:
	Produkt() {}
	Produkt(string n1, string v1 ,int id, int p, int c) :name(n1), vyrobca(v1), ID(id), pocet(p), cena(c) {}
	string N() { return name; }
	string V() { return vyrobca; }
	int I() { return ID; }
	int P() { return pocet; }
	int C() { return cena; }
	void setprodukt(string n1, string v1, int id, int p, int c) { name = n1; vyrobca = v1; ID = id; pocet = p; cena = c; }
	void printprodukt();
	void reducepocet();
};
void Produkt::printprodukt()
{
	cout << name << vyrobca << ID << pocet << cena << endl;
}

void Produkt::reducepocet()
{
	pocet--;
}

class Zakaznik {
private:
	string meno;
	string priezvisko;
	int rozpocet;
	Produkt kupenprod[20];
	int counter = 0;
	
public:
	Zakaznik() {}
	Zakaznik(string m1, string p1, int r1) :meno(m1), priezvisko(p1), rozpocet(r1) {}
	void setzakaznik(string m1 ,string p1, int r1);
	int ROZPOCET();
	void reducerozpocet(Produkt *prodPtr);
	void setkupenprod(Produkt *prodPtr);
	void printkupenprod();
	void savekupenprod();
};

void Zakaznik::setzakaznik(string m1, string p1, int r1) {
	meno = m1; priezvisko = p1; rozpocet = r1;
	cout << m1 << " " << p1 << " " << r1 << endl << endl;
}

int Zakaznik::ROZPOCET()
{
	return rozpocet;
}

void Zakaznik::reducerozpocet(Produkt* prodPtr)
{
	rozpocet = rozpocet - prodPtr->C();
}

void Zakaznik::setkupenprod(Produkt *prodPtr)
{
	kupenprod[counter] = *prodPtr;
	counter++;
}

void Zakaznik::savekupenprod()
{
	fstream f2;
	f2.open("Kupene.txt", ios::out);
	for (int i = 0; i < counter; i++)
	{
		f2 << kupenprod[i].N() << " " << kupenprod[i].V() << endl;
	}
	f2.close();
}

void Zakaznik::printkupenprod()
{
	for (int i = 0; i < 3; i++)
	{
		cout << kupenprod[i].N()<< " " << kupenprod[i].V() << endl;/* kupenprod[i].I() << kupenprod[i].P() << kupenprod[i].C();*/
	}
}

class Eshop {
private:
	int n;
	Produkt* produkty;
public:
	Eshop() {}
	Eshop(int n1) :n(n1) {}
	~Eshop();
	void setprodukty();
	Produkt* podlanazvu();	
	Produkt* podlavyrobcu();
	Produkt* infoPodlaId(Produkt* prod);
	void kupit(Zakaznik* roz,Produkt* prod);
};

Eshop::~Eshop()
{
	delete[] produkty;
}

void Eshop::setprodukty()
{
	string na, vy;
	int id, p, c;

	fstream f1;
	f1.open("Zad.txt", ios::in);
	if (!f1.is_open())
	{
		cout << "neotvorilo";
	}
	f1 >> n;
	produkty = new Produkt[n];

	for (int i = 0; i < n; i++)
	{
		f1 >> na >> vy >> id >> p >> c;
		produkty[i].setprodukt(na, vy, id, p, c);
		
		cout << produkty[i].N() << " " << produkty[i].V() << /*" "  << produkty[i].I()<< " " << produkty[i].P() << " " << produkty[i].C() <<*/ endl;
	}
	cout << endl;
	f1.close();
}

Produkt* Eshop::podlanazvu()
{
	string strc;
	cin >> strc;

	Produkt* s = new Produkt[n];
	//cout << n;
	for (int i = 0; i < n; i++)
	{
		if (strc.compare(produkty[i].N()) == 0)
		{
			cout << produkty[i].N() << " " << produkty[i].V() << " ID: " << produkty[i].I() << endl;
			s[i].setprodukt(produkty[i].N(), produkty[i].V(), produkty[i].I(), produkty[i].P(), produkty[i].C());
			//cout << s[i].N();
		}
		else
		{
			s[i].setprodukt("bruh", "bruh", -456735437, 0, 0);
		}
	}
	return s;
}

Produkt* Eshop::podlavyrobcu()
{
	string strc;
	cin >> strc;
	Produkt* s=new Produkt[n];
	for (int i = 0; i < n; i++)
	{
		if (strc.compare(produkty[i].V()) == 0)
		{
			cout << produkty[i].N() << " " << produkty[i].V() << " ID: " << produkty[i].I() << endl;
			s[i].setprodukt(produkty[i].N(), produkty[i].V(), produkty[i].I(), produkty[i].P(), produkty[i].C());
			//cout << s[i].N();
		}
		else 
		{
			s[i].setprodukt("bruh", "bruh", -456735437, 0, 0);
		}
	}
	return s;
}

Produkt* Eshop::infoPodlaId(Produkt* prod)
{
	int id;
	Produkt* prodPtr = nullptr;
	cout << "Zadajte id produktu: " << endl;
	cin >> id;
	for (int i = 0; i < n; i++) {
		if (id == prod[i].I())
		{
			cout <<"Na sklade: "<< prod[i].P() << " Cena: " << prod[i].C() << endl;
			prodPtr = &(produkty[i]);
		}
	}
	return prodPtr;
}

void Eshop::kupit(Zakaznik* roz,Produkt* prodPtr)
{
	int v = 0, w;
	cout << "Tlac 1: Kupit\nTlac 2: Spat" << endl;
	cin >> w;

	while (v != 2)
	{
		switch (w)
		{
		case 1:
			if (roz->ROZPOCET()-prodPtr->C() >= 0 && prodPtr->P() >0) {
				prodPtr->reducepocet();
				roz->reducerozpocet(prodPtr);
				roz->setkupenprod(prodPtr);
				roz->savekupenprod();
				v = 2;
				break;
			}
			else if(roz->ROZPOCET() - prodPtr->C() < 0)
			{
				cout << "Nemas na to peniaze" << endl;
				v = 2;
				break;
			}
			else
			{
				cout << "Nie je na skalde" << endl;
				v = 2;
				break;
			}
		case 2:
			v = 2;
			break;
		}
	}
	cout << "pocet teraz: " << prodPtr->P() << " "<< roz->ROZPOCET()<< endl;
}

int main(void)
{
	string m1 = "Akos";
	string p1 = "Ibolya";
	int r1=50;
	Zakaznik ja;
	cout << "Zadajte svoje meno, priezvisko a rozpocet" << endl;
	//cin >> m1 >> p1 >> r1;
	ja.setzakaznik(m1,p1,r1);

	Eshop eshop;
	eshop.setprodukty();

	Produkt* prod=nullptr;
	Produkt* prodPtr=nullptr;

	int v = 0, w;
	while (v != 3) {
		cout << "Hladat podla nazvu, tlac 1 \nHladat podla vyrobcu, tlac 2 \nExit, tlac 3\n";
		cin >> w;
		switch (w)
		{
		case 1:
			prod = eshop.podlanazvu();
			prodPtr = eshop.infoPodlaId(prod);
			eshop.kupit(&ja,prodPtr);
			break;
		case 2:
			prod = eshop.podlavyrobcu();
			prodPtr = eshop.infoPodlaId(prod);
			eshop.kupit(&ja,prodPtr);
			break;
		case 3:
			v = 3;
			break;
		}
	}
	ja.printkupenprod();
	
	cout << "Suma v e-shope: " << r1 - ja.ROZPOCET() << endl;;
	

	return 0;
}