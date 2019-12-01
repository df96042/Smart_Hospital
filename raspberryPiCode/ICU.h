#ifndef SH_ICU
#define SH_ICU
#include "common.h"
#include "fever.h"
#include "vegetative_state.h"
#include "nurse.h"

namespace han
{

	class ICU{
		private:
			double room_temp;
			int danger_situation;
			
		public:
			ICU(){	room_temp = 0;	danger_situation = 0;	}
			Fever patient1;
			Vegetative patient2;
			Nurse nurse;
			int get_danger_situation(){return danger_situation;}
			double get_room_temp(){return room_temp;}
			void print();
			void get_sensor();

			void gpio_setting(); // ¹ÎÁö
			void setup_raspberry();
			void upload_data(); //mysql
			void judge_danger();

			void situation_control(); // ¹ÎÁö
	};

}
#endif /* SH_ICU */