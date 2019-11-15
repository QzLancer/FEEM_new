#pragma once

#include "particle.h"
#include <QString>
#include <QVector>
using namespace std;

class PSO
{
public:
	//���캯��
    PSO(int _numberOfParticles,
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
        QString _psoType);
	//��������
	~PSO();

	//�Ż�����
	void optimize();
	//������ֵ
	//const double *getBestValue();
	//������λ��
	//const double *getBestPosition();
	//������ֵ��Ӧ��
	bool getBestFeasibility();
	//��ӡ���ֵ
	void printBest();
	//�������
	double getnorm(const double *A, const double *V);

    QVector<QVector<double>> getBestPosition() const;
    QVector<QVector<double>> getBestValue() const;

private:

	//��ʼ��������Ⱥ
	void initializeParticles();
	//����������Ⱥ
	void updateParticles();
	//����ȫ������
	void updateGlobalBest();
	//��������ռ�����
	void updateDomiance();
	//���¾�Ӫ��Ⱥ
	void updateExtraParticles();
	//���£�������ûɶ��
	void updateConvergence();
	//���̶�
	void RussianBest();
	//��ӡ��n������
	void printParticle(int);
	//��������Ⱥ
	Particle **particles;
	//��Ӣ����Ⱥ
	Particle **extraParticles;
	//�м�����
	//Particle *tempParticle;
	//���Ӹ���
	int numberOfParticles;
	//���Ӿ�Ӣ��Ⱥ���Ӹ�������
	int numberOfExtraParticles;
	//���Ӿ�Ӣ��Ⱥ�ִ�������
	int sizeOfExtraParticles;
	//�Ż�Ŀ�����
	int numberOfObjectives;
	//��������
	int numberOfVariables;
	//�������λ��
	int bestParticleIndex;
	//Ȩ��
	double weight;
	//�������
	double vari;
	//����λ���Ͻ�
	double upperWeight;
	//����λ���Ͻ�
	double lowerWeight;
	//����������
	int maxIteration;
	//��Ӧ��
	double* distance;

	double threshold;

    QString psoType;

    QString stoppingCriteria;

	double impBest();

	double impAv();

	double noAce();

	double movObj();

	double movPor();

	double stdDev();

	double maxDist();

	double maxDistQuick();

	double comCrit();

	double diffMaxDistQuick();
	
};

