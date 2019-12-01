#include "vegetative_state.h"

namespace han
{
	void Vegetative::aduino_setting(string device_port){
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
		name = "minji";
		danger = 0;
	}


	void Vegetative::get_sensor(){
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
				ptr = strchr(buf, '!');
				strncpy(bufStr,ptr+1,3);
				if(bufStr[2]==',')
					bufStr[2]='\n';
				else bufStr[3]='\n';
				m.lock();
				heart_rate = atoi(bufStr);
				m.unlock();

				ptr = strchr(buf, '@');
				strncpy(bufStr,ptr+2,3);
				bufStr[3]='\n';
				m.lock();
				infusion_solution = atof(bufStr);
				printf("vegetative_patient ------ heart : %d , infusion_solution : %lf",heart_rate, infusion_solution);
				cout<<endl;
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

	void Vegetative::print(){
		cout << "Vegetative print << \t heart_rate : " << heart_rate << "\t infusion_solution : " << infusion_solution << "\t wake_up : " << wake_up << endl;
	}

	void Vegetative::give_order(){
		cout << "give_order" << endl;
	}
}