/*
 * Servico.h
 */

#ifndef SERVICO_H_
#define SERVICO_H_

#include "Camiao.h"
#include "Funcionario.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Servico
{
public:
	/** \brief Criacao de um Servico por definicao
	    \param Nao possui parametros
		\return Nao possui retorno
	 */
	Servico();
	/**   \brief Criacao de um Servico para um camiao do tipo Normal e Animais
		  \param origem Origem do servico
		  \param destino Destino do servico
		  \param distancia Distancia total do servico
		  \param tipo_produto Tipo de produto a transportar
		  \param quantidade Quantidade de produto a transportar
		  \param Nif Nif do Cliente que encomendou o servico
		  \param c Camioes que se encontram a executar o servico
		  \param f Funcionarios que se encontram a executar o servico

		  \return Nao possui retorno
	*/
	Servico(string origem, string destino, int distancia, string tipo_produto, int quantidade, unsigned long Nif, vector<Camiao *> &c, vector<Funcionario *> &f);
	/** \brief Criacao de um Servico para um camiao do tipo Congelacao
		 * \param origem Origem do servico
		 * \param destino Destino do servico
		 * \param distancia Distancia total do servico
		 * \param tipo_produto Tipo de produto a transportar
		 * \param quantidade Quantidade de produto a transportar
		 * \param Nif Nif do Cliente que encomendou o servico
		 * \param c Camioes que se encontram a executar o servico
		 * \param temp Temperatura necessaria no transporte no produto
		 * \param f Funcionarios que se encontram a executar o servico
		 *
		 * \return Nao possui retorno
		 */
	Servico(string origem, string destino, int distancia, string tipo_produto, int quantidade, unsigned long Nif, vector<Camiao *> &c, int temp, vector<Funcionario *> &f);
	/**
	 * \brief Criacao de um Servico para um camiao do tipo Perigosos
		 * \param origem Origem do servico
		 * \param destino Destino do servico
		 * \param distancia Distancia total do servico
		 * \param tipo_produto Tipo de produto a transportar
		 * \param quantidade Quantidade de produto a transportar
		 * \param Nif Nif do Cliente que encomendou o servico
		 * \param c Camioes que se encontram a executar o servico
		 * \param nivel_p Nivel de perigosidade do produto
		 * \param f Funcionarios que se encontram a executar o servico
		 *
		 * \return Nao possui retorno
		 */
	Servico(string origem, string destino, int distancia, string tipo_produto, int quantidade, unsigned long Nif, vector<Camiao *> &c, string nivel_p, vector<Funcionario *> &f);
	/**\brief Retorna a Origem do produto
		 * \param Nao possui parametros
		 *
		 * \return Origem do produto
		 */
	string getOrigem()const;
	/**\brief Retorna o Destino do produto
		 * \param Nao possui parametros
		 *
		 * \return Destino do produto
		 */
	string getDestino()const;
	/**\brief Retorna a Distancia da viagem
		 * \param Nao possui parametros
		 *
		 * \return Distancia do produto
		 */
	int getDistancia()const;
	 /**\brief Retorna o Tipo de produto
		 * \param Nao tem parametros
		 *
		 * \return Tipo de produto
		 */
	string getTipo_produto()const;
	/**\brief Verifica se o servico esta terminado ou nao
		 * \param Nao tem parametros
		 *
		 * \return Servico terminado ou em execucao
		 */
	bool getTerminado()const;
	/** Retorna a Capacidade do produto
		 * \param Nao tem parametros
		 *
		 * \return Capacidade do produto
		 */
	int getCapacidade()const;
	/**\brief Retorna o Nif do produto
		 * \param Nao tem parametros
		 *
		 * \return Nif do produto
		 */
	unsigned long getNif()const;
	/** \brief Termina o servico e actualiza todo o vetor de camioes, pondo desocupado os camioes que estao em veiculos ocupados
		 * \param Nao possui parametros
		 *
		 * \return Nao possui retorno
		 */
	void termina_servico();
	/** \brief Compara dois servicos e diz se o primeiro e mais pequeno que o segundo, um servico e mais pequeno que o outro se a sua distancia for menor ou se esta for igual, qual delas usufrui de menos capacidade
	 * \param Ser Servico com o qual o primeiro vai ser comparado
		 *
		 * \return Retornaa veracidade acerca de o servico ser mais pequeno que o que recebe como argumento
		 */
	bool operator < (const Servico &Ser)const;
	/**
	 * \brief Retorna os camioes utilizados no servico
		 * \param Nao possui parametros
		 *
		 * \return Camioes utilizados no servico
		 */
	vector<Camiao*> getCamioes();
	/**\brief Retorna os funcionarios que executraram o servico
		 * \param Nao possui parametros
		 *
		 * \return Funcionarios que executraram o servico
		 */
	vector<Funcionario*> getFuncionarios();
	/** \brief Devolve o preco para um determinado servico
		 * \param Nao possui parametros
		 *
		 * \return Preco do servico a executar
		 */
	int getPreco() const;
	/**\brief Retorna o ID do servico
		 * \param Nao possui parametros
		 *
		 * \return ID que identifica o servico
		 */
	int getID() const;
	/**\brief Incrementa o ID global de maneira a que os ids surjam de forma sequencial
		 * \param Nao possui parametros
		 *
		 * \return Nao possui retorno
		 */
	static void incGlobalID();

private:
	/** Variavel estatica que permite incrementar de uma forma sequencial o ID dos servicos*/
	static int globalID;
	/** ID do servico */
	int ID;
	/** Vetor de camioes que executam o servico */
	vector<Camiao*> Camioes;
	/** Vetor de funcionarios que executam o servico */
	vector<Funcionario*> Funcionarios;
	/** Origem do servico */
	string origem;
	/** Destino do servico */
	string destino;
	/** Distancia da viagem */
	int distancia;
	/** Carga utilizada no total do servico */
	int capacidade;
	/** Tipo de produto transportado no servico */
	string tipo_produto;
	/** Variavel que define se o servico esta terminado ou nao */
	bool terminado;
	/** Variavel que identifica o cliente que encomendou o servico atraves do nif */
	unsigned long Nif;
	/** Custo do servico executado */
	int preco;

};


#endif /* SERVICO_H_ */
