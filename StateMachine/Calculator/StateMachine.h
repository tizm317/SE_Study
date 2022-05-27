#pragma once
#include <string>

using namespace std;

#define NUM_OF_TABLE_ENTRIES 100

typedef enum
{
	STATE_EMPTY,
	STATE_ACCUMULATING_DIGITS,
	STATE_OPERATOR_INPUTTED,
	STATE_ACCUMULATING_DIGITS_2,
	STATE_SHOWING_RESULT,
	STATE_SHOWING_ERROR,
	STATE_END,
} State;

typedef enum
{
	EVENT_INPUT_DIGITS,
	EVENT_CLEAR,
	EVENT_INPUT_OP,
	EVENT_PUSH_EQUALS,
	EVENT_ERROR, // ?
	EVENT_QUIT
} Event;


class StateMachine
{
private:
	State curState;

	typedef struct
	{
		State curState;
		Event event;
		void (StateMachine::* action)();
		State nextState;
	} EventActionTable;

	// state
	EventActionTable table[NUM_OF_TABLE_ENTRIES]
	{
		// 1. STATE_EMPTY
		{STATE_EMPTY, EVENT_INPUT_DIGITS, &StateMachine::inputDigits, STATE_ACCUMULATING_DIGITS},
		// 2. STATE_ACCUMULATING_DIGITS
		{STATE_ACCUMULATING_DIGITS, EVENT_INPUT_DIGITS, &StateMachine::inputDigits, STATE_ACCUMULATING_DIGITS},
		{STATE_ACCUMULATING_DIGITS, EVENT_CLEAR, &StateMachine::clear, STATE_EMPTY},
		{STATE_ACCUMULATING_DIGITS, EVENT_INPUT_OP, &StateMachine::inputOp, STATE_OPERATOR_INPUTTED},
		// 3. STATE_OPERATOR_INPUTTED
		{STATE_OPERATOR_INPUTTED, EVENT_INPUT_DIGITS, &StateMachine::inputDigits, STATE_ACCUMULATING_DIGITS_2},
		{STATE_OPERATOR_INPUTTED, EVENT_INPUT_DIGITS, &StateMachine::inputOp, STATE_OPERATOR_INPUTTED},
		{STATE_OPERATOR_INPUTTED, EVENT_CLEAR, &StateMachine::clear, STATE_EMPTY},
		// 4. STATE_ACCUMULATING_DIGITS_2
		{STATE_ACCUMULATING_DIGITS_2, EVENT_INPUT_DIGITS, &StateMachine::inputDigits, STATE_ACCUMULATING_DIGITS_2},
		{STATE_ACCUMULATING_DIGITS_2, EVENT_INPUT_OP, &StateMachine::inputOp, STATE_OPERATOR_INPUTTED},
		{STATE_ACCUMULATING_DIGITS_2, EVENT_PUSH_EQUALS, &StateMachine::pushEquals, STATE_SHOWING_RESULT},
		{STATE_ACCUMULATING_DIGITS_2, EVENT_ERROR, &StateMachine::showError, STATE_SHOWING_ERROR},
		{STATE_ACCUMULATING_DIGITS_2, EVENT_CLEAR, &StateMachine::clear, STATE_EMPTY},
		// 5. STATE_SHOWING_RESULT
		{STATE_SHOWING_RESULT, EVENT_INPUT_DIGITS, &StateMachine::inputDigits, STATE_ACCUMULATING_DIGITS},
		{STATE_SHOWING_RESULT, EVENT_CLEAR, &StateMachine::clear, STATE_EMPTY},
		// 6. STATE_SHOWING_ERROR
		{STATE_SHOWING_ERROR, EVENT_CLEAR, &StateMachine::clear, STATE_EMPTY},
	};

	// action
	void inputDigits();
	void clear();
	void inputOp();
	void pushEquals();
	void showError();


	// ¸Þ¼Òµå
	Event getNextEvent();
	string getCurStateString();

public:
	void run();
};