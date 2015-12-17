/*
 * Oficina.h
 */

#ifndef OFICINA_H_
#define OFICINA_H_

#include <string>
#include <iostream>

using namespace std;

class Oficina
{
public:
	/** \brief Criacao de uma Oficina por definicao
	    \param Nao possui parametros
		\return Nao possui retorno
	 */
	Oficina();

	/**
	 * \brief Construtor de uma Oficina
	 * \param nome Nome da Oficina
	 * \param marca Marca da Oficina criada
	 * \param disp tempo que a Oficina demora a ficar disponivel
	 *
	 */
	Oficina(string nome, string marca, int disp);
	/**
	 * \brief Retorna o nome da Oficina
	 * \return nome Nome da Oficina
	 */
	string getNome()const;
	/**
	 * \brief Retorna a marca da Oficina
	 * \return marca Marca da Oficina
	 */
	string getMarca()const;
	/**
	 * \brief Retorna a disponibilidade da Oficina
	 * \return disp Disponibilidade da Oficina
	 */
	int getDisp()const;
	/**
	 * \brief Overload do operador < entre oficinas para a comparacao das mesmas
	 * \param F Oficina com o qual vais fazer a comparacao
	 * \return Retorna em forma de booleano se a oficina e ou nao menor que a Oficina F
	 *  */
	bool operator <(const Oficina F)const;

private:
	/** Nome da Oficina */
	string nome;
	/** Marca da Oficina */
	string marca;
	/** Disponibilidade da Oficina */
	int disp;

};
#endif /* OFICINA_H_ */
