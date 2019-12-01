#include "nurse.h"

namespace han
{
	int Nurse::danger_emergency(){
		
		digitalWrite(LED_RED, HIGH);
		
		if(digitalRead(BUTTON) == HIGH){
			return danger_num = 3;
		}
		else return danger_num = 1;
	}

	int Nurse::danger_ringer(){

		digitalWrite(LED_YELLOW, HIGH);
		
		if(digitalRead(BUTTON) == HIGH){
			return danger_num = 3;
		}
		else return danger_num = 2;
	}
	
	int Nurse::danger_situation_off(){
		
		digitalWrite(LED_RED, LOW);
		digitalWrite(LED_YELLOW, LOW);

		return danger_num = 0;
	}

	void Nurse::print(){
		cout << "Nurse print << \t danger_num : " << danger_num << endl;
	}
}