#include<iostream>
#include<string>
using namespace std;

class Plantatie
{
private:
	const int cod;
	string numePlantatie;
	int nrCopaci;
	int* varsteCopaci;
public:
	~Plantatie()
	{
		if (this->varsteCopaci != NULL)
			delete[] this->varsteCopaci;
	}

	Plantatie(int cod) :cod(cod)
	{
		this->numePlantatie = "Plantatia mea";
		this->nrCopaci = 0;
		this->varsteCopaci = NULL;
	}

	Plantatie(int cod, string numePlantatie, int nrCopaci, int* varsteCopaci) :cod(cod)
	{
		this->numePlantatie = numePlantatie;
		this->nrCopaci = nrCopaci;
		this->varsteCopaci = new int[this->nrCopaci];
		for (int i = 0; i < this->nrCopaci; i++)
			this->varsteCopaci[i] = varsteCopaci[i];
	}

	Plantatie(const Plantatie& p) :cod(p.cod)
	{
		this->numePlantatie = p.numePlantatie;
		this->nrCopaci = p.nrCopaci;
		this->varsteCopaci = new int[this->nrCopaci];
		for (int i = 0; i < this->nrCopaci; i++)
			this->varsteCopaci[i] = p.varsteCopaci[i];
	}

	Plantatie operator=(const Plantatie& p)
	{
		this->numePlantatie = p.numePlantatie;
		this->nrCopaci = p.nrCopaci;
		if (this->varsteCopaci != NULL)
			delete[] this->varsteCopaci;
		this->varsteCopaci = new int[this->nrCopaci];
		for (int i = 0; i < this->nrCopaci; i++)
			this->varsteCopaci[i] = p.varsteCopaci[i];
		return *this;
	}

	string getNumePlantatie()
	{
		return this->numePlantatie;
	}

	int getNrCopaci()
	{
		return this->nrCopaci;
	}

	int getCod()
	{
		return this->cod;
	}

	void setVarsteCopaci(int* varsteCopaci, int nrCopaci)
	{
		if (varsteCopaci != NULL && nrCopaci > 0)
		{
			this->nrCopaci = nrCopaci;
			if (this->varsteCopaci != NULL)
				delete[]this->varsteCopaci;
			this->varsteCopaci = new int[this->nrCopaci];
			for (int i = 0; i < this->nrCopaci; i++)
				this->varsteCopaci[i] = varsteCopaci[i];
		}
		else throw exception("Imposibil!");
	}

	int getVarstaCopac(int n)
	{
		return this->varsteCopaci[n];
	}

	int cautaCopacInVarsta()
	{
		int max = 0;
		for (int i = 0; i < this->nrCopaci; i++)
			if (this->varsteCopaci[i] > max)
				max = this->varsteCopaci[i];
		return max;
	}

	int medieVarstaCopaci()
	{
		int varste = 0;
		for (int i = 0; i < this->nrCopaci; i++)
				varste+= this->varsteCopaci[i];
		return varste/this->nrCopaci;
	}

	friend ostream& operator<<(ostream& out, Plantatie& p)
	{
		out << p.cod<<". "<<p.numePlantatie << " are " << p.nrCopaci << " copaci cu varstele: ";
		for (int i = 0; i < p.nrCopaci; i++)
			out<<p.varsteCopaci[i] << " ";
		return out;
	}

	int operator()(int n)
	{
		int nr = 0;
		for (int i = 0; i <this->nrCopaci; i++)
				if(this->varsteCopaci[i]<n)
					nr ++;
		return nr;
	}

	Plantatie operator++(int)
	{
		Plantatie copie = *this;
		this->nrCopaci = copie.nrCopaci + 1;
		if (this->varsteCopaci != NULL)
			delete[] this->varsteCopaci;
		this->varsteCopaci = new int[this->nrCopaci];
		for (int i = 0; i < this->nrCopaci - 1; i++)
			this->varsteCopaci[i] = copie.varsteCopaci[i];
		this->varsteCopaci[this->nrCopaci - 1] = 0;
		return copie;
	}

	explicit operator string()
	{
		return this->numePlantatie;
	}

	bool operator>(Plantatie p)
	{
		if (this->medieVarstaCopaci() > p.medieVarstaCopaci())
			return true;
		else
			return false;
	}
};

void main()
{
	Plantatie p1(101);
	cout << p1.getNumePlantatie();
	int varsteCopaci[]{ 20,36,27,84 };
	Plantatie p2(102, "Goji Farm", 4, varsteCopaci);
	cout << "\n" << p2.getNrCopaci();

	Plantatie p3 = p2;
	cout << "\n" << p3.getCod();

	int varsteCopaci2[]{ 40,39,27 };
	try
	{
		p3.setVarsteCopaci(varsteCopaci2, 3);
		cout << "\n" << p3.getVarstaCopac(1);
	}
	catch(exception ex)
	{
		cout << ex.what();
	}

	p1 = p3;
	int varstaMaxima = p1.cautaCopacInVarsta();
	cout << "\nCopacul cel mai in varsta are: " << varstaMaxima;
	cout << endl;

	Plantatie* pp = new Plantatie(103);
	*pp = p2;
	cout << *pp;

	delete pp;
	int nrCopaciTineri = p2(30);
	cout << "\n" << nrCopaciTineri;

	Plantatie p4 = p3++;
	cout << endl;
	cout << p3;
	cout << endl;
	cout << p4;

	cout << endl;
	cout << (string)p2;
	if (p2 > p3)
		cout << "\nMedia de varsta a copacilor din P2 este mai mare decat cea din P3";
	else
		cout<< "\nMedia de varsta a copacilor din P3 este mai mare decat cea din P2";
}