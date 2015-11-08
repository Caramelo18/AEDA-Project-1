/*
 * Servico.cpp
 */

#include "Servico.h"

int Servico::globalID = 1;


Servico::Servico()
{

}


Servico::Servico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, vector<Camiao *> &c , vector<Funcionario *> &f)
{
	unsigned int i = 0;

	int cap = capacidade;
	while(capacidade > 0 && i < c.size())
	{
		if (c[i]->getTipo() == tipo_produto && c[i]->getDisponivel())
		{
			capacidade = capacidade - c[i]->getCapacidade();
			Camioes.push_back(c[i]);
			if (origem != "abcd") // para pedir o orcamento arbitra-se um a origem "abcd"
				c[i]->setDisponivel(false);
		}
		i++;
	}

	if (capacidade > 0)
		throw camioesIndisponiveis();

	unsigned int funcsdisp = 0;
	for (unsigned int i = 0; i < f.size(); i++)
		if(f[i]->getDisponivel())
			funcsdisp++;

	if (funcsdisp < Camioes.size())
		throw FuncionariosIndisponiveis();

	unsigned int funcness = Camioes.size();
	if (origem != "abcd")
	{
		for(unsigned int i = 0; i < Camioes.size(); i++)
			Camioes[i]->setDisponivel(false);
		ID = globalID++;
		for (unsigned int i = 0; i < f.size() && funcness > 0; i++)
		{
			if(f[i]->getDisponivel())
			{
				f[i]->setDisponibilidade(false);
				Funcionarios.push_back(f[i]);
				funcness--;
			}
		}
	}

	this->origem = origem;
	this->destino = destino;
	this->distancia = distancia;
	this->tipo_produto = tipo_produto;
	this->capacidade = cap;
	terminado = false;
	this->Nif=Nif;
	preco = 0;
	for (unsigned int i = 0; i < Camioes.size(); i++)
		preco = preco + Camioes[i]->getPreco(distancia);

}

Servico::Servico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, vector<Camiao *> &c, int temp, vector<Funcionario *> &f)
{
	unsigned int i = 0;
	int cap = capacidade;
	while(capacidade > 0 && i < c.size())
	{
		if (c[i]->getTipo() == tipo_produto && c[i]->getDisponivel())
		{
			capacidade = capacidade - c[i]->getCapacidade();
			Camioes.push_back(c[i]);
			if (origem != "abcd") // para pedir o orcamento arbitra-se um a origem "abcd"
				c[i]->setDisponivel(false);
		}
		i++;
	}

	if (capacidade > 0)
		throw camioesIndisponiveis();

	unsigned int funcsdisp = 0;
	for (unsigned int i = 0; i < f.size(); i++)
		if(f[i]->getDisponivel())
			funcsdisp++;

	if (funcsdisp < Camioes.size())
		throw FuncionariosIndisponiveis();

	unsigned int funcness = Camioes.size();
	if (origem != "abcd")
	{
		for(unsigned int i = 0; i < Camioes.size(); i++)
			Camioes[i]->setDisponivel(false);
		ID = globalID++;
		for (unsigned int i = 0; i < f.size() && funcness > 0; i++)
		{
			if(f[i]->getDisponivel())
			{
				f[i]->setDisponibilidade(false);
				Funcionarios.push_back(f[i]);
				funcness--;
			}
		}
	}

	this->origem = origem;
	this->destino = destino;
	this->distancia = distancia;
	this->tipo_produto = tipo_produto;
	this->capacidade = cap;
	terminado = false;
	this->Nif=Nif;
	preco = 0;
	for (unsigned int i = 0; i < Camioes.size(); i++)
	{
		double dif = 20 - temp;
		dif = dif / 10;
		preco += (6 + dif) * distancia;
	}
}

Servico::Servico(string origem, string destino, int distancia, string tipo_produto, int capacidade, unsigned long Nif, vector<Camiao *> &c, string nivel_p, vector<Funcionario *> &f)
{
	unsigned int i = 0;

	int cap = capacidade;
	while(capacidade > 0 && i < c.size())
	{
		if (c[i]->getTipo() == tipo_produto && c[i]->getDisponivel())
		{
			capacidade = capacidade - c[i]->getCapacidade();
			Camioes.push_back(c[i]);
			if (origem != "abcd") // para pedir o orcamento arbitra-se um a origem "abcd"
				c[i]->setDisponivel(false);
		}
		i++;
	}

	if (capacidade > 0)
		throw camioesIndisponiveis();

	unsigned int funcsdisp = 0;
	for (unsigned int i = 0; i < f.size(); i++)
		if(f[i]->getDisponivel())
			funcsdisp++;

	if (funcsdisp < Camioes.size())
		throw FuncionariosIndisponiveis();

	unsigned int funcness = Camioes.size();
	if (origem != "abcd")
	{
		for(unsigned int i = 0; i < Camioes.size(); i++)
			Camioes[i]->setDisponivel(false);
		ID = globalID++;
		for (unsigned int i = 0; i < f.size() && funcness > 0; i++)
		{
			if(f[i]->getDisponivel())
			{
				f[i]->setDisponibilidade(false);
				Funcionarios.push_back(f[i]);
				funcness--;
			}
		}
	}


	this->origem = origem;
	this->destino = destino;
	this->distancia = distancia;
	this->tipo_produto = tipo_produto;
	this->capacidade = cap;
	terminado = false;
	this->Nif=Nif;
	preco = 0;
	for (unsigned int i = 0; i < Camioes.size(); i++)
	{
		if (nivel_p == "inflamavel")
			preco += 7 * distancia;
		else if (nivel_p == "toxica")
			preco += 8 * distancia;
		else if (nivel_p == "corrosiva")
			preco += 7.5 * distancia;
		else if (nivel_p == "radioactiva")
			preco += 9 * distancia;
	}
}

string Servico::getOrigem()const
{
	return origem;
}

vector<Camiao*> Servico::getCamioes()
{
	return Camioes;
}

string Servico::getDestino()const
{
	return destino;
}


int Servico::getDistancia()const
{
	return distancia;
}

string Servico::getTipo_produto()const
{
	return tipo_produto;
}

bool Servico::getTerminado()const
{
	return terminado;
}

int Servico::getCapacidade()const
{
	return capacidade;
}

unsigned long Servico::getNif()const
{
	return Nif;
}


void Servico::termina_servico()
{
	for(unsigned int i=0; i <Camioes.size(); i++)
		Camioes[i]->setDisponivel(true);

	for(unsigned int i=0; i < Funcionarios.size(); i++)
		Funcionarios[i]->setDisponibilidade(true);

	terminado = true;
}

bool Servico::operator < (const Servico &Ser)const
{
	if (distancia < Ser.getDistancia())
		return true;

	if(distancia == Ser.getDistancia())
	{
		if(capacidade < Ser.getCapacidade())
			return true;
		else
			return false;
	}
	else return false;
}

void Servico::incGlobalID()
{
	globalID++;
}

int Servico::getPreco() const
{
	return preco;
}

int Servico::getID() const
{
	return ID;
}

vector<Funcionario*> Servico::getFuncionarios()
{
	return Funcionarios;
}
