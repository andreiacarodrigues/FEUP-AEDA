#ifndef DEC_IVA_H
#define DEC_IVA_H

#include "Date.h"
#include "Fatura.h"

class DeclIVA
{
private:
	// Valor total da faturação mensal
	double total_faturacao_mensal;
	// Data da declaração
	Date data;
public:
	// Create Declaração

	/// Creates a DeclIVA (Constructor).
	/**
	 * @param valor The value of the total monthly billing.
	 * @param Data The Date of the declaration.
	 */
	DeclIVA(double valor, Date Data) { total_faturacao_mensal = valor; data = Data; }

	// Read Declaração

	/// Gets the total monthly billing.
	/**
	 * @return The value of the total monthly billing.
	 */
	double get_TFM() { return total_faturacao_mensal; };

	/// Gets the date.
	/**
	 * @return The Date of the declaration.
	 */
	Date get_Data() { return data; }

	// Update Declaração

	/// Sets the total monthly billing.
	/**
	 * @param valor The new value for the total monthly billing.
	 */
	void set_TFM(double valor) { total_faturacao_mensal = valor; }

	/// Sets the Date.
	/**
	 * @param Data The new Date for the declaration.
	 */
	void set_Data(Date Data) { data = Data; }

	// Print Declaração

	/// Prints the information(Date and total monthly billing) of the declaration (DeclIVA).
	void print() 
	{ 
		data.print();
		std::cout << std::endl << "Total da faturacao mensal: " << total_faturacao_mensal << std::endl << std::endl;
	}

	class DeclaracaoInvalida
	{
	private:
		double total_faturas;
		double montante = 0;
		std::vector<Fatura> faturas;
	public:
		DeclaracaoInvalida(double total_montante_faturas, double TFM, std::vector<Fatura> faturas_passivo) { total_faturas = total_montante_faturas; montante = TFM; faturas = faturas_passivo; }
		double get_total_faturas() { return total_faturas; }
		bool valorMenor() { if (total_faturas < montante) return 1; else return 0; }
		double valorEmFalta(){ return montante - total_faturas; }
		std::vector<Fatura> getFaturas() { return faturas; }
	};


	class DeclaracaoInexistente
	{
	private:
		std::string nif;
		Date d;
	public:
		DeclaracaoInexistente(std::string NIF, Date data) { nif = NIF; d = data; }
		std::string getNIF(){ return nif; }
		Date getDate() { return d; }

	};
};

#endif
