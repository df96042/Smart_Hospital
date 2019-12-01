#include "fever.h"

namespace han{

	void Fever::aduino_setting(string device_port){
		//get filedescriptor
		if ((fd = serialOpen (device_port.c_str(), 115200)) < 0){
			fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
			exit(1); //error
		}
 
		/*//setup GPIO in wiringPi mode
		if (wiringPiSetup () == -1){
			fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
			exit(1); //error
		}*/

		//setup the others
		name = "yohan";
		danger = 0;
	}


	void Fever::get_sensor(){
		char buf[200], flushBuf[200]={0, };
		char *ptr;
		char bufStr[20];
		int i = 0;
		unsigned long Atime=0;

		while(1){
			// Pong every 3 seconds
			if(millis()-Atime>=3000){
				serialPuts (fd, "Pong!\n");
				// you can also write data from 0-255
				// 65 is in ASCII 'A'
				serialPutchar (fd, 65);
				Atime=millis();
			}
			// read signal	
			if(serialDataAvail (fd)){
		
				//char newChar = serialGetchar (fd);
				//printf("%c", newChar);
		
				buf[i++] = serialGetchar(fd);
				//cout << buf[i-1];
				if(i>40){
					/////////////////////////////error
					ptr = strchr(buf, '!');
					/////////////////////////////error
					strncpy(bufStr,ptr+1,3);
					if(bufStr[2]==',')
					bufStr[2]='\n';
					else bufStr[3]='\n';
					m.lock();
					heart_rate = atoi(bufStr);
					m.unlock();
	
					ptr = strchr(buf, '#');
					strncpy(bufStr,ptr+1,5);
					bufStr[5]='\n';
					m.lock();
					temp = atof(bufStr);
					printf("fever_patient ------ heart : %d , temp : %lf",heart_rate, temp);
					cout << endl;
					m.unlock();

					strcpy(buf, flushBuf);
					i = 0;
					fflush(stdout);
					break;
				}
			//fgets(bufStr, sizof(bufStr),stdout);
			fflush(stdout);
			}
		}	
	}

	void Fever::print(){
		cout << "Fever print << \t heart_rate : " << heart_rate << "\t temp : " << temp << endl;
	}


	void Fever::give_order(){
		cout << "give_order" << endl;
	}
}