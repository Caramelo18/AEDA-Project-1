/*
 * Oficina.h
 */

#ifndef OFICINA_H_
#define OFICINA_H_

#include <string>
#include <iostream>
#include "Camiao.h"

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
	 * \param C Camiao que vai receber o servico da oficina
	 *
	 */
	Oficina(string nome, string marca, int disp, string matriculaCami);
	/**
	 * \brief Retorna o nome da Oficina
	 * \return nome Nome da Oficina
	 */
	string getNome()const;

	/*
	 * \brief Retorna a marca da Oficina
	 *
	 * \return marca Marca da Oficina
	 */
	string getMarca()const;

	/*
	 * \brief Retorna a disponibilidade da Oficina
	 *
	 * \return disp Disponibilidade da Oficina
	 */
	int getDisp()const;

	/*
	 * \brief Retorna a matricula do camiao que esta na oficina
	 *
	 * \return matriculaCami matricula do camiao que esta na oficina
	 */
	string getMatri()const;

	/*
	 * \brief Overload do operador < entre oficinas para a comparacao das mesmas
	 * \param F Oficina com o qual vais fazer a comparacao
	 *
	 * \return Retorna em forma de booleano se a oficina e ou nao menor que a Oficina F
	 */
	bool operator <(const Oficina F)const;

	/*
	 * \brief realiza o servico ao camiao de matricula Matri , adicionando a disponibilidade e agregando a Matri a oficina
	 * \param Matri camiao de matricula Matri que vai receber o servico
	 *
	 * \return Nao possui retorno
	 */
	void fazServico(string Matri);

	/*
	 * \brief termina o servico da oficina ficando a disponibilidade a zero e sem matriculas associadas
	 *
	 * \return Nao possui retorno
	 */
	void termServico();

	friend ostream & operator<<(ostream & s, const Oficina  F);

private:
	/** Nome da Oficina */
	string nome;
	/** Marca da Oficina */
	string marca;
	/** Disponibilidade da Oficina */
	int disp;
	/** Matricula do camiao que esta na oficina */
	string matriculaCami;

};
#endif /* OFICINA_H_ */
