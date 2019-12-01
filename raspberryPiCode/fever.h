#ifndef SH_FEVER
#define SH_FEVER
#include "common.h"
#include "patient.h"

namespace han
{

	class Fever: public Patient{
		private:
			int heart_rate;
			double temp;

	
		public:
			Fever(){ heart_rate=0;	temp=0;	}
			int get_heart_rate(){return heart_rate;}
			void set_heart_rate(int num){heart_rate = num;}
			double get_temp(){return temp;}
			void set_temp(double num){temp = num;}
			int get_fd(){return fd;}
			void set_fd(int num){fd = num;}
			void print();

			void aduino_setting(string device_port);
			void get_sensor();
			void give_order();
	};

}

#endif /* SH_FEVER */