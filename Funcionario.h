/*
 * Funcionario.h
 */

#ifndef FUNCIONARIO_H_
#define FUNCIONARIO_H_

#include <string>
#include <iostream>

using namespace std;

class FuncionariosIndisponiveis
{
public:
	/**
	 * \brief Construtor para lancar a excepcao de funcionarios insuficientes para executar o determinado Servico
	 */
	FuncionariosIndisponiveis() {}
};


class Funcionario
{
private:
	/** Nome do Funcionario */
	string nome;
	/** Salario do Funcionario */
	int salario;
	/** BI que identifica o Funcionario */
	unsigned long BI;
	/** Booleano que define se o funcionario esta disponivel ou nao */
	bool disponivel;
	/** Horas diarias de um funcionario */
	unsigned int horas;
public:
	Funcionario();
	/**
	 * \brief Construtor que cria o novo Funcionario
	 * \param nome Nome do Funcionario
	 * \param salario Vencimento mensal do Funcionario
	 * \param BI Numero de identificacao do Funcionario
	 * \param disp Disponibilidade do funcionario para executar o servico
	 */
	Funcionario(string nome, int salario, unsigned long BI, string disp);
	/**
	 * \brief Retorna o nome do Funcionario
	 * \return Nome do Funcionario
	 */
	string getNome() const;
	/**
	 * \brief Retorna o salario do Funcionario
	 * \return Salario do Funcionario
	 */
	int getSalario() const;
	/**
	 * \brief Define o Salario do funcionario
	 * \param salario Novo salario do Funcionario
	 */
	void setSalario(int salario);
	/**
	 * \brief Retorna o BI do Funcionario
	 * \return Numero de identificacao do Funcionario
	 */
	unsigned int getBI() const;
	/**
	 * \brief Retorna um booleano em se o Funcionario esta ou nao disponivel para executar um novo servico
	 * \return Disponibilidade do Funcionario
	 */
	bool getDisponivel() const;

	unsigned int getHoras() const;

	/**
	 * \brief Define a disponibilidade do Funcionario
	 * \param disp Booleano para o qual vai ser alterada a disponibilidade do Funcionario
	 */
	void setDisponibilidade(bool disp);
	/**
	 * \brief Funcao que imprime as informacoes do Funcionario
	 */
	void imprimeFuncionario() const;

	bool operator<(Funcionario f);

	void incrementaHoras(int distancia);
};

#endif /* FUNCIONARIO_H_ */
