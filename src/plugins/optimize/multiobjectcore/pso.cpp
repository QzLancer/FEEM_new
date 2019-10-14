#include "pso.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <exception>
#include <ctime>
using namespace std;




PSO::PSO(int _numberOfParticles,
	int _numberOfVariables,
	int _numberOfObjectives,
	int _numberOfExtraParticles,
	double *_lowerBounds,
	double *_upperBounds,
	double *_vmax,
	void(*_objectiveFunction)(Particle *),
	double _lowerWeight,
	double _upperWeight,
	int _maxIteration,
	double _c1,
	double _c2,
	double _vari,
    QStringList _optimizeMode,
    QString _stoppingCriteria,
    QString _psoType)
{
	int i = 0;

	srand((unsigned)time(0));

	numberOfParticles = _numberOfParticles;
	maxIteration = _maxIteration;
	numberOfObjectives = _numberOfObjectives;
	numberOfExtraParticles = _numberOfExtraParticles;
	upperWeight = _upperWeight;
	lowerWeight = _lowerWeight;
	stoppingCriteria = _stoppingCriteria;
	psoType = _psoType;
	vari = _vari;
	numberOfVariables = _numberOfVariables;
	
	//��������С�ڵ���0�򱨴�
	if (numberOfParticles <= 0)
		throw "Number of particles can't be less or equal than zero.";
	//�½����Ӿ���
    particles = new Particle *[static_cast<unsigned long long>(numberOfParticles)];
	//��ʼ������Ⱥ
	for (i = 0; i < numberOfParticles; i++)
		particles[i] = new Particle(_numberOfVariables,_numberOfObjectives,
		_lowerBounds,
		_upperBounds,
		_vmax,
		_c1, _c2,
		&weight, &vari,
        _objectiveFunction,
        _optimizeMode);
	//��ʼ��һ����Ӣ���Ӿ����СΪ�����ľ�Ӣ��Ⱥ��Ŀ
	extraParticles = new Particle *[2 * numberOfExtraParticles];
	//��ʼ��һ����Ӣ����Ⱥ
	for (i = 0; i < (2*numberOfExtraParticles); i++)
		extraParticles[i] = new Particle(_numberOfVariables,_numberOfObjectives,
		_lowerBounds,
		_upperBounds,
		_vmax,
		_c1, _c2,
		&weight, &vari,
        _objectiveFunction,
        _optimizeMode);

	//tempParticle = new Particle(_numberOfVariables, _numberOfObjectives,
	//	_lowerBounds,
	//	_upperBounds,
	//	_vmax,
	//	_c1, _c2,
	//	&weight,
	//	_objectiveFunction);

	//�������Ӹ���
	bestParticleIndex = 0;
	updateGlobalBest();
	//��Ӣ��Ⱥ�ִ���������ʼ��
	sizeOfExtraParticles = 0;
	//��ʼ����Ӧ��
	distance = new double[2*numberOfExtraParticles];


}

PSO::~PSO()
{
	//delete tempParticle;
	for (int i = 0; i < numberOfParticles; i++){
		delete particles[i];
		//cout << "Particle=" << i << endl;
	}
	delete[] particles;
	for (int i = 0; i < (2 * numberOfExtraParticles); i++){
		delete extraParticles[i];
		//cout << "extraParticles=" << i << endl;
	}
	delete[] extraParticles;
	delete[] distance;
	//cout << "why" << endl;
	
}

void PSO::updateParticles()
{	
	//����ȫ�����Ž������Ⱥ
	for (int i = 0; i < numberOfParticles; i++) {
		particles[i]->updateParticle(extraParticles[bestParticleIndex]->getBestPosition());
	}
}

void PSO::updateDomiance()
{
	//�жϸ������໥ռ�����
	//ռ�������¼
	int _dominance;
	for (int i = 0; i < numberOfParticles; i++)
	{
		_dominance = 0;
		for (int j = 0; j < numberOfParticles; j++)
		{
			int dom_less = 0;
			int dom_equal = 0;
			int dom_more = 0;
			for (int k = 0; k < numberOfObjectives; k++)
			{
				if (*(particles[i]->getValue() + k) < *(particles[j]->getValue() + k))
					dom_less++;
				else if (*(particles[i]->getValue() + k) == *(particles[j]->getValue() + k))
					dom_equal++;
				else
					dom_more++;
			}
			if ((dom_less == 0) && (dom_equal != numberOfObjectives))
				_dominance++;
		}
		particles[i]->setParetoDominance(_dominance);
	}
}

void PSO::updateGlobalBest()
{
	//���������������
	for (int i = 0; i < numberOfParticles; i++)
		if (particles[i]->getFeasible() || !particles[bestParticleIndex]->getBestFeasible())
			if (particles[i]->getFeasible() != particles[bestParticleIndex]->getBestFeasible() || particles[i]->getValue() <= particles[bestParticleIndex]->getBestValue())
				bestParticleIndex = i;
}

void PSO::updateExtraParticles()
{
	//���������������뾫Ӣ��Ⱥ�У�������룩
	for (int i = 0; i < numberOfParticles; i++){
		if (particles[i]->getParetoDominance() == 0){
			sizeOfExtraParticles++;
			*extraParticles[sizeOfExtraParticles-1] = *particles[i];
			//
			if (sizeOfExtraParticles > 1){
				//��������Ӳ��ж�
				for (int m = 0; m < sizeOfExtraParticles-1; m++){
					int _dominance = 0;
					int dom_less = 0;
					int dom_equal = 0;
					int dom_more = 0;
					for (int k = 0; k < numberOfObjectives; k++)
					{
						if (*(extraParticles[sizeOfExtraParticles - 1]->getValue() + k) < *(extraParticles[m]->getValue() + k))
							dom_less++;
						else if (*(extraParticles[sizeOfExtraParticles - 1]->getValue() + k) == *(extraParticles[m]->getValue() + k))
							dom_equal++;
						else
							dom_more++;
					}
					if ((dom_less == 0) && (dom_equal != numberOfObjectives))
						extraParticles[sizeOfExtraParticles - 1]->setParetoDominance(1);
					else if ((dom_more == 0) && (dom_equal != numberOfObjectives))
						extraParticles[m]->setParetoDominance(1);
					else
						extraParticles[m]->setParetoDominance(0);
				}

				//ɾ����ռ������
				if (extraParticles[sizeOfExtraParticles - 1]->getParetoDominance() == 1)
				{
					sizeOfExtraParticles--;
					for (int ii = 0; ii < sizeOfExtraParticles;ii++)
						extraParticles[ii]->setParetoDominance(0);
				}
				else
				{
					int fzsizeOfExtraParticles = sizeOfExtraParticles;
						for (int ii = 0; ii < fzsizeOfExtraParticles; ii++)
					{
							if (extraParticles[ii]->getParetoDominance() != 0)
							{
								sizeOfExtraParticles--;
								for (int j = ii; j < sizeOfExtraParticles; j++){
									*extraParticles[j] = *extraParticles[j + 1];
								}
								ii--;
							}
					}
				}
				//ɾ����Ӣ��Ⱥ���ظ�����
				for (int ii = 0; ii < sizeOfExtraParticles; ii++){
					for (int j = ii + 1; j < sizeOfExtraParticles; j++){
						int signEqual = 1;
						for (int k = 0; k < numberOfVariables; k++){
							if (*(extraParticles[ii]->getValue() + k) != *(extraParticles[j]->getValue() + k))
								signEqual = 0;
						}
						if (signEqual == 1){
							for (int k = 0; k < sizeOfExtraParticles - j+ 1 ; k++){
								*extraParticles[j + k] = *extraParticles[j + k + 1];
							}
							j--;
							sizeOfExtraParticles--;
						}
					}
				}

				//����
				double detcan = 0;
				double* minPos;
				double* maxPos;
				double tempdistance;
				double det;
				double predistance;

				Particle *tempParticle = extraParticles[2*numberOfExtraParticles-1];

				minPos = new double[numberOfObjectives];
				maxPos = new double[numberOfObjectives];
				for (int iii = 0; iii < numberOfObjectives; iii++){
					minPos[iii] = *(extraParticles[0]->getValue() + iii);
					maxPos[iii] = *(extraParticles[0]->getValue() + iii);
				}
				detcan = (2 - (2 - 0.005)*((upperWeight - weight) / (upperWeight - lowerWeight)));
				if (detcan <= 0.7)
					detcan = 0.7;
				for(int ii = 0; ii < sizeOfExtraParticles; ii++){
					for (int iii = 0; iii < numberOfObjectives; iii++){
						if (minPos[iii] >= *(extraParticles[ii]->getValue() + iii))
							minPos[iii] = *(extraParticles[ii]->getValue() + iii);
						if (maxPos[iii] <= *(extraParticles[ii]->getValue() + iii))
							maxPos[iii] = *(extraParticles[ii]->getValue() + iii);
					}
				}
				det = detcan*getnorm(minPos, maxPos)/sizeOfExtraParticles;
				for (int ii = 0; ii < sizeOfExtraParticles; ii++){
					distance[ii] = 0;
					for (int iii = 0; iii < sizeOfExtraParticles; iii++){
						predistance = getnorm(extraParticles[ii]->getValue(), extraParticles[iii]->getValue());
						if (predistance <= det)
						{
							distance[ii] = distance[ii] + 1 - (predistance / det)*(predistance / det);
						}
					}
					distance[ii] = distance[ii] - 0.99;
					distance[ii] = 1/distance[ii];
				}
				for (int ii = 0; ii < sizeOfExtraParticles; ii++){
					for (int iii = (ii + 1); iii < sizeOfExtraParticles; iii++){
						if (distance[ii] < distance[iii]){
							*tempParticle = *extraParticles[ii];
							tempdistance = distance[ii];
							*extraParticles[ii] = *extraParticles[iii];
							distance[ii] = distance[iii];
							*extraParticles[iii] = *tempParticle;
							distance[iii] = tempdistance;
						}
				 	}
				}
				if (sizeOfExtraParticles > numberOfExtraParticles){ sizeOfExtraParticles = numberOfExtraParticles; }
				delete[] maxPos;
				delete[] minPos;
			}
		}
	}
}

void PSO::RussianBest()
{
	double random1;
	double temp;
	double roucan;
	temp = 0;
	roucan = 0;
	for (int i = 0; i < sizeOfExtraParticles; i++)
		temp = temp + distance[i];
	random1 = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)+1);
	random1 = random1*temp;
	for (int i = 0; i < sizeOfExtraParticles; i++)
	{
		roucan = roucan + distance[i];
		if (random1 <= roucan)
		{
 			bestParticleIndex = i;
			break;
		}
	}
}


double PSO::getnorm(const double *A, const double *V)
{
	double norm;
	norm = 0;
	for (int i = 0; i < numberOfObjectives; i++)
	{
		norm = norm + (A[i] - V[i])*(A[i] - V[i]);
	}
	norm = sqrt(norm);
	return norm;
}


void PSO::printBest()
{	
	for (int i = 0; i < numberOfExtraParticles; i++)
	{
		extraParticles[i]->printParticle();
	}
	cout << numberOfExtraParticles << endl;
	cout << sizeOfExtraParticles << endl;
}


//�������ݹ�������Ѱ�ŷ���
void PSO::optimize()
{
	//�Ż����� ����������update ĿǰĬ��none
	int i = 0;
	double inivari=vari;
	while (i < maxIteration){
		    weight = upperWeight - double(i) / maxIteration * (upperWeight - lowerWeight);
			vari = inivari*pow((1 - double(i) / maxIteration), 5);
			if (i > (maxIteration / 2))
				vari = 0;
			updateParticles();
			updateDomiance();
			updateExtraParticles();
			RussianBest();
			i++;
			//cout << i << endl;
	}

	//cout << i << endl;
}

