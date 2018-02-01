#ifndef LIST_MANIPULATION_H
#define LIST_MANIPULATION_H

#include <fstream>
#include <sstream>

#include "Contribuinte.h"
#include "Fatura.h"
#include "DecIVA.h"

// Ficheiros Write

void write_contribuintes(std::vector<Contribuinte*> &cVec);

void write_passivos(std::vector<PassivoIVA> &pVec);

void write_faturas(std::vector<Fatura> &fVec);

// Ficheiros Load

void load_contribuintes(std::vector<Contribuinte*> &cVec);

void load_passivos(std::vector<Contribuinte*> &cVec, std::vector<PassivoIVA> &pVec, std::vector<Fatura> &fVec);

void load_faturas(std::vector<Contribuinte*> &cVec, std::vector<PassivoIVA> &pVec, std::vector<Fatura> &fVec);

// Pesquisa

//Pesquisa todas as faturas de um certo emissor num certo mês
std::vector<Fatura> faturas_emissor_mes(std::vector<Fatura> &fVec, std::string NIF, Date data);
std::vector<Fatura> Faturas_Emissor_Mes(std::vector<Fatura> &fVec, std::string NIF, Date data);

//Pesquisa todas as faturas de um certo emissor
std::vector<Fatura> faturas_emissor(std::vector<Fatura> &fVec, std::string NIF);

//Pesquisa todas as declaracoes de um certo sujeito passivo de iva
std::vector<DeclIVA> declaracoes_sujeito_passivo(std::vector<PassivoIVA> &pVec, std::string NIF);

int procura_contribuinte(std::vector<Contribuinte*> &cVec, std::string NIF);
int procura_passivo(std::vector<PassivoIVA> &pVec, std::string NIF);
int procura_fatura(std::vector<Fatura> &fVec, std::string NIF, Date data);
int procura_declaracao(std::vector<PassivoIVA> &pVec, std::string NIF, Date data);


// Adições

// Adiciona um novo contribuinte se este for válido
void add_contribuinte(std::vector<Contribuinte*> &cVec, Contribuinte * c);

// Adiciona um novo passivo de IVA se este for válido
void add_passivo(std::vector<Contribuinte*> &cVec, std::vector<PassivoIVA> &pVec, PassivoIVA * p);

// Adiciona uma nova fatura se esta for válida
void add_fatura(std::vector<Contribuinte*> &cVec, std::vector<PassivoIVA> &pVec, std::vector<Fatura> &fVec, Fatura &f);

// Adiciona uma nova declaração se esta for válida
void add_declaracao(std::vector<PassivoIVA> &pVec, std::vector<Fatura> &fVec, PassivoIVA p, DeclIVA d);


//Remocoes

void retira_contribuinte(std::vector<Contribuinte*> &cVec, std::string NIF);

void retira_passivo(std::vector<Contribuinte*> &cVec, std::vector<PassivoIVA> &pVec, std::string NIF);

void remove_faturas(std::vector<Fatura> &fVec, std::string NIF);

// Sorts

void ordena_faturas_NIF_Emi(std::vector<Fatura> &fVec);
void ordena_faturas_montante(std::vector<Fatura> &fVec);
void ordena_contribuintes_NIF(std::vector<Contribuinte * > &cVec);
void ordena_contribuintes_nome(std::vector<Contribuinte * > &cVec);
void ordena_passivos_NIF(std::vector<PassivoIVA> &pVec);
void ordena_passivos_nome(std::vector<PassivoIVA> &pVec);

#endif
