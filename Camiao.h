/*
 * Camiao.h
 */

#ifndef CAMIAO_H_
#define CAMIAO_H_

#include <string>
#include <iostream>

using namespace std;

class camioesIndisponiveis
{
public:
	/** \brief Lança a excepcao se nao houverem camioes disponiveis para o servico */
	camioesIndisponiveis(){}
};


class Camiao
{
protected:
	/** Indica a capacidade maxima do camiao */
	int capacidade;
	/**Indisca o tipo de transporte do camiao */
	string tipo;
	/** Indica a marca do camiao */
	string marca;
	/** Indica se o camiao se encontra disponviel para um novo servico */
	bool disponivel;
	/** Matricula que distingue os camioes */
	string matricula;
public:
	/**
	 * \brief Criacao de um Camiao por definicao
	 * \param Nao possui parametros
	 * \return Nao possui retorno
	 */
	Camiao();
	/**
	 * \brief Construtor que inicia um novo camiao
	 * \param marca Marca do camiao
	 * \param tipo Tipo de produto que o camiao transporta
	 * \param capacidade Carga maxima que o camiao pode utilizar no servico
	 * \param matricula Identificacao de cada camiao
	 * */
	Camiao(string marca, string tipo, int capacidade, string matricula);
	/**
	 * \brief Devolve o custo do camiao para um determinado servico, diferente para cada uma das classes derivadas
	 * \param dist Distancia do servico necessaria para calcular o preco
	 * \return Custo do camiao para esse servico
	 */
	virtual int getPreco(int dist);
	/**
	 * \brief Devolve a capacidade maxima do camiao, diferente para cada uma das classes diferentes
	 * \return Capacide maxima do camiao
	 */
	int getCapacidade();
	/**
	 * \brief Devolve o tipo do camiao
	 * \return Tipo do camiao
	 */
	string getTipo();
	/**
	 * \brief Devolve a marca do camiao
	 * \return Marca do camiao
	 */
	string getMarca();
	/**
	 * \brief Devolve em forma de T ou F se o camiao esta disponivel ou nao, respetivamente
	 * \return Boolenao acerca da disponibilidade do camiao
	 */
	bool getDisponivel();
	/**
	 * \brief Define a disponobilidade de um determinado camiao a partir do parametro bo
	 * \param bo Booleano que vai definir a proxima diponibilidade do camiao
	 */
	void setDisponivel( bool bo);
	/**
	 * \brief Devolve a matricula do camiao
	 * \return Matricula do camiao
	 */
	string getMatricula() const;
	/**
	 * \brief Imprime toda a informacao do camiao
	 */
	void imprimeCamiao() const;

};


class Normal: public Camiao
{
public:
	/**
	 * \brief Construtor para a criacao do tipo de camiao Normal
	 * \param marca Marca do camiao
	 * \param tipo Tipo de produto que o camiao transporta
	 * \param capacidade Carga maxima que o camiao pode utilizar no servico
	 * \param matricula Identificacao de cada camiao
	 */
	Normal(string marca, string tipo, int capacidade, string matricula);
	/**
	 * \brief Devolve o custo do camiao para um determinado servico
	 * \param dist Distancia do servico necessaria para calcular o preco
	 * \return Custo do camiao para esse servico
	 */
	int getPreco(int dist);
};

class Congelacao: public Camiao
{
public:
	/**
	 * \brief Construtor para a criacao do tipo de camiao Congelacao
	 * \param marca Marca do camiao
	 * \param tipo Tipo de produto que o camiao transporta
	 * \param capacidade Carga maxima que o camiao pode utilizar no servico
	 * \param matricula Identificacao de cada camiao
	 */
	Congelacao(string marca, string tipo, int capacidade, string matricula);
	/**
	 * \brief Devolve o custo do camiao para um determinado servico
	 * \param dist Distancia do servico necessaria para calcular o preco
	 * \return Custo do camiao para esse servico
	 */
	int getPreco (int dist);
};

class Perigosos: public Camiao
{
public:
	/**
	 * \brief Construtor para a criacao do tipo de camiao Perigosos
	 * \param marca Marca do camiao
	 * \param tipo Tipo de produto que o camiao transporta
	 * \param capacidade Carga maxima que o camiao pode utilizar no servico
	 * \param matricula Identificacao de cada camiao
	 */
	Perigosos(string marca, string tipo, int capacidade, string matricula);
	/**
	 * \brief Devolve o custo do camiao para um determinado servico
	 * \param dist Distancia do servico necessaria para calcular o preco
	 * \param nivelp Nivel de perigosidade do produto transportado no servico
	 * \return Custo do camiao para esse servico
	 */
	int getPreco(int dist, string nivelp);
};

class Animais: public Camiao
{
public:
	/**
	 * \brief Construtor para a criacao do tipo de camiao Animais
	 * \param marca Marca do camiao
	 * \param tipo Tipo de produto que o camiao transporta
	 * \param capacidade Carga maxima que o camiao pode utilizar no servico
	 * \param matricula Identificacao de cada camiao
	 */
	Animais(string marca, string tipo, int capacidade, string matricula);
	/**
	 * \brief Devolve o custo do camiao para um determinado servico
	 * \param dist Distancia do servico necessaria para calcular o preco
	 * \return Custo do camiao para esse servico
	 */
	int getPreco(int dist);
};


#endif /* CAMIAO_H_ */
