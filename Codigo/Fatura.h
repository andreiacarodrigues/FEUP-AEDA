#ifndef FATURA_H
#define FATURA_H

#include "Date.h"

class Fatura
{
private:
	// ID
	int ID = 0;
	// Data de emissão
	Date data;
	// NIF do emissor
	std::string NIF_emissor;
	// NIF do consumidor
	std::string NIF_consumidor;
	// Valor pago
	double valor_pago;
	// Taxa de IVA associada
	double regime_iva;
public:
	// Create Declaração

	/// Creates a Fatura (Constructor).
	/**
	 * @param Data The Date of the declaration.
	 * @param ne The emissor NIF.
	 * @param nc The consumer NIF.
	 * @param vp The paid value.
	 * @param ri The IVA regime.
	 */
	Fatura(Date Data, std::string ne, std::string nc, double vp, double ri)
	{
		data = Data; NIF_emissor = ne; NIF_consumidor = nc; valor_pago = vp; regime_iva = ri;
	}

	// Read Declaração

	/// Gets the ID.
	/**
	 * @return The ID of the bill.
	 */
	int getID() { return ID; }

	/// Gets the Date.
	/**
	 * @return The date of the bill.
	 */
	Date getData() { return data; }

	/// Gets the emissor NIF.
	/**
	 * @return The NIF of the emissor of the bill.
	 */
	std::string getNIF_Emi() { return NIF_emissor; }

	/// Gets the consumer NIF.
	/**
	 * @return The NIF of the consumer of the bill.
	 */
	std::string getNIF_Cons() { return NIF_consumidor; }

	/// Gets the paid value.
	/**
	 * @return The value paid in the bill.
	 */
	double getValor_Pago() { return valor_pago; }

	/// Gets the IVA regime.
	/**
	 * @return The IVA regime of the bill.
	 */
	double getRegime_IVA() { return regime_iva; }

	// Update Declaração

	/// Sets the ID.
	/**
	 * @param id The new ID of the bill.
	 */
	void setID(int id) { ID = id; }

	/// Sets the Date.
	/**
	 * @param Data The new date of the bill.
	 */
	void setData(Date Data) { data = Data; }

	/// Sets the emissor NIF.
	/**
	 * @param ne The new NIF of the emissor of the bill.
	 */
	void setNIF_Emi(std::string ne) { NIF_emissor = ne; }

	/// Sets the consumer NIF.
	/**
	 * @param nc The new NIF of the consumer of the bill.
	 */
	void setNIF_Cons(std::string nc) { NIF_consumidor = nc; }

	/// Sets the paid value.
	/**
	 * @param vp The new value paid in the bill.
	 */
	void setValor_Pago(double vp) { valor_pago = vp; }

	/// Sets the IVA regime(TAX).
	/**
	 * @param ri The new IVA regime for the bill.
	 */
	void setRegime_IVA(double ri) { regime_iva = ri; }

	// Print Declaração
	/// Prints the information(ID, date, emissor NIF, consumer NIF, paid value and IVA regime) of the bill (Fatura) in the screen.
	void print()
	{
		std::cout << "ID: " << ID << std::endl;
		std::cout << "Data: "; data.print(); std::cout << std::endl;
		std::cout << "NIF do emissor: " << NIF_emissor << std::endl;
		std::cout << "NIF do consumidor: " << NIF_consumidor << std::endl;
		std::cout << "Valor pago: " << valor_pago << std::endl;
		std::cout << "Regime de IVA: " << regime_iva << std::endl << std::endl;
	}

	class FaturaInexistente
	{
	private:
		std::string nif;
		Date d;
	public:
		FaturaInexistente(std::string NIF, Date data) { nif = NIF; d = data; }
		std::string getNIF() { return nif; }
		void getData() { d.print(); }
	};

	class FaturasInexistentes
	{
	private:
		std::string nif;
	public:
		FaturasInexistentes(std::string NIF){ nif = NIF; }
		std::string getNIF() { return nif; }
	};

	class MontanteInvalido
	{
	public:
		MontanteInvalido(){}
	};
	
	class NIFInvalido
	{
	public:
		NIFInvalido() {};
	};
};

#endif
