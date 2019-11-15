#include "particle.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <exception>
#include <QObject>
#include <QDebug>

using namespace std;

//int Particle::numberOfVariables = 1;
//�õľ�ָ̬�� Ҫ���ⲿ����
const double *Particle::lowerBounds = nullptr;

const double *Particle::upperBounds = nullptr;

const double *Particle::maxVelocity = nullptr;

double Particle::c1 = 2;

double Particle::c2 = 2;

const double *Particle::weight = nullptr;

const double *Particle::vari = nullptr;

void(*Particle::functionPtr) (Particle *);

Particle::Particle(int _numberOfVariables,
	int _numberOfObjectives,
	const double *_lowerBounds,
	const double *_upperBounds,
	const double *_vmax,
	double _c1, double _c2,
	const double *_weight, 
	const double *_vari,
    void(*_functionPtr)(Particle *),
    QStringList _optimizeMode)
{
    optimizeMode = _optimizeMode;

	lowerBounds = _lowerBounds;
	upperBounds = _upperBounds;

	numberOfVariables = _numberOfVariables;
	numberOfObjectives = _numberOfObjectives;

	if (numberOfVariables <= 0)
		throw "Number of variables can't be less or equal than zero.";
	if (numberOfObjectives <= 0)
		throw "Number of objectives can't be less or equal than zero.";

	c1 = _c1;
	c2 = _c2;
	weight = _weight;
	vari = _vari;
	functionPtr = _functionPtr;
	maxVelocity = _vmax;

    position = new double[static_cast<unsigned long long>(numberOfVariables)];
    velocity = new double[static_cast<unsigned long long>(numberOfVariables)];
    bestPosition = new double[static_cast<unsigned long long>(numberOfVariables)];
    value = new double[static_cast<unsigned long long>(numberOfObjectives)];
    bestValue = new double[static_cast<unsigned long long>(numberOfObjectives)];

	inicializeParticle();
}

Particle::Particle(const Particle& str)
{
	//��������
	numberOfVariables=str.numberOfVariables;
	//�Ż�Ŀ�����
	numberOfObjectives=str.numberOfObjectives;
	//����λ��
    position = new double[static_cast<unsigned long long>(numberOfVariables)];
	//�����ٶ�
    velocity = new double[static_cast<unsigned long long>(numberOfVariables)];
	//�������λ��
    bestPosition = new double[static_cast<unsigned long long>(numberOfVariables)];
	//λ���ٶȸ���
	for (int i = 0; i < numberOfVariables; i++) {
		position[i] = str.position[i];
		velocity[i] = str.velocity[i];
		bestPosition[i] = str.bestPosition[i];
	}
	//����ֵ
    value = new double[static_cast<unsigned long long>(numberOfObjectives)];
	//�������ֵ
    bestValue = new double[static_cast<unsigned long long>(numberOfObjectives)];
	for (int i = 0; i < numberOfObjectives; i++) {
		value[i] = str.value[i];
		bestValue[i] = str.bestValue[i];
	}
	//���ӿ�����
	feasible = str.feasible;
	bestFeasible = str.bestFeasible;
	//Ȩ��
	c1 = str.c1;
	c2 = str.c2;
	weight = str.weight;
	vari = str.vari;
	functionPtr = str.functionPtr;
	maxVelocity = str.maxVelocity;
	//Լ�������Ż������н����趨��
	constraits = str.constraits;
	//���ӱ�ռ�Ŵ���
	paretoDominance = str.paretoDominance;
	//����λ���Ͻ��½�
	lowerBounds = str.lowerBounds;
	upperBounds = str.upperBounds;
	//��������ٶ�
	maxVelocity = str.maxVelocity;
}

Particle& Particle::operator=(const Particle& str)
{
	if (this != &str)
	{
		//��������
		this->numberOfVariables = str.numberOfVariables;
		//�Ż�Ŀ�����
		this->numberOfObjectives = str.numberOfObjectives;
		//λ���ٶ�Ŀ��ֵ����
		for (int i = 0; i < numberOfVariables; i++) {
			this->position[i] = str.position[i];
			this->velocity[i] = str.velocity[i];
			this->bestPosition[i] = str.bestPosition[i];
		}
		for (int i = 0; i < numberOfObjectives; i++) {
			this->value[i] = str.value[i];
			this->bestValue[i] = str.bestValue[i];
		}
		//���ӿ�����
		this->feasible = str.feasible;
		this->bestFeasible = str.bestFeasible;
		//Ȩ��
		this->c1 = str.c1;
		this->c2 = str.c2;
		this->weight = str.weight;
		this->vari = str.vari;
		this->functionPtr = str.functionPtr;
		this->maxVelocity = str.maxVelocity;
		//Լ�������Ż������н����趨�� 
		this->constraits = str.constraits;
		//���ӱ�ռ�Ŵ���
		this->paretoDominance = str.paretoDominance;
		//����λ���Ͻ��½�
		this->lowerBounds = str.lowerBounds;
		this->upperBounds = str.upperBounds;
		//��������ٶ�
		this->maxVelocity = str.maxVelocity;
	}
	return *this;
}

Particle::~Particle()
{
	//cout << "aa" << endl;
	delete[] position; 
	delete[] velocity;
	delete[] bestPosition;
	delete[] value;
	delete[] bestValue;
}

void Particle::inicializeParticle()
{
	//��ʼ������λ�ã��ٶ�=0��ֵ���λ�ã�������
	for (int i = 0; i < numberOfVariables; i++) {
		double random = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)+1); //����0-1�������� ��תΪdouble
		position[i] = lowerBounds[i] + (upperBounds[i] - lowerBounds[i]) * random;
		random = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)+1);
		velocity[i] = lowerBounds[i] + (upperBounds[i] - lowerBounds[i]) * random;
	}

	(*functionPtr)(this);

	bestFeasible = feasible;
	for (int i = 0; i < numberOfVariables; i++)
		bestPosition[i] = position[i];
	for (int i = 0; i < numberOfObjectives; i++)
		bestValue[i] = value[i];
}

void Particle::updateParticle(const double *globalBestPosition)
{
	//����λ�ø���
	double random1;
	double random2;
	double random3;
	double random4;

	for (int i = 0; i < numberOfVariables; i++) {
		random1 = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)+1);
		random2 = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)+1);
		velocity[i] = *weight * velocity[i] + c1 * random1 * (bestPosition[i] - position[i]) + c2 * random2 * (globalBestPosition[i] - position[i]);

		//�ж��ٶ��Ƿ����
		if (fabs(velocity[i]) > maxVelocity[i])
			velocity[i] = maxVelocity[i] * velocity[i] / fabs(velocity[i]);

		//λ�ø���
		position[i] = position[i] + velocity[i];
		random3 = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)+1);
		random4 = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)+1);
		if (random3 < *vari)
		{
			position[i] = random4*(upperBounds[i] - lowerBounds[i]) + lowerBounds[i];
			//cout << 'a' ;
		}


		//�ж�λ���Ƿ����
		if (position[i] >= upperBounds[i])
			position[i] = upperBounds[i];

		if (position[i] <= lowerBounds[i])
			position[i] = lowerBounds[i];
	}

	(*functionPtr)(this);

	for (int i = 0; i < numberOfObjectives; i++)
		value[i] += constraits;

	updateParticleBest();
}

const double *Particle::getBestPosition()
{
	return bestPosition;
}

const double *Particle::getBestValue()
{
	return bestValue;
}

bool Particle::getBestFeasible()
{
	return bestFeasible;
}

const double *Particle::getValue()
{
	return value;
}

void Particle::setValue(const double *_value)
{
    for (int i = 0; i < numberOfObjectives; i++){
        if(optimizeMode[i] == "Maximize"){
            value[i] = _value[i];
        }
        else if(optimizeMode[i] == "Minimize"){
            value[i] = 1/_value[i];
        }
        else{
            qDebug() << "Error: Particle::setValue!";
        }
    }
//    for(int i = 0; i < numberOfObjectives; ++i){
//        qDebug() << optimizeMode[i];
//        value[i] = _value[i];
//    }
}

void Particle::setConstraits(double _constraits)
{
	constraits = _constraits;
}

void Particle::setParetoDominance(int _paretoDominance)
{
	paretoDominance = _paretoDominance;
}

int Particle::getParetoDominance()
{
	return paretoDominance;
}




bool Particle::getFeasible()
{
	return feasible;
}

void Particle::setFeasible(bool _feasible)
{
	feasible = _feasible;
}

int Particle::getNumberOfVariables()
{
	return numberOfVariables;
}

int Particle::getNumberOfObjective()
{
	return numberOfObjectives;
}

const double *Particle::getPosition()
{
	return position;
}

void Particle::printParticle()
{
	//cout << "Position = ";
	for (int i = 0; i < numberOfVariables; i++)
		cout << position[i] << "   ";
	cout << endl;
	//cout << "Value = ";
	for (int i = 0; i < numberOfObjectives; i++)
		cout << value[i] << "   ";
	cout << endl;
	//cout << "Constraints = " << constraits << endl;
	//cout << "Feasible? " << (feasible ? "true" : "false") << endl;
}

void Particle::printParticleBest()
{
	cout << "Position = ";
	for (int i = 0; i < numberOfVariables; i++)
		cout << bestPosition[i] << "   ";
	cout << endl;
	cout << "Value = ";
	for (int i = 0; i < numberOfObjectives; i++)
		cout << bestValue[i] << "   ";
	cout << endl;
	cout << "Feasible? " << (bestFeasible ? "true" : "false") << endl;
}

///private
void Particle::updateParticleBest()
{
	if (feasible || !bestFeasible) {
		//�ж�֧����
		int dominance = 0;
		int nondominance = 0;
		int dom_less = 0;
		int dom_equal = 0;
		int dom_more = 0;
		for (int k = 0; k < numberOfObjectives; k++)
		{
			if (value[k] < bestValue[k])
				dom_less++;
			else if (value[k] == bestValue[k])
				dom_equal++;
			else
				dom_more++;
		}
		if ((dom_less == 0) && (dom_equal != numberOfObjectives))
			dominance++;
		else if ((dom_more == 0) && (dom_equal != numberOfObjectives))
			nondominance++;
		//�ж�����ֵ
		if (feasible != bestFeasible){
			for (int i = 0; i < numberOfVariables; i++)
				bestPosition[i] = position[i];
			for (int i = 0; i < numberOfObjectives; i++)
				bestValue[i] = value[i];
		}
		else if (nondominance == 1){
			for (int i = 0; i < numberOfVariables; i++)
				bestPosition[i] = position[i];
			for (int i = 0; i < numberOfObjectives; i++)
				bestValue[i] = value[i];
		}
		else if ((static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)+1)) > 0.5){
			for (int i = 0; i < numberOfVariables; i++)
				bestPosition[i] = position[i];
			for (int i = 0; i < numberOfObjectives; i++)
				bestValue[i] = value[i];
		}
	}
}
