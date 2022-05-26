#pragma once
#include <string>

#define NUMBER_OF_TABLE_ENTRIES 100 // event-action table ���� entry ����

using namespace std;

typedef enum
{
	EVENT_REQUEST_TRIP,
	EVENT_REQUEST_PAYMENT,
	EVENT_PAYMENT_FAILED,
	EVENT_PAYMENT_SUCCEEDED,
	EVENT_TRIP_COMPLETED,
	EVENT_QUIT,
} Event;

typedef enum
{
	STATE_READY,
	STATE_TRIP_REQUESTED,
	STATE_PAYMENT_REQUESTED,
	STATE_DERIVER_ASSIGNED,
	STATE_END,
} State;


class StateMachine
{
private:
	State curState;

	// event-action table
	typedef struct
	{
		State curState;
		Event event;
		void (StateMachine::* action)();
		State nextState;
	} EventActionTable;

	EventActionTable table[NUMBER_OF_TABLE_ENTRIES]
	{
		// STATE_READY
		{STATE_READY, EVENT_REQUEST_TRIP, &StateMachine::requestTrip, STATE_TRIP_REQUESTED},
		// STATE_TRIP_REQUESTED
		{STATE_TRIP_REQUESTED, EVENT_REQUEST_PAYMENT, &StateMachine::requestPayment, STATE_PAYMENT_REQUESTED},
		// STATE_PAYMENT_REQUESTED
		{STATE_PAYMENT_REQUESTED, EVENT_PAYMENT_FAILED, &StateMachine::paymentFailed, STATE_TRIP_REQUESTED},
		{STATE_PAYMENT_REQUESTED, EVENT_PAYMENT_SUCCEEDED, &StateMachine::paymentSucceeded, STATE_DERIVER_ASSIGNED},
		// STATE_DERIVER_ASSIGNED
		{STATE_DERIVER_ASSIGNED, EVENT_TRIP_COMPLETED, &StateMachine::tripCompleted, STATE_READY}
	};

	// action �Լ���
	void requestTrip();
	void requestPayment();
	void paymentFailed();
	void paymentSucceeded();
	void tripCompleted();

	Event getNextEvent();			// ����ڷκ��� ���� event �Է� ����
	string getCurrentStateString(); // ���� ���¸� string���� �����ؼ� ��ȯ


public:
	void run();
};