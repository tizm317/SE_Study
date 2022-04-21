#include <stdio.h>
#include <list>
#include <iostream>

using namespace std;

class Transportation
{
private:
	//const char* companyName;   // 회사 이름

public:
	virtual int getFare() const = 0;   // 총 운행거리와 단위거리 당 요금의 곱 반환
	virtual const char* getCompanyName() const = 0;
};

class Taxi : public Transportation
{
private:
	int totalDistance;      // 총 운행거리
	const char* companyName;

public:
	Taxi(const char* companyName, int totalDistance)
		: totalDistance(totalDistance), companyName(companyName)
	{}

	virtual int getFare() const
	{
		// 총 운행 거리 * 단위거리 당 요금 반환
		// 단위 거리 당 요금 : 1000
		return totalDistance * 1000;
	}
	virtual const char* getCompanyName() const
	{
		return companyName;
	}

};

class Bus : public Transportation
{
private:
	int   numBoarding;      // 탑승 횟수
	const char* companyName;

public:
	Bus(const char* companyName, int numBoarding)
		: numBoarding(numBoarding), companyName(companyName)
	{}

	virtual int getFare() const
	{
		// 탑승 횟수 * 기본요금 반환
		// 기본 요금 : 1000
		return numBoarding * 1000;
	}
	virtual const char* getCompanyName() const
	{
		return companyName;
	}
};

class TransportationList
{
private:
	list<Transportation*> lt_tp;

public:
	void addTransprtation(Transportation* newTransport)
	{
		lt_tp.push_back(newTransport);
	}
	int getTotalFare()
	{
		int sum = 0;
		for (auto& tp : lt_tp)
		{
			//cout << tp->getCompanyName() << endl; // 이름 출력
			sum += tp->getFare();
		}
		cout << sum << endl; // 총합 출력
		return sum;
	}
};

int main(void)
{
	TransportationList transprotations;
	Transportation* pNewTransportation = NULL;

	// 대중교통 이용내역 추가
	pNewTransportation = new Taxi("Hongik Taxi", 1200);
	transprotations.addTransprtation(pNewTransportation);

	pNewTransportation = new Taxi("Sangsu Taxi", 2300);
	transprotations.addTransprtation(pNewTransportation);

	pNewTransportation = new Bus("Seogyo Bus", 130);
	transprotations.addTransprtation(pNewTransportation);

	pNewTransportation = new Bus("Hongik Bus", 220);
	transprotations.addTransprtation(pNewTransportation);

	transprotations.getTotalFare();

	return 0;
}