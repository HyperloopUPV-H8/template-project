#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"

using namespace std::chrono_literals;

enum States{
	OPERATIONAL,
	FALLO
};

class Test{
public:
	uint64_t current = 0;
	void add(){
		add_protection(&current,Boundary<uint64_t,BELOW>(10));
	}

};


int main(void)
{

	//uint64_t current = 0;
	Test test;
	StateMachine state_machine;
	state_machine.add_state(States::OPERATIONAL);
	state_machine.add_state(States::FALLO);
	DigitalOutput pin(PB0);
	auto ledtoggle = [&pin](){
		pin.toggle();
	};
	state_machine.add_low_precision_cyclic_action(ledtoggle, 100ms);

	auto ledon = [&pin](){
		pin.turn_on();
	};
	state_machine.add_enter_action(ledon, States::FALLO);
	ProtectionManager::link_state_machine(state_machine,States::FALLO);
	STLIB::start();
	//add_protection(&current,Boundary<uint64_t,BELOW>(10));

	test.add();

	while(1) {
		ProtectionManager::check_protections();
		STLIB::update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
