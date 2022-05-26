#pragma once
#include <string>

#define NUMBER_OF_TABLE_ENTRIES 100 // event-action table 현재 entry 개수
#define MAX_NUMBER_OF_ACTIONS 3		// transition 시 실행되는 최대 action 개수

using namespace std;

typedef enum
{
	EVENT_INSERT_100,
	EVENT_PRESS_REFUND_BUTTON_PRESSED,
	EVENT_BEVERAGE_BUTTON_PRESSED,
	EVENT_QUIT,
} Event;

typedef enum
{
	STATE_READY,
	STATE_100_INSERTED,
	STATE_200_INSERTED,
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
		int num_actions;
		void (StateMachine::* action[MAX_NUMBER_OF_ACTIONS])(int);
		int action_paramter[MAX_NUMBER_OF_ACTIONS];
		State nextState;
	} EventActionTable;

	EventActionTable table[NUMBER_OF_TABLE_ENTRIES]
	{
		// STATE_READY
		{STATE_READY, EVENT_INSERT_100, 1, {&StateMachine::displayInsertedMoney}, {100}, STATE_100_INSERTED},
		// STATE_100_INSERTED
		{STATE_100_INSERTED, EVENT_PRESS_REFUND_BUTTON_PRESSED, 2, {&StateMachine::refundMoney, &StateMachine::displayInsertedMoney}, {100, 0}, STATE_READY},
		{STATE_100_INSERTED, EVENT_INSERT_100, 2, {&StateMachine::displayInsertedMoney, &StateMachine::displayLight}, {200, 1}, STATE_200_INSERTED},
		// STATE_200_INSERTED
		{STATE_200_INSERTED, EVENT_INSERT_100, 1, {&StateMachine::refundMoney}, {100}, STATE_200_INSERTED},
		{STATE_200_INSERTED, EVENT_PRESS_REFUND_BUTTON_PRESSED, 3, {&StateMachine::displayInsertedMoney, &StateMachine::refundMoney, &StateMachine::displayLight}, {0, 200, 0}, STATE_READY},
		{STATE_200_INSERTED, EVENT_BEVERAGE_BUTTON_PRESSED, 3, {&StateMachine::displayInsertedMoney, &StateMachine::displayLight, &StateMachine::giveBeverage}, {0, 0, 0}, STATE_READY},
	};

	// action 함수들
	void displayInsertedMoney(int money);
	void refundMoney(int money);
	void displayLight(int light);
	void giveBeverage(int dummy);

	Event getNextEvent();			// 사용자로부터 다음 event 입력 받음
	string getCurrentStateString(); // 현재 상태를 string으로 생성해서 반환


public:
	void run();
};