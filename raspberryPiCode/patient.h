#ifndef SH_PATIENT
#define SH_PATIENT
#include "common.h"

namespace han
{

	class Patient{
		protected:
			string name;
			int danger;
			mutex m;
			int fd;

		public:
			Patient(){	name="NULL";	danger=0;	fd=0; }
			int get_danger(){return danger;}
			void set_danger(int num){danger = num;}
			string get_name(){return name;}

		
	};
}

#endif /* SH_PATIENT */