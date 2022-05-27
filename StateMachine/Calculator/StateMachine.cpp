#include "StateMachine.h"
#include <iostream>


void StateMachine::inputDigits()
{
	cout << "inputDigits" << endl;
}

void StateMachine::clear()
{
	cout << "clear" << endl;

}

void StateMachine::inputOp()
{
	cout << "inputOp" << endl;
}

void StateMachine::pushEquals()
{
	cout << "pushEquals" << endl;
}

void StateMachine::showError()
{
	cout << "showError" << endl;
}

//

Event StateMachine::getNextEvent()
{
	Event selectedEvent;
	int inputEvent;

	//
	cout << "[현재 상태 : " << getCurStateString() << " ]" << endl;
	cout << "1. inputDigits" << endl;
	cout << "2. clear" << endl;
	cout << "3. inputOp" << endl;
	cout << "4. pushEquals" << endl;
	cout << "5. showError" << endl;
	cout << "6. Quit" << endl;
	cout << "Select an event # : ";
	cin >> inputEvent;

	switch (inputEvent)
	{
	case 1:
		selectedEvent = EVENT_INPUT_DIGITS;
		break;
	case 2:
		selectedEvent = EVENT_CLEAR;
		break;
	case 3:
		selectedEvent = EVENT_INPUT_OP;
		break;
	case 4:
		selectedEvent = EVENT_PUSH_EQUALS;
		break;
	case 5:
		selectedEvent = EVENT_ERROR;
		break;
	default:
		curState = STATE_END;
		selectedEvent = EVENT_QUIT;
		break;
	}

	return selectedEvent;
}

string StateMachine::getCurStateString()
{
	string returnString;
	switch (curState)
	{
	case STATE_EMPTY:
		returnString = "STATE_EMPTY";
		break;
	case STATE_ACCUMULATING_DIGITS:
		returnString = "STATE_ACCUMULATING_DIGITS";
		break;
	case STATE_OPERATOR_INPUTTED:
		returnString = "STATE_OPERATOR_INPUTTED";
		break;
	case STATE_ACCUMULATING_DIGITS_2:
		returnString = "STATE_ACCUMULATING_DIGITS_2";
		break;
	case STATE_SHOWING_RESULT:
		returnString = "STATE_SHOWING_RESULT";
		break;
	case STATE_SHOWING_ERROR:
		returnString = "STATE_SHOWING_ERROR";
		break;
	default:
		returnString = "STATE_END";
		break;
	}

	return returnString;
}

void StateMachine::run()
{
	Event curEvent;

	curState = STATE_EMPTY;

	while (curState != STATE_END)
	{
		curEvent = getNextEvent();

		for (int i = 0; i < NUM_OF_TABLE_ENTRIES; i++)
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
	}
	cout << endl;
}
