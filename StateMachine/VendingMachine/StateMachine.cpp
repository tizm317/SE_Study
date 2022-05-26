#include "StateMachine.h"
#include <iostream>

void StateMachine::displayInsertedMoney(int money)
{
	cout << "���� ���Ե� �ݾ��� " << money << "���Դϴ�" << endl;

	return;
}

void StateMachine::refundMoney(int money)
{
	cout << "��ȯ�Ǵ� �ݾ��� " << money << "���Դϴ�" << endl;

}

void StateMachine::displayLight(int light)
{
	// On : 1, Off : 0
	if(light == 0)
		cout << "���� ��ư�� ������ �������ϴ�" << endl;
	else
		cout << "���� ��ư�� ������ �������ϴ�" << endl;
	return;
}

void StateMachine::giveBeverage(int dummy)
{
	cout << "���ᰡ ���Խ��ϴ�" << endl;
	return;
}

Event StateMachine::getNextEvent()
{
	Event selectedEvent;
	int inputEvent;

	cout << "[���� ���� :" << getCurrentStateString() << "]" << endl;
	cout << "1. Input 100 won" << endl;
	cout << "2. Press Refund Button" << endl;
	cout << "3. Press Beverage Button" << endl;
	cout << "4. Quit " << endl;
	cin >> inputEvent;

	switch (inputEvent)
	{
	case 1:
		selectedEvent = EVENT_INSERT_100;
		break;
	case 2:
		selectedEvent = EVENT_PRESS_REFUND_BUTTON_PRESSED;
		break;
	case 3:
		selectedEvent = EVENT_BEVERAGE_BUTTON_PRESSED;
		break;
	case 4:
		selectedEvent = EVENT_QUIT;
		curState = STATE_END;
		break;
	default:
		cout << "Wrong Input" << endl;
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
	case STATE_100_INSERTED:
		returnedString = "STATE_100_INSERTED";
		break;
	case STATE_200_INSERTED:
		returnedString = "STATE_200_INSERTED";
		break;
	}
	return returnedString;
}

void StateMachine::run()
{
	int i, j;
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
					for (j = 0; j < table[i].num_actions; j++)
						(this->*table[i].action[j])(table[i].action_paramter[j]);

					curState = table[i].nextState;
					break;
				}
			}
		}
		cout << endl << endl;
	}
}
