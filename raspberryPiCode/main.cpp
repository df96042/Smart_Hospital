#include "common.h"
#include "ICU.h"
#include "fever.h"
#include "vegetative_state.h"

using namespace han;

//Global Variable
void init_setting(ICU &room);

int main(int argc, char *argv[] ){
	cout << "main start!"<< endl;
	//Local variable + class
	ICU room1;



	//setting all (+multi thread)
	init_setting(room1);
	cout << "make thread!"<< endl;
	thread t(&ICU::get_sensor, &room1);
	//thread t1(&Fever::get_sensor, &room1.patient1);
	//thread t2(&Vegetative::get_sensor, &room1.patient2);

	// while loop
	while(true){
		room1.upload_data();
	}
	t.join();
	//t1.join();
	//t2.join();
	return 0;
}



void init_setting(ICU &room){
	printf("%s \n", "main setting Start!");
	fflush(stdout);
	room.setup_raspberry();
}
