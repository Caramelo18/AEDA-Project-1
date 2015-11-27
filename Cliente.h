/*
 * Cliente.h
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <iostream>
#include <string>

using namespace std;


class Cliente
{
public:
	/**
	 * \brief Criacao do cliente
	 * \param Nome Nome do cliente
	 * \param Nif Nif do cliente, usado para distinguir os clientes
	 */
	Cliente(string Nome,unsigned long Nif);
	/**
	 * \brief Devolve o Nome do cliente
	 * \return Nome do cliente
	 */
	string getNome()const;
	/**
	 * \brief Devolve o Nif do cliente
	 * \return Nif do cliente
	 */
	unsigned long getNif()const;
	/**
	 * \brief Overload do operador < entre clientes para a comparacao dos mesmos
	 * \param Cli Cliente com o qual vais fazer a comparacao
	 * \return Retorna em forma de booleano se o cliente e ou nao menor que o Cliente Cli
	 */
	bool operator <(const Cliente &Cli)const;
	/**
	 * \brief Overload do operador == para comparar se os Clientes sao a mesma pessoa
	 * \param c Cliente com o qual o Cliente pricipal vai ser comparado
	 * \return Retorna em forma de booleano se os Clientes sao a mesma pessoa
	 */
	bool operator ==(const Cliente &c)const;

	void setNome(string nome);

	void setNif(unsigned long nif);
protected:
	/** Nome do Cliente */
	string Nome;
	/** Nif e forma de identificacao do Cliente */
	unsigned long Nif;
};

#endif /* CLIENTE_H_ */
