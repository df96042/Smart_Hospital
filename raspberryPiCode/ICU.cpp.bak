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
			
			sprintf(query,"insert into %s (time, heartbeat,temperature,w_alarm, weight) value (%d,%d,%lf,%d,%lf);",patient_name, now,heart1,temp,w_alarm,weight);
			printf("%s\n",query);
			res = mysql_perform_query(conn, query);
		
			sprintf(query,"update Alarm set w_alarm=%d where patient_name='%s'",(int)weight, patient_name);
			//printf("%s\n",query);
			res = mysql_perform_query(conn, query);
	
	  //		while((row = mysql_fetch_row(res)) != NULL)
			//// 
			sprintf(query, "select state from Alarm where patient_name='%s'", patient_name);	
			res3 = mysql_perform_query(conn, query);
			row=mysql_fetch_row(res3);
			//printf("%s\n", query);
			nurse=atoi(row[0]);

	//		if(nurse == SOSO){
	//				printf("Thank you nurse!!\n");
	//				patient_state=SOSO;
	//		}
			mysql_free_result(res3);
			cnt=0;
			sprintf(query, "select * from %s order by time DESC limit 3", patient_name);
			res2 = mysql_perform_query(conn, query);
			
	//		printf("%s\n", query);
	
			while((row = mysql_fetch_row(res2)) != NULL){
					if(atof(row[2])>DANGEROUS_TEMP)///////////temp, heartbeat
						cnt++;
					else if(atoi(row[1])>DANGEROUS_BEAT)
						cnt++;
			}
			if(cnt==3){
				if(patient1.danger==GOOD){
						printf("Alarm!!\n");
						patient_state=BAD;	
				}
			}
			else{
					printf("I'm good\n");
					patient_state=GOOD;
			}
			sprintf(query, "update Alarm set state='%d' where patient_name='%s'", patient_state, patient_name);
			mysql_perform_query(conn, query);
			printf("%s\n", query);
		}
	
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