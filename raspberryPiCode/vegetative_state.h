#ifndef SH_VEGETATIVE
#define SH_VEGETATIVE
#include "common.h"
#include "patient.h"

namespace han{

	class Vegetative: public Patient{
		private:
			int heart_rate;
			double infusion_solution;
			bool wake_up;
			
		public:
			Vegetative(){	heart_rate=0;	infusion_solution =0;	wake_up=0;	}
			Vegetative(string);
			int get_heart_rate(){return heart_rate;}
			void set_heart_rate(int num){heart_rate = num;}
			double get_infusion_solution(){return infusion_solution;}
			void set_infusion_solution(double num){infusion_solution = num;}
			bool get_wake_up(){return wake_up;}
			void print();

			void aduino_setting(string device_port);
			void get_sensor();
			void give_order();
	};


}
#endif /* SH_VEGETATIVE */