#ifndef CONTRIBUINTES_H
#define CONTRIBUINTES_H

#include <string>
#include <vector>

#include "DecIVA.h"

class Contribuinte
{
protected:
	/// NIF of the Contribuinte
	//Número de identificação fiscal
	std::string NIF;
	/// Name of the Contribuinte
	std::string nome;
	/// Email of the Contribuinte
	std::string email;
	/// Address of the Contribuinte
	std::string morada_fiscal;
public:
	/// Creates a Contribuinte (Constructor).
	/**
	 * @param nif NIF of the Contribuinte.
	 * @param Nome Name of the Contribuinte.
	 * @param Email Email of the Contribuinte.
	 * @param Morada_Fiscal Address of the Contribuinte.
	 */
	Contribuinte(std::string nif, std::string Nome, std::string Email, std::string Morada_Fiscal)
	{
		NIF = nif; nome = Nome; email = Email; morada_fiscal = Morada_Fiscal;
	}

	// Read Contribuinte

	/// Gets the NIF.
	/**
	 * @return The NIF of the Contribuinte.
	 */
	std::string getNIF() { return NIF; }

	/// Gets the name.
	/**
	 * @return The Name of the Contribuinte.
	 */
	std::string getNome() { return nome; }

	/// Gets the Email.
	/**
	 * @return The Email of the Contribuinte.
	 */
	std::string getEmail() { return email; }

	/// Gets the address.
	/**
	 * @return The Address of the Contribuinte.
	 */
	std::string getMF() { return morada_fiscal; }

	// Update Contribuinte

	/// Sets the NIF of the Contribuinte.
	/**
	 * @param nif The new nif of the Contribuinte.
	 */
	void setNIF(std::string nif) { NIF = nif; }

	/// Sets the name of the Contribuinte.
	/**
	 * @param Nome The new name of the Contribuinte.
	 */
	void setNome(std::string Nome) { nome = Nome; }

	/// Sets the Email of the Contribuinte.
	/**
	 * @param nif The new Email of the Contribuinte.
	 */
	void setEmail(std::string Email) { email = Email; }

	/// Sets the address of the Contribuinte.
	/**
	 * @param Morada_Fiscal The new address of the Contribuinte.
	 */
	void setMF(std::string Morada_Fiscal) { morada_fiscal = Morada_Fiscal; }

	// Print Contribuinte

	/// Prints the informantion(NIF, name, Email and Address) of the Contribuinte on the screen.
	virtual void print()
	{
		std::cout << "NIF: " << NIF << std::endl;
		std::cout << "Nome: " << nome << std::endl;
		std::cout << "Email: " << email << std::endl;
		std::cout << "Morada Fiscal: " << morada_fiscal << std::endl << std::endl;
	}

	// Validação

	/// Checks if a NIF is valid.
	/**
	 * @return false if the NIF is not valid.
	 * @return true if the NIF is valid.
	 */
	bool isValid()
	{
		if (NIF.size() != 9) return false;

		std::vector<int> nr;
		for (unsigned int i = 0; i < 9; i++)
			nr.push_back((int)NIF[i] - 48);

		for (unsigned int i = 0; i < 9; i++)
			if (nr[i] < 0 || nr[i] > 9)
				return false;

		long verifica = (nr[0] * 9 + nr[1] * 8 + nr[2] * 7 + nr[3] * 6 + nr[4] * 5 + nr[5] * 4 + nr[6] * 3 + nr[7] * 2) % 11;
		long controlo = nr[8];

		if (verifica == 0 || verifica == 1)
		{
			if (controlo == 0)
				return true;
			else
				return false;
		}

		if (11 - verifica != controlo) 
			return false;
		else
			return true;
	}

	// Excepção
	class NIF_Invalido
	{
	private:
		std::string NIF;
	public:
		NIF_Invalido(std::string nif) { NIF = nif; }
		std::string getNIF() { return NIF; }
	};

	class ContribuinteJaExistente
	{
	public:
		ContribuinteJaExistente() {}

	};

	class ContribuinteInexistente
	{
	private:
		std::string NIF;
	public:
		ContribuinteInexistente(std::string nif) { NIF = nif; }
		std::string getNIF() { return NIF; }
	};
};

class PassivoIVA : public Contribuinte
{
private:
	/// Classificação de actividades económicas
	int CAE;
	/// Declarações por ele emitidas
	std::vector<DeclIVA> declaracoes;
public:
	/// Creates a PassivoIVA(Constructor).
	/**
	 *
	 *
	 * @param nif NIF of the Contribuinte.
	 * @param Nome Name of the Contribuinte.
	 * @param Email Email of the Contribuinte.
	 * @param Morada_Fiscal Address of the Contribuinte.
	 * @param CAE CAE of the Contribuinte.
	 */
	PassivoIVA(std::string nif, std::string Nome, std::string Email, std::string Morada_Fiscal, int cae) : Contribuinte(nif, Nome, Email, Morada_Fiscal) { CAE = cae; }

	// Read Contribuinte

	/// Gets the CAE.
	/**
	 * @return CAE of the PassivoIVA.
	 */
	int getCAE() { return CAE; }
	///  Gets the vector of declarations.
	/**
	 * @return declaracoes of the PassivoIVA.
	 */
	std::vector<DeclIVA> getDeclaracoes() { return declaracoes; }

	// Update Contribuinte

	/// Sets the CAE.
	/**
	 * @param cae The new CAE of the PassivoIVA.
	 */
	void setCAE(int cae) { CAE = cae; }

	/// Sets the vector declaracoes
	/*
	 * @param decs The new vector declaracoes of the PassivoIVA
	 */
	void setDeclaracoes(std::vector<DeclIVA> decs) { declaracoes = decs; }

	// Print Contribuinte

	/// Prints the informantion(NIF, name, Email, Address and CAE) of the PassivoIVA on the screen.
	void print()
	{
		std::cout << "NIF: " << NIF << std::endl;
		std::cout << "Nome: " << nome << std::endl;
		std::cout << "Email: " << email << std::endl;
		std::cout << "Morada Fiscal: " << morada_fiscal << std::endl;
		std::cout << "CAE: " << CAE << std::endl << std::endl;
	}

	class PassivoIVAInexistente
	{
	private:
		std::string NIF;
	public:
		PassivoIVAInexistente(std::string nif) { NIF = nif; }
		std::string getNIF() { return NIF; }
	};
};

#endif
