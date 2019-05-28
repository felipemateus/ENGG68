#include "taskFlyport.h"
#include "time.h"
//#include "rtcc.h"



char string_serial[60] = "waiting ...";
time_t now;
struct tm *ts;
struct tm mytime;

DWORD epoch = 0;
DWORD epochtime = 0xA2C2A;
char dateUTC[100];
char dateUTC1[50];

// Para configurar GMT deve-se somar
// ou subtrair de acordo com zona GTM
// para Brazil deve-se subtrair por 3
int GMT_hour_adding = 3;


void FlyportTask()
{
	// Flyport connects to default network
	WFConnect(WF_DEFAULT);
	while(WFGetStat() != CONNECTED);
	vTaskDelay(25);
	UARTWrite(1,"Flyport Wi-fi connected...hello world!\r\n");
	vTaskDelay(200);
	UARTWrite(1,string_serial);
	while(epoch <epochtime)
	{
		vTaskDelay(50);
		//lembrar de habilitar SNTP cliente no wizard
		epoch = SNTPGetUTCSeconds();
	}
	
	UARTWrite(1,"done!\r\n");
	//Para converter DWORD para forma amigável
	//DMWORD => time_t -> struct tm
	epoch =  SNTPGetUTCSeconds();
	now = (time_t)epoch;
	ts = localtime(&now);
	vTaskDelay(20);
	ts->tm_hour = (ts->tm_hour + GMT_hour_adding);
	
	if(ts->tm_hour > 24)
	{
		ts->tm_hour = ts->tm_hour - 24;
	}
	else if( ts->tm_hour < 0)
	{
		ts->tm_hour = ts->tm_hour +24;
	}
	
	sprintf( string_serial, "\nReceived date/time is: %s \r\n",asctime(ts));
	UARTWrite(1,string_serial);
	RTCCSet(ts);
	while(1)
	{
		vTaskDelay(1000);
		RTCCGet(&mytime);//pega o tempo e a data atual
		sprintf(string_serial,"\nAtual date/time is: %s \r\n",asctime(&mytime));
		UARTWrite(1,string_serial);
	}
		
	
	
	
}





