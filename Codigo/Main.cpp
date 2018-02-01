#include "Contribuinte.h"
#include "Fatura.h"
#include "CustomUI.h"
#include "ListManipulation.h"

using namespace std;

int main()
{
	// Resource Declaration

	vector<Contribuinte*> Contribuintes;
	vector<PassivoIVA> Passivos_IVA;
	vector<Fatura> Faturas;

	// Load from files

	load_contribuintes(Contribuintes);
	load_passivos(Contribuintes, Passivos_IVA, Faturas);
	load_faturas(Contribuintes, Passivos_IVA, Faturas);

	// Program Logic

	Contribuinte Edu("510550037", "Eduardo", "edu@gmail.com", "Rua do Edu");
	Contribuinte De("505753669", "De", "de@gmail.com", "Rua do De");
	Contribuinte Diogo("500835217", "Diogo", "d@gmail.com", "Rua do Diogo");
	PassivoIVA Maria("509766226", "Maria", "mar@gmail.com", "Rua do Maria", 2);
	PassivoIVA Manel("123456789", "Manel", "mane@gmail.com", "Rua do Manel", 3);
	Fatura f1(Date(2000, 1, 2), "509766226", "510550037", 50, 50);
	Fatura f2(Date(2000, 2, 2), "123456789", "505753669", 10, 50);
	DeclIVA dec1(25, Date(2000, 1, 20));
	DeclIVA dec2(5, Date(2000, 2, 30));
	//add_contribuinte(Contribuintes, &Edu);
	//add_contribuinte(Contribuintes, &De);
	//add_contribuinte(Contribuintes, &Diogo);
	//add_passivo(Contribuintes, Passivos_IVA, &Maria);
	//add_passivo(Contribuintes, Passivos_IVA, &Manel);
	//add_fatura(Contribuintes, Passivos_IVA, Faturas, f1);
	//add_fatura(Contribuintes, Passivos_IVA, Faturas, f2);
	//add_declaracao(Passivos_IVA, Faturas, Maria, dec1);
	//add_declaracao(Passivos_IVA, Faturas, Manel, dec2);

	
	clrscr();

	bool running = true;

	while (running)
	{
		int comando1;
		int comando2;
		int comando3;
		int comando4;
		int comando5;
		int comando6;
		setcolor(11);
		cout << "      FATURACAO DE IVA - Turma 6 - Grupo 15 - MIEIC 2015/2016 " << endl << endl << endl;
		setcolor(7);
		cout << "Insira um dos seguintes comandos: " << endl << endl;
		setcolor(8);
		cout << "1 - Adicionar ..." << endl;
		cout << "2 - Remover ..." << endl;
		cout << "3 - Imprimir ..." << endl;
		cout << "4 - Ordenar ..." << endl;
		cout << "5 - Procurar ..." << endl;
		cout << "6 - Salvar informacao" << endl;
		cout << "7 - Encerrar programa" << endl << endl;
		cout << " -> ";
		cin >> comando1;

		switch (comando1)
		{
		case 1:
		{	
			 clrscr();
			 setcolor(7);
			 cout << "Insira um dos seguintes comandos: " << endl << endl;
			 setcolor(8);
			 cout << "1 - Adicionar Contribuinte" << endl;
			 cout << "2 - Adicionar Sujeito Passivo de IVA" << endl;
			 cout << "3 - Adicionar Fatura" << endl;
			 cout << "4 - Adicionar Declaracao" << endl;
			 cout << "0 - Retornar ao menu anterior" << endl << endl;
			 cout << " -> ";
			 cin >> comando2;

			 switch (comando2)
			 {
			 case 1:
			 {
					   string nif;
					   string nome;
					   string email;
					   string morada;
					   clrscr();
					   setcolor(7);
					   cout << "Insira os dados necessarios: " << endl << endl;
					   setcolor(8);
					   cout << "NIF: ";
					   cin >> nif;
					   cout << "Nome: ";
					   cin.ignore(99999, '\n');
					   getline(cin, nome);
					   cout << "Email : ";
					   cin >> email;
					   cout << "Morada Fiscal : ";
					   cin.ignore(99999, '\n');
					   getline(cin, morada);
					   cout << endl;

					   Contribuinte * novoC = new Contribuinte(nif, nome, email, morada);
					  

					   try{   add_contribuinte(Contribuintes, novoC);   }
					   catch (Contribuinte::NIF_Invalido ni)
					   {
						   setcolor(7);
						   cout << "NIF invalido: " << ni.getNIF() << endl;
					   }
					   catch (Contribuinte::ContribuinteJaExistente ni)
					   {
						   setcolor(7);
						   cout << "Contribuinte ja existente." << endl;
					   }
					   setcolor(7);
					   cout << "Clique para continuar." << endl;
					   system("pause");
					   clrscr();	
					   break;
			 }
			 case 2:
			 {
					   string nif;
					   string nome;
					   string email;
					   string morada;
					   int cae;
					   clrscr();
					   setcolor(7);
					   cout << "Insira os dados necessarios: " << endl << endl;
					   setcolor(8);
					   cout << "NIF: ";
					   cin >> nif;
					   cout << "Nome: ";
					   cin.ignore(99999, '\n');
					   getline(cin, nome);
					   cout << "Email : ";
					   cin >> email;
					   cout << "Morada Fiscal : ";
					   cin.ignore(99999, '\n');
					   getline(cin, morada);
					   cout << "Classificacao de atividades economicas : ";
					   cin >> cae;
					   cout << endl;
					   PassivoIVA * novoP = new PassivoIVA(nif, nome, email, morada, cae);
					   try{ add_passivo(Contribuintes,Passivos_IVA, novoP); }
					   catch (Contribuinte::NIF_Invalido ni)
					   {
						   setcolor(7);
						   cout << "NIF invalido: " << ni.getNIF() << endl;
					   }
					   catch (Contribuinte::ContribuinteJaExistente ni)
					   {
						   setcolor(7);
						   cout << "Contribuinte ja existente." << endl;
					   }
					   setcolor(7);
					   cout << "Clique para continuar." << endl;
					   system("pause");
					   clrscr();
					   break;
			 }
			 case 3:
			 {
					   int dia;
					   int mes;
					   int ano;
					   string ne;
					   string nc;
					   double vp;
					   double ri;
					   clrscr();
					   setcolor(7);
					   cout << "Insira os dados necessarios: " << endl << endl;
					   setcolor(8);
					   cout << "Data de Emissao da Fatura: " << endl;
					   cout << "Dia: ";
					   cin >> dia;
					   cout << "Mes: ";
					   cin >> mes;
					   cout << "Ano : ";
					   cin >> ano;
					   cout << "NIF do Emissor : ";
					   cin >> ne;
					   cout << "NIF do Consumidor : ";
					   cin >> nc;
					   cout << "Valor a pagar : ";
					   cin >> vp;
					   cout << "Regime IVA (%) : ";
					   cin >> ri; 
					   cout << endl;
					   try
					   {   add_fatura(Contribuintes, Passivos_IVA, Faturas, Fatura(Date(ano, mes, dia), ne, nc, vp, ri));  }
					   catch (Fatura::MontanteInvalido f)
					   {
						   setcolor(7);
						   cout << "Montante introduzido tem de ser maior que 0" << endl;
					   }
					   catch (Fatura::NIFInvalido n)
					   {
						   setcolor(7);
						   cout << "O NIF do emissor nao pode ser igual ao NIF do consumidor. " << endl;
					   }
					   catch (Contribuinte::ContribuinteInexistente c)
					   {
						   setcolor(7);
						   cout << "Contribuinte com o nif " << c.getNIF() << " inexistente." << endl;
					   }
					   setcolor(7);
					   cout << "Clique para continuar." << endl;
					   system("pause");
					   clrscr();
					   break;
			 }
			 case 4:
			 {
					   int dia;
					   int mes;
					   int ano;
					   double valor;
					   string nif;
					   clrscr();
					   setcolor(7);
					   cout << "Insira os dados necessarios: " << endl << endl;
					   setcolor(8);
					   cout << "NIF Sujeito Passivo de IVA: ";
					   cin >> nif;
					   cout << "Data de Emissao da Declaracao: " << endl;
					   cout << "Dia: ";
					   cin >> dia;
					   cout << "Mes: ";
					   cin >> mes;
					   cout << "Ano : ";
					   cin >> ano;
					   cout << "Valor Total da Faturacao Mensal: ";
					   cin >> valor;
					   cout << endl;
					   
					   try
					   {
						   int index = procura_passivo(Passivos_IVA, nif);
						   add_declaracao(Passivos_IVA, Faturas, Passivos_IVA[index], DeclIVA(valor, Date(ano, mes, dia)));
					   }
					   catch (DeclIVA::DeclaracaoInvalida dec)
					   {
						   if (dec.valorMenor())
						   {
							   setcolor(7);
							   cout << "Declaracao nao adicionada. Valor em falta: " << dec.valorEmFalta() << endl;
						   }
						   else
						   {
							   setcolor(7);
							   cout << "Declaracao nao adicionada. Montante declarado superior ao valor total a pagar. Lista de faturas referentes ao mes: " << endl;
							   for (unsigned int i = 0; i < dec.getFaturas().size(); i++)
							   {
								   dec.getFaturas()[i].print();
							   }
						   }
					   }
					   catch (PassivoIVA::PassivoIVAInexistente p)
					   {
						   setcolor(7);
						   cout << "Sujeito passivo com o nif " << p.getNIF() << " inexistente." << endl;
					   }
					   setcolor(7);
					   cout << "Clique para continuar." << endl;
					   system("pause");
					   clrscr();
					   break;
			 }
			 case 0:{ clrscr(); break; }
			 default:
				 break;
			 }
			 break;
		}
		case 2:
		{
				  clrscr();
				  setcolor(7);
				  cout << "Insira um dos seguintes comandos: " << endl << endl;
				  setcolor(8);
				  cout << "1 - Remover Contribuinte" << endl;
				  cout << "2 - Remover Sujeito Passivo de IVA" << endl;
				  cout << "3 - Remover Faturas de um Sujeito Passivo de IVA" << endl;
				  cout << "0 - Retornar ao menu anterior" << endl << endl;
				  cout << " -> ";
				  cin >> comando3;

				  switch (comando3)
				  {
				  case 1:
				  {
							string nif;
							clrscr();
							setcolor(7);
							cout << "Insira os dados necessarios: " << endl << endl;
							setcolor(8);
							cout << "NIF Contribuinte: ";
							cin >> nif;
							try
							{	retira_contribuinte(Contribuintes, nif); }
							catch (Contribuinte::ContribuinteInexistente c)
							{
								setcolor(7);
								cout << "Contribuinte com o nif " << c.getNIF() << " inexistente." << endl;
							}
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 2:
				  {
							string nif;
							clrscr();
							setcolor(7);
							cout << "Insira os dados necessarios: " << endl << endl;
							setcolor(8);
							cout << "NIF Sujeito Passivo IVA: ";
							cin >> nif;
							try
							{retira_passivo(Contribuintes, Passivos_IVA, nif);}
							catch (PassivoIVA::PassivoIVAInexistente p)
							{
								setcolor(7);
								cout << "Contribuinte com o nif " << p.getNIF() << " inexistente." << endl;

							}
							catch (Contribuinte::ContribuinteInexistente c)
							{
								setcolor(7);
								cout << "Contribuinte com o nif " << c.getNIF() << " inexistente." << endl;
							}
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 3:
				  {
							string nif;
							clrscr();
							setcolor(7);
							cout << "Insira os dados necessarios: " << endl << endl;
							setcolor(8);
							cout << "NIF Sujeito Passivo de IVA : ";
							cin >> nif;
							
							try
							{remove_faturas(Faturas, nif);}
							catch (Fatura::FaturasInexistentes f)
							{
								setcolor(7);
								cout << "O contribuinte com o NIF " << f.getNIF() << " nao tem faturas. " << endl;
							}
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 0:{ clrscr(); break; }
				  default:
					  break;
				  } 
				  break;
		}
		case 3:
		{
				  clrscr();
				  setcolor(7);
				  cout << "Insira um dos seguintes comandos: " << endl << endl;
				  setcolor(8);
				  cout << "1 - Imprimir Contribuintes" << endl;
				  cout << "2 - Imprimir Sujeitos Passivos de IVA" << endl;
				  cout << "3 - Imprimir Faturas" << endl;
				  cout << "4 - Imprimir Faturas de um Sujeito Passivo de IVA" << endl;
				  cout << "5 - Imprimir Faturas de um Sujeito Passivo de IVA num Determinado Mes" << endl;
				  cout << "6 - Imprimir Declaracoes de um Sujeito Passivo de IVA" << endl;
				  cout << "0 - Retornar ao menu anterior" << endl << endl;
				  cout << " -> ";
				  cin >> comando4;

				  switch (comando4)
				  {
				  case 1:
				  {
							clrscr();
							setcolor(8);
							for (unsigned int i = 0; i < Contribuintes.size(); i++)
								Contribuintes[i]->print();
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 2:
				  {
							clrscr();
							setcolor(8);
							for (unsigned int i = 0; i < Passivos_IVA.size(); i++)
								Passivos_IVA[i].print();
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 3:
				  {
							clrscr();
							setcolor(8);
							for (unsigned int i = 0; i < Faturas.size(); i++)
								Faturas[i].print();
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 4:
				  {
							string nif;
							clrscr();
							setcolor(7);
							cout << "Insira os dados necessarios: " << endl << endl;
							setcolor(8);
							cout << "NIF Sujeito Passivo de IVA : ";
							cin >> nif;
							setcolor(8);
							vector<Fatura> faturas = faturas_emissor(Faturas, nif);
							for (unsigned int i = 0; i < faturas.size(); i++)
								faturas[i].print();
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 5:
				  {
							string nif;
							int dia;
							int mes;
							int ano;
							clrscr();
							setcolor(7);
							cout << "Insira os dados necessarios: " << endl << endl;
							setcolor(8);
							cout << "NIF Sujeito Passivo de IVA : ";
							cin >> nif;
							cout << "Data de Emissao da Fatura: " << endl;
							cout << "Dia: ";
							cin >> dia;
							cout << "Mes: ";
							cin >> mes;
							cout << "Ano : ";
							cin >> ano;
							setcolor(8);
							vector<Fatura> faturas = Faturas_Emissor_Mes(Faturas, nif, Date(ano, mes, dia));
							for (unsigned int i = 0; i < faturas.size(); i++)
								faturas[i].print();
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 6:
				  {
							string nif;
							clrscr();
							setcolor(7);
							cout << "Insira os dados necessarios: " << endl << endl;
							setcolor(8);
							cout << "NIF Sujeito Passivo de IVA : ";
							cin >> nif;
							setcolor(8);
							vector<DeclIVA> declaracoes = declaracoes_sujeito_passivo(Passivos_IVA, nif);
							cout << declaracoes.size();
							for (unsigned int i = 0; i < declaracoes.size(); i++)
								declaracoes[i].print();
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 0:{ clrscr(); break; }
				  default:
					  break;
				  }
				  break;
		}
		case 4:
		{
				  clrscr();
				  setcolor(7);
				  cout << "Insira um dos seguintes comandos: " << endl << endl;
				  setcolor(8);
				  cout << "1 - Ordenar Contribuintes pelo NIF" << endl;
				  cout << "2 - Ordenar Contribuintes pelo nome" << endl;
				  cout << "3 - Ordenar Sujeitos Passivos de IVA pelo NIF" << endl;
				  cout << "4 - Ordenar Sujeitos Passivos de IVA pelo nome" << endl;
				  cout << "5 - Ordenar Faturas pelo NIF do Emissor" << endl;
				  cout << "6 - Ordenar Faturas pelo Montante" << endl;
				  cout << "0 - Retornar ao menu anterior" << endl << endl;
				  cout << " -> ";
				  cin >> comando5;

				  switch (comando5)
				  {
				  case 1:
				  {
							clrscr();
							setcolor(8);
							ordena_contribuintes_NIF(Contribuintes);
							cout << "Ordenacao concluida." << endl;
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 2:
				  {
							clrscr();
							setcolor(8);
							ordena_contribuintes_nome(Contribuintes);
							cout << "Ordenacao concluida." << endl;
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 3:
				  {
							clrscr();
							setcolor(8);
							ordena_passivos_NIF(Passivos_IVA);
							cout << "Ordenacao concluida." << endl;
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 4:
				  {
							clrscr();
							setcolor(8);
							ordena_passivos_nome(Passivos_IVA);
							cout << "Ordenacao concluida." << endl;
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 5:
				  {
							clrscr();
							setcolor(8);
							ordena_faturas_NIF_Emi(Faturas);
							cout << "Ordenacao concluida." << endl;
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 6:
				  {
							clrscr();
							setcolor(8);
							ordena_faturas_montante(Faturas);
							cout << "Ordenacao concluida." << endl;
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 0:{ clrscr(); break; }
				  default:
					  break;
				  }
				  break;
		}
		case 5:
		{
				  clrscr();
				  setcolor(7);
				  cout << "Insira um dos seguintes comandos (retornam indice no vetor onde estes elementos estao presentes): " << endl << endl;
				  setcolor(8);
				  cout << "1 - Procurar Contribuinte" << endl;
				  cout << "2 - Procurar Sujeito Passivo de IVA" << endl;
				  cout << "3 - Procurar Fatura de um Sujeito Passivo de IVA" << endl;
				  cout << "4 - Procurar Declaracao de um Sujeito Passivo de IVA" << endl;
				  cout << "0 - Retornar ao menu anterior" << endl << endl;
				  cout << " -> ";
				  cin >> comando6;

				  switch (comando6)
				  {
				  case 1:
				  {
							string nif;
							clrscr();
							setcolor(7);
							cout << "Insira os dados necessarios: " << endl << endl;
							setcolor(8);
							cout << "NIF Contribuinte: ";
							cin >> nif;
							try
							{
								if (procura_contribuinte(Contribuintes, nif) >= 0)
									cout << procura_contribuinte(Contribuintes, nif) << endl;
							}
							catch (Contribuinte::ContribuinteInexistente c)
							{
								cout << "Contribuinte com o nif " << c.getNIF() << " inexistente." << endl;
							}
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 2:
				  {
							string nif;
							clrscr();
							setcolor(7);
							cout << "Insira os dados necessarios: " << endl << endl;
							setcolor(8);
							cout << "NIF Contribuinte: ";
							cin >> nif;
							try
							{
								if (procura_passivo(Passivos_IVA, nif) >= 0)
									cout << procura_passivo(Passivos_IVA, nif) << endl;
							}
							catch (PassivoIVA::PassivoIVAInexistente p)
							{
								cout << "Sujeito passivo com o nif " << p.getNIF() << " inexistente." << endl;
							}
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 3:
				  {
							string nif;
							int dia;
							int mes;
							int ano;
							clrscr();
							setcolor(7);
							cout << "Insira os dados necessarios: " << endl << endl;
							setcolor(8);
							cout << "NIF Sujeito Passivo de IVA : ";
							cin >> nif;
							cout << "Data de Emissao da Fatura: " << endl;
							cout << "Dia: ";
							cin >> dia;
							cout << "Mes: ";
							cin >> mes;
							cout << "Ano : ";
							cin >> ano;

							try
							{
								if (procura_fatura(Faturas, nif, Date(ano, mes, dia)) >= 0)
									cout << procura_fatura(Faturas, nif, Date(ano, mes, dia)) << endl;
							}
							catch (Fatura::FaturaInexistente f)
							{
								cout << "Fatura do emissor com nif " << f.getNIF() << " e data ";
								f.getData();
								cout << " inexistente." << endl;
							}
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 4:
				  {
							string nif;
							int dia;
							int mes;
							int ano;
							clrscr();
							setcolor(7);
							cout << "Insira os dados necessarios: " << endl << endl;
							setcolor(8);
							cout << "NIF Sujeito Passivo de IVA : ";
							cin >> nif;
							cout << "Data de Emissao da Fatura: " << endl;
							cout << "Dia: ";
							cin >> dia;
							cout << "Mes: ";
							cin >> mes;
							cout << "Ano : ";
							cin >> ano;

							try
							{
								if (procura_declaracao(Passivos_IVA, nif, Date(ano, mes, dia)) >= 0)
									cout << procura_declaracao(Passivos_IVA, nif, Date(ano, mes, dia)) << endl;
							}
							catch (DeclIVA::DeclaracaoInexistente d)
							{
								cout << "A declaracao do contribuinte " << d.getNIF() << " do mes " << d.getDate().getMes() << " nao existe." << endl;
							}
							catch (PassivoIVA::PassivoIVAInexistente p)
							{
								cout << "Sujeito passivo com o nif " << p.getNIF() << " inexistente." << endl;
							}
							setcolor(7);
							cout << "Clique para continuar." << endl;
							system("pause");
							clrscr();
							break;
				  }
				  case 0:{ clrscr(); break; }
				  default:
					  break;
				  }
				  break;
		}
		case 6:
		{
				  write_contribuintes(Contribuintes);
				  write_passivos(Passivos_IVA);
				  write_faturas(Faturas);
				  clrscr();
				  break;
		}
		case 7:
		{
				running = false;
				break;
		}
		default:
			break;
		}
	}

	return 0;
}
