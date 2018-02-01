#ifndef DATA_H
#define DATA_H

#include <iostream>


//Excepção mes >12 e dia >31

class Date
{
private:
	unsigned int ano;
	unsigned int mes;
	unsigned int dia;
public:
	// Create Date

	/// Creates an empty Date (Default Constructor).
	Date() {};

	/// Creates a Date (Constructor).
	/**
	 * @param Ano The year of the date.
	 * @param Mes The month of the date.
	 * @param Dia The day of the date.
	 */
	Date(int Ano, int Mes, int Dia) { ano = Ano; mes = Mes; dia = Dia; }

	// Read Date

	/// Gets this Date.
	/**
	 * @return This Date.
	 */
	Date getData() { return *this; }

	/// Gets the year.
	/**
	 * @return The year of the Date.
	 */
	unsigned int getAno() { return ano; }

	/// Gets the month.
	/**
	 * @return The month of the Date.
	 */
	unsigned int getMes() { return mes; }

	/// Gets the day.
	/**
	 * @return The day of the Date.
	 */
	unsigned int getDia() { return dia; }

	// Update Date

	/// Sets this Date as a new one.
	/**
	 * @param Ano The new year for the Date.
	 * @param Mes The new month for the Date.
	 * @param Dia The new day for the Date.
	 */
	void setData(unsigned int Ano, unsigned int Mes, unsigned int Dia) { ano = Ano; mes = Mes; dia = Dia; }

	/// Sets only the year of the Date.
	/**
	 * @param Ano The new year for the Date.
	 */
	void setAno(unsigned int Ano) { ano = Ano; }

	/// Sets only the month of the Date.
	/**
	 * @param Mes The new month for the Date.
	 */
	void setMes(unsigned int Mes) { mes = Mes; }

	/// Sets only the day of the Date.
	/**
	 * @param Dia The new day for the Date.
	 */
	void setDia(unsigned int Dia) { dia = Dia; }

	// Print Date

	/// Prints the Date in the form of "day/month/year".
	void print()
	{
		std::cout << dia << "/" << mes << "/" << ano;
	}
};

#endif
