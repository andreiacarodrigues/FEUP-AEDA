#include "ListManipulation.h"

using namespace std;

// Ficheiros Write

string blanks(string s, unsigned int n)
{
	while (s.size() < n)
		s += " ";

	return s;
}

void write_contribuintes(std::vector<Contribuinte*> &cVec)
{
	stringstream ss;
	ofstream out_stream;

	out_stream.open("contribuintes.txt");

	out_stream << "NIF         Nome                                  Email                    Morada Fiscal" << endl;

	for (unsigned int i = 0; i < cVec.size(); i++)
	{
		ss << cVec[i]->getNIF() << "   " << blanks(cVec[i]->getNome() , 35) << "   " << blanks(cVec[i]->getEmail(), 22) << "   " << cVec[i]->getMF() << endl;
		string sender = ss.str();
		out_stream << sender;

		ss.str("");
		ss.clear();
	}

	out_stream.close();
}

void write_passivos(std::vector<PassivoIVA> &pVec)
{
	stringstream ss;
	ofstream out_stream;

	out_stream.open("passivos.txt");


	for (unsigned int i = 0; i < pVec.size(); i++)
	{
		ss << "NIF " << pVec[i].getNIF() << endl;
		ss << "Nome " << pVec[i].getNome() << endl;
		ss << "Email " << pVec[i].getEmail() << endl;
		ss << "Morada Fiscal " << pVec[i].getMF() << endl;
		ss << "CAE " << pVec[i].getCAE() << endl;

		for (unsigned int j = 0; j < pVec[i].getDeclaracoes().size(); j++)
		{
			ss << pVec[i].getDeclaracoes()[j].get_TFM() << endl;
			ss << pVec[i].getDeclaracoes()[j].get_Data().getAno() << "/";
			ss << pVec[i].getDeclaracoes()[j].get_Data().getMes() << "/";
			ss << pVec[i].getDeclaracoes()[j].get_Data().getDia() << endl;
		}

		ss << "FIM" << endl;

		string sender = ss.str();
		out_stream << sender;

		ss.str("");
		ss.clear();
	}

	out_stream.close();
}

void write_faturas(std::vector<Fatura> &fVec)
{
	stringstream ss;
	stringstream ssAux;
	ofstream out_stream;

	string utility = "";

	out_stream.open("faturas.txt");

	out_stream << "ID          Data         NIF do emissor    NIF do consumidor   Valor pago      Taxa IVA" << endl;

	for (unsigned int i = 0; i < fVec.size(); i++)
	{
		ssAux << fVec[i].getID();
		utility = ssAux.str();
		ssAux.str("");
		ss << blanks(utility, 10);


		ss << "  " << fVec[i].getData().getDia() << "/" << fVec[i].getData().getMes() << "/" << fVec[i].getData().getAno() << "     " << blanks(fVec[i].getNIF_Emi(), 15) << "   " << blanks(fVec[i].getNIF_Cons(), 17) << "   ";
			
		ssAux << fVec[i].getValor_Pago();
		utility = ssAux.str();
		ssAux.str("");
		ss << blanks(utility, 15);
		
		ss << "   " << fVec[i].getRegime_IVA() << endl;

		string sender = ss.str();
		out_stream << sender;

		ss.str("");
		ss.clear();
	}

	out_stream.close();
}

// Ficheiros Load

string trim(string& str)
{
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

void load_contribuintes(std::vector<Contribuinte*> &cVec)
{
	string receiveS;
	stringstream ss;
	ifstream in_stream;

	string NIF = "";
	string Nome = "";
	string Email = "";
	string MF = "";

	in_stream.open("contribuintes.txt");

	getline(in_stream, receiveS);

	while (getline(in_stream, receiveS))
	{
		NIF = trim(receiveS.substr(0, 9));
		Nome = trim(receiveS.substr(12, 38));
		Email = trim(receiveS.substr(43, 28));
		MF = trim(receiveS.substr(71));

		Contribuinte * newC = new Contribuinte(NIF, Nome, Email, MF);
		try
		{
			add_contribuinte(cVec, newC);

		}
		catch (Contribuinte::NIF_Invalido ni)
		{
			cout << "NIF invalido: " << ni.getNIF() << endl;
		}
		catch (Contribuinte::ContribuinteJaExistente)
		{
			cout << "Contribuinte ja existente." << endl;
		}
	}
}

void load_passivos(std::vector<Contribuinte*> &cVec, std::vector<PassivoIVA> &pVec, std::vector<Fatura> &fVec)
{

	string receiveS;
	stringstream ss;
	ifstream in_stream;

	string NIF = "";
	string Nome = "";
	string Email = "";
	string MF = "";
	int CAE;

	bool escrever = false;
	bool escreverDec = false;

	double valor;
	int dia, mes, ano;

	in_stream.open("passivos.txt");

	int controlo = 0;

	while (getline(in_stream, receiveS))
	{
		switch (controlo)
		{
		case 0:
			NIF = receiveS.substr(4, 9);
			controlo++;
			break;
		case 1:
			Nome = receiveS.substr(5);
			controlo++;
			break;
		case 2:
			Email = receiveS.substr(6);
			controlo++;
			break;
		case 3:
			MF = receiveS.substr(14);
			controlo++;
			break;
		case 4:
			CAE = atoi(receiveS.substr(4).c_str());
			controlo++;
			escrever = true;
			break;
		case 5:
			if (receiveS == "FIM")
				controlo = 0;
			else
			{
				valor = atoi(receiveS.substr(0).c_str());

				getline(in_stream, receiveS);

				int pos1 = -1;
				int pos2 = -1;

				for (unsigned int i = 0; i < receiveS.size(); i++)
				{
					if (receiveS[i] == '/')
					{
						if (pos1 == -1)
							pos1 = i;
						else
							pos2 = i;
					}
				}

				ano = atoi(receiveS.substr(0, pos1).c_str());
				mes = atoi(receiveS.substr(pos1 + 1, pos2 - pos1).c_str());
				dia = atoi(receiveS.substr(pos2 + 1).c_str());
				escreverDec = true;
			}
		}

		if (escrever)
		{
			PassivoIVA newP(NIF, Nome, Email, MF, CAE);

			try
			{
				add_passivo(cVec, pVec, &newP);

			}
			catch (Contribuinte::NIF_Invalido ni)
			{
				cout << "NIF invalido: " << ni.getNIF() << endl;
			}
			catch (Contribuinte::ContribuinteJaExistente ni)
			{
				cout << "Contribuinte ja existente." << endl;
			}
		}

		if (escreverDec)
		{
			PassivoIVA newP(NIF, Nome, Email, MF, CAE);

			Date data(ano, mes, dia);
			DeclIVA newDec (valor, data);

			add_declaracao(pVec, fVec, newP, newDec);
		}
	}

	in_stream.close();
}

void load_faturas(std::vector<Contribuinte*> &cVec, std::vector<PassivoIVA> &pVec, std::vector<Fatura> &fVec)
{
	string receiveS;
	string receiveAux;
	stringstream ss;
	ifstream in_stream;

	int ID;
	string NIF_e = "";
	string NIF_c = "";
	double valor;
	double regimeIVA;
	int dia, mes, ano;

	in_stream.open("faturas.txt");

	getline(in_stream, receiveS);

	while (getline(in_stream, receiveS))
	{
		receiveAux = receiveS.substr(0, 12);
		receiveAux = trim(receiveAux);
		ID = atoi(receiveAux.c_str());

		receiveAux = receiveS.substr(12, 11);
		receiveAux = trim(receiveAux);

		int pos1 = -1;
		int pos2 = -1;

		for (unsigned int i = 0; i < receiveAux.size(); i++)
		{
			if (receiveAux[i] == '/')
			{
				if (pos1 == -1)
					pos1 = i;
				else
					pos2 = i;
			}
		}

		dia = atoi(receiveAux.substr(0, pos1).c_str());
		mes = atoi(receiveAux.substr(pos1 + 1, pos2 - pos1).c_str());
		ano = atoi(receiveAux.substr(pos2 + 1).c_str());

		Date data(ano, mes, dia);

		string NIF_e = receiveS.substr(25, 9);
		string NIF_c = receiveS.substr(43, 9);

		valor = atoi(trim(receiveS.substr(63, 9)).c_str());
		regimeIVA = atoi(receiveS.substr(79).c_str());

		Fatura newF (data, NIF_e, NIF_c, valor, regimeIVA);
		
		try
		{
			add_fatura(cVec, pVec, fVec, newF);

		}
		catch (Fatura::NIFInvalido)
		{
			cout << "NIF invalido." << endl;
		}
		catch (Fatura::MontanteInvalido){
			cout << "Montante invalido." << endl;
		}
		catch (Contribuinte::ContribuinteInexistente)
		{
			cout << "Contribuinte ja existente." << endl;
		}
	}

	in_stream.close();
}

// Pesquisa

vector<Fatura> Faturas_Emissor_Mes(std::vector<Fatura> &fVec, std::string NIF, Date data)
{
	vector<Fatura> Faturas_Ret;

	for (unsigned int i = 0; i < fVec.size(); i++)
		if ((fVec[i].getNIF_Emi() == NIF) && (fVec[i].getData().getAno() == data.getAno()) && (fVec[i].getData().getMes() == data.getMes()))
			Faturas_Ret.push_back(fVec[i]);

	return Faturas_Ret;
}

vector<Fatura> faturas_emissor(std::vector<Fatura> &fVec, std::string NIF)
{
	vector<Fatura> Faturas_Ret;
	for (unsigned int i = 0; i < fVec.size(); i++)
		if (fVec[i].getNIF_Emi() == NIF)
			Faturas_Ret.push_back(fVec[i]);

	return Faturas_Ret;
}

vector<DeclIVA> declaracoes_sujeito_passivo(std::vector<PassivoIVA> &pVec, std::string NIF)
{
	vector<DeclIVA> Declaracoes_Ret;
	for (unsigned int i = 0; i < pVec.size(); i++)
		if (pVec[i].getNIF() == NIF)
			Declaracoes_Ret = pVec[i].getDeclaracoes();

	return Declaracoes_Ret;
}

int procura_contribuinte(std::vector<Contribuinte*> &cVec, std::string NIF)
{
	for (unsigned int i = 0; i < cVec.size(); i++)
	{
		if (cVec[i]->getNIF() == NIF)
			return i;
	}
    throw Contribuinte::ContribuinteInexistente(NIF);
}

int procura_passivo(std::vector<PassivoIVA> &pVec, std::string NIF)
{
	for (unsigned int i = 0; i < pVec.size(); i++)
	{
		if (pVec[i].getNIF() == NIF)
			return i;
	}
	throw PassivoIVA::PassivoIVAInexistente(NIF);
}

int procura_fatura(std::vector<Fatura> &fVec, std::string NIF, Date data)
{
	
	for (unsigned int i = 0; i < fVec.size(); i++)
	{
		if (fVec[i].getNIF_Emi() == NIF && (fVec[i].getData().getAno() == data.getAno()) && (fVec[i].getData().getMes() == data.getMes()) && (fVec[i].getData().getDia() == data.getDia()))
			return i;
	
	}
	throw Fatura::FaturaInexistente(NIF, data);
}

int procura_declaracao(std::vector<PassivoIVA> &pVec, std::string NIF, Date data)
{
	for (unsigned int i = 0; i < pVec.size(); i++)
	{
		if (pVec[i].getNIF() == NIF)
		{
			for (unsigned int j = 0; j < pVec[i].getDeclaracoes().size(); j++)
			{
				if ((pVec[i].getDeclaracoes()[j].get_Data().getAno() == data.getAno()) && (pVec[i].getDeclaracoes()[j].get_Data().getMes() == data.getMes()))
					return j;
			}
			throw DeclIVA::DeclaracaoInexistente(NIF, data);
		}
	}
	throw PassivoIVA::PassivoIVAInexistente(NIF);
}

// Adições

void add_contribuinte(vector<Contribuinte*> &cVec, Contribuinte * c)
{
	if (!c->isValid())
		throw Contribuinte::NIF_Invalido(c->getNIF());
	else
	{
		for (unsigned int i = 0; i < cVec.size(); i++)
		{
			if (cVec[i]->getNIF() == c->getNIF())
			{
				throw Contribuinte::ContribuinteJaExistente();
			}
		}

		cVec.push_back(c);
		cout << "Contribuinte adicionado. " << endl;
	}
}

void add_passivo(vector<Contribuinte*> &cVec, vector<PassivoIVA> &pVec, PassivoIVA * p)
{
	if (!p->isValid())
		throw Contribuinte::NIF_Invalido(p->getNIF());
	else
	{
		for (unsigned int i = 0; i < cVec.size(); i++)
		if (cVec[i]->getNIF() == p->getNIF())
			throw Contribuinte::ContribuinteJaExistente();

		cVec.push_back(p);
		pVec.push_back(*p);
		cout << "Sujeito passivo adicionado. " << endl;
	}
}

void add_fatura(std::vector<Contribuinte*> &cVec, std::vector<PassivoIVA> &pVec, std::vector<Fatura> &fVec, Fatura &f)
{
	// Verifica se o montante é positivo
	if (f.getValor_Pago() < 0)
		throw Fatura::MontanteInvalido();

	// Verifica se os NIF são iguais
	if (f.getNIF_Cons() == f.getNIF_Emi())
		throw Fatura::NIFInvalido();
	
	// Verifica se o emissor e o consumidor existem
	bool consExiste = false;
	bool emExiste = false;

	for (unsigned int i = 0; i < cVec.size(); i++)
		if (cVec[i]->getNIF() == f.getNIF_Cons())
			consExiste = true;

	if (!consExiste)
		throw Contribuinte::ContribuinteInexistente(f.getNIF_Cons());

	for (unsigned int i = 0; i < pVec.size(); i++)
		if (pVec[i].getNIF() == f.getNIF_Emi())
			emExiste = true;

	if (!emExiste)
		throw Contribuinte::ContribuinteInexistente(f.getNIF_Emi());

	// Adciona a fatura com o ID adequado
	f.setID(Faturas_Emissor_Mes(fVec, f.getNIF_Emi(), f.getData()).size() + 1);
	fVec.push_back(f);
	cout << "Fatura adicionada. " << endl;
}

void add_declaracao(vector<PassivoIVA> &pVec, vector<Fatura> &fVec, PassivoIVA p, DeclIVA d)
{
	double total_montante_faturas = 0;

	for (unsigned int i = 0; i < pVec.size(); i++)
	{
		if (pVec[i].getNIF() == p.getNIF())
		{
			vector<Fatura> faturas_passivo = Faturas_Emissor_Mes(fVec, p.getNIF(), d.get_Data());
			
			for (unsigned int j = 0; j < faturas_passivo.size(); j++)
			{
				total_montante_faturas += faturas_passivo[j].getValor_Pago() * (faturas_passivo[j].getRegime_IVA() / 100);
			}

			if (total_montante_faturas == d.get_TFM())
			{
				vector<DeclIVA> declaracoes;
				for (unsigned int k = 0; k < pVec[i].getDeclaracoes().size(); k++)
					declaracoes.push_back(pVec[i].getDeclaracoes()[k]);
				declaracoes.push_back(d);
				pVec[i].setDeclaracoes(declaracoes);
				cout << "Declaracao adicionada com sucesso." << endl;
				return;
			}
			else
				throw DeclIVA::DeclaracaoInvalida(total_montante_faturas, d.get_TFM(), faturas_passivo);
		}
	}
}

// Remoções
void retira_contribuinte(vector<Contribuinte*> &cVec, std::string NIF)
{
	for (unsigned int i = 0; i < cVec.size(); i++)
	{
		if (NIF == cVec[i]->getNIF())
		{
			cVec.erase(cVec.begin() + i);
			cout << "Contribuinte eliminado. " << endl;
			return;
		}
	}
	throw Contribuinte::ContribuinteInexistente(NIF);
}

void retira_passivo(vector<Contribuinte*> &cVec,vector<PassivoIVA> &pVec, std::string NIF)
{
	for (unsigned int j = 0; j < cVec.size(); j++)
	{
		if (NIF == cVec[j]->getNIF())
		{
			cVec.erase(cVec.begin() + j);
		}
	}
	
	for (unsigned int i = 0; i < pVec.size(); i++)
	{
		if (NIF == pVec[i].getNIF())
		{
			pVec.erase(pVec.begin() + i);
			cout << "Sujeito passivo eliminado. " << endl;
			return;
		}
	}
	throw PassivoIVA::PassivoIVAInexistente(NIF);
}

void remove_faturas(std::vector<Fatura> &fVec, std::string NIF)
{
	vector<Fatura> f;
	for (unsigned int i = 0; i < fVec.size(); i++)
	{
		if (NIF == fVec[i].getNIF_Emi())
		{
			f.push_back(fVec[i]);
			fVec.erase(fVec.begin() + i);
			i--;
		}
	}

	if (f.size() == 0)
		throw Fatura::FaturasInexistentes(NIF);
	else
	{
		cout << "Faturas eliminadas. " << endl;
		return;
	}
}

// Ordenaçao

void ordena_faturas_NIF_Emi(vector<Fatura> &fVec)
{
	for (unsigned int p = 1; p < fVec.size(); p++)
	{
		Fatura tmp = fVec[p];
		int j;
		for (j = p; j > 0 && (tmp.getNIF_Emi() < fVec[j - 1].getNIF_Emi()); j--)
			fVec[j] = fVec[j - 1];
		fVec[j] = tmp;
	}
}

void ordena_faturas_montante(vector<Fatura> &fVec)
{
	for (unsigned int p = 1; p < fVec.size(); p++)
	{
		Fatura tmp = fVec[p];
		int j;
		for (j = p; j > 0 && (tmp.getValor_Pago() < fVec[j - 1].getValor_Pago()); j--)
			fVec[j] = fVec[j - 1];
		fVec[j] = tmp;
	}
}

void ordena_contribuintes_NIF(vector<Contribuinte *> &cVec)
{
	for (unsigned int p = 1; p < cVec.size(); p++)
	{
		Contribuinte * tmp = cVec[p];
		int j;
		for (j = p; j > 0 && (tmp->getNIF() < cVec[j - 1]->getNIF()); j--)
			cVec[j] = cVec[j - 1];
		cVec[j] = tmp;
	}
}

void ordena_contribuintes_nome(vector<Contribuinte* > &cVec)
{
	for (unsigned int p = 1; p < cVec.size(); p++)
	{
		Contribuinte * tmp = cVec[p];
		int j;
		for (j = p; j > 0 && (tmp->getNome() < cVec[j - 1]->getNome()); j--)
			cVec[j] = cVec[j - 1];
		cVec[j] = tmp;
	}
}

void ordena_passivos_NIF(vector<PassivoIVA> &pVec)
{
	for (unsigned int p = 1; p < pVec.size(); p++)
	{
		PassivoIVA tmp = pVec[p];
		int j;
		for (j = p; j > 0 && (tmp.getNIF() < pVec[j - 1].getNIF()); j--)
			pVec[j] = pVec[j - 1];
		pVec[j] = tmp;
	}
}

void ordena_passivos_nome(vector<PassivoIVA> &pVec)
{
	for (unsigned int p = 1; p < pVec.size(); p++)
	{
		PassivoIVA tmp = pVec[p];
		int j;
		for (j = p; j > 0 && (tmp.getNome() < pVec[j - 1].getNome()); j--)
			pVec[j] = pVec[j - 1];
		pVec[j] = tmp;
	}
}
