#include "StateMachine.h"
#include <iostream>

void StateMachine::requestTrip()
{
	cout << "requestTrip" << endl;
	return;
}

void StateMachine::requestPayment()
{
	cout << "requestPayment" << endl;
	return;
}

void StateMachine::paymentFailed()
{
	cout << "paymentFailed" << endl;
	return;
}

void StateMachine::paymentSucceeded()
{
	cout << "paymentSucceeded" << endl;
	return;
}

void StateMachine::tripCompleted()
{
	cout << "tripCompleted" << endl;
	return;
}

Event StateMachine::getNextEvent()
{
	Event selectedEvent;
	int inputEvent;

	cout << "[현재 상태 :" << getCurrentStateString() << "]" << endl;
	cout << "1. requestTrip" << endl;
	cout << "2. requestPayment" << endl;
	cout << "3. paymentFailed" << endl;
	cout << "4. paymentSucceeded " << endl;
	cout << "5. tripCompleted " << endl;
	cout << "6. Quit " << endl;
	cout << "Select an event # : ";
	cin >> inputEvent;

	switch (inputEvent)
	{
	case 1:
		selectedEvent = EVENT_REQUEST_TRIP;
		break;
	case 2:
		selectedEvent = EVENT_REQUEST_PAYMENT;
		break;
	case 3:
		selectedEvent = EVENT_PAYMENT_FAILED;
		break;
	case 4:
		selectedEvent = EVENT_PAYMENT_SUCCEEDED;
		break;
	case 5:
		selectedEvent = EVENT_TRIP_COMPLETED;
		break;
	case 6:
		selectedEvent = EVENT_QUIT;
		curState = STATE_END;
		break;
	default:
		cout << "Wrong Input, Please Input between 1~6" << endl;
		selectedEvent = EVENT_QUIT;
		curState = STATE_END;
		break;
	}

	return selectedEvent;
}

string StateMachine::getCurrentStateString()
{
	string returnedString;

	switch (curState)
	{
	case STATE_READY:
		returnedString = "STATE_READY";
		break;
	case STATE_TRIP_REQUESTED:
		returnedString = "STATE_TRIP_REQUESTED";
		break;
	case STATE_PAYMENT_REQUESTED:
		returnedString = "STATE_PAYMENT_REQUESTED";
		break;
	case STATE_DERIVER_ASSIGNED:
		returnedString = "STATE_DERIVER_ASSIGNED";
		break;
	}
	return returnedString;
}

void StateMachine::run()
{
	int i;
	Event curEvent;

	curState = STATE_READY;
	while (curState != STATE_END)
	{
		curEvent = getNextEvent();

		for (i = 0; i < NUMBER_OF_TABLE_ENTRIES; i++)
		{
			if (curState == table[i].curState)
			{
				if (curEvent == table[i].event)
				{
					(this->*table[i].action)();

					curState = table[i].nextState;
					break;
				}
			}
		}
		cout << endl << endl;
	}
}
