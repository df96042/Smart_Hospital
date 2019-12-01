#include "ICU.h"

namespace han
{

	void ICU::gpio_setting(){
		//setup GPIO in wiringPi mode
		if (wiringPiSetupGpio() == -1){
		fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
		exit(1);
		}
		
		//FAN은 선풍기 IO 포트 번호 지정
		pinMode(FAN, OUTPUT);
		pinMode(BUTTON, INPUT);
		pinMode(LED_RED, OUTPUT);
		pinMode(LED_YELLOW, OUTPUT);

	}

	void ICU::setup_raspberry(){
				cout << "raspberry, aduino setting" <<endl;
				patient1.aduino_setting("/dev/ttyACM0");
				patient2.aduino_setting("/dev/ttyACM1");
				gpio_setting();
	}

	void ICU::upload_data(){ //mysql
		/*MYSQL *conn;
	    MYSQL_RES *res;
		MYSQL_RES *res2;
		MYSQL_RES *res3;
	    MYSQL_ROW row;
		char query[256];
		time_t now;
		int cnt=0;
		bool alarm = true;
		int flag;
	
		conn = mysql_connection_setup();
	
		res = mysql_perform_query(conn, "show tables");
		while((row = mysql_fetch_row(res)) != NULL)
	        printf("%s\n", row[0]);
	
		while(1){
			sleep(2);
			time(&now);
			////////////////patient1 전용//////////////////////
			sprintf(query,"insert into %s (time, heart_rate, temp, alarm) value (%d,%d,%lf,%d);", patient1, now, heart_rate, temp, alarm);
			printf("%s\n",query);
			res = mysql_perform_query(conn, query);
			
			////////////////patient2 전용//////////////////////
			sprintf(query,"insert into %s (time, heart_rate, weight, alarm) value (%d,%d,%lf,%d);", patient2, now, heart_rate, weight, alarm);
			printf("%s\n",query);
			res = mysql_perform_query(conn, query);
	
		sleep(1000000);
	  return 0;
		*/
	}

	void ICU::print(){
		cout << "ICU print << \t room temp : " << room_temp << "\t danger_situation : " << danger_situation << endl;
		patient1.print();
		patient2.print();
		nurse.print();
		cout << endl;
	}
	
	
	void ICU::situation_control(){

		int danger = get_danger_situation();
		int room_temperature = get_room_temp();
		int set_room_temp = 26;

		switch(danger){
			case 1: danger = nurse.danger_emergency(); break;
			case 2: danger = nurse.danger_ringer(); break;
			case 3: danger = nurse.danger_situation_off(); break;
			case 0: break;
		}

		if(set_room_temp < room_temperature){
			digitalWrite(FAN, HIGH);
		}
		else digitalWrite(FAN, LOW);

	}// 민지

	void ICU::get_sensor(){
		while(true){
			patient1.get_sensor();
			patient2.get_sensor();
			judge_danger();
		}
	}
/*#define DANGEROUS_TEMP 30.0
#define DANGEROUS_BEAT 130

#define GOOD	1
#define SOSO	2
#define BAD		3
#define BUTTON	5	*/
	void judge_danger(){
		if(this.patient1.get_temp() > DANGEROUS_TEMP)
			this.patient1.set_danger(2);
		else if(this.patient1.get_heart_rate() > DANGEROUS_BEAT)
			this.patient1.set_danger(1);
		else
			this.patient1.set_danger(0);
		
		if(this.patient2.get_infusion_solution() < DANGEROUS_INFUSION_WEIGHT)
			this.patient2.set_danger(2);
		else if(this.patient2.get_heart_rate() > DANGEROUS_BEAT)
			this.patient2.set_danger(1);
		/*else if(patient2.get_wake_up() == 1)
			patient2.set_danger(3);*/
		else
			this.patient2.set_danger(0);

		cout << "fever_patient danger is --"<<this.patient1.get_danger() <<"-- vegeta_patient danger is --"<<this.patient2.get_danger() <<"--"<<endl;

	}
}