#include "taskFlyport.h"
#include "time.h"


time_t now;
struct tm *ts;
struct tm mytime;
DWORD epoch = 0;
// Para configurar GMT deve-se somar
// ou subtrair de acordo com zona GTM
// para Brazil deve-se subtrair por 3
int GMT_hour_adding = -3;


void leSensorTemperatura()
{
	return 0;
	
}


void rtccConfig()
{
	epoch = SNTPGetUTCSeconds();
	now =  (time_t)epoch;
	ts = localtime(&now);
	
	ts->tm_hour = (ts->tm_hour + GMT_hour_adding);
	
	if(ts->tm_hour > 24)
	{
		ts->tm_hour = ts->tm_hour - 24;
	}
	else if( ts->tm_hour < 0)
	{
		ts->tm_hour = ts->tm_hour +24;
	}
	
	
	RTCCSet(ts);
	//RTCCAlarmConf(ts,REPEAT_INFINITE, EVERY_HALF_SEC, &set_analogOutput);
	
	
}

void FlyportTask()
{
	float tempCelsius = 0;
	//UDP Udpsock = INVALID_SOCKET;
	char msg[500];
	//int cnt = 0;
	BOOL flagErr = FALSE;
	int myAdcValue = 0;
	
	
	// Flyport connects to default network
	WFConnect(WF_DEFAULT);
	while(WFGetStat() != CONNECTED);
	while(!DHCPAssigned);
	
	UARTWrite(1,"Tentando UDP!\n");
	int UdpSocket = UDPClientOpen("192.168.43.33","5555");
	int UdpRxLength = 0;
	
	while(1){
		vTaskDelay(50);
		
		
		//UARTWrite(1,"Flyport Wi-fi connected UDP...hello world!\r\n");
		
		
		//LM35 Possui como saida 10mV para cada grau Cº
		myAdcValue = ADCVal(2);
		
		//Converte a temperatura em V para Cº
		tempCelsius = (myAdcValue *(5/1023))/0.01 ;
		
		
		
		
		sprintf(msg,"Flyport Wi-fi connected UDP temp: %f !\r\n", tempCelsius);
		
		UARTWrite(1,msg);
		
		
		//Cria mensagem para enviar para o servidor
		//sprintf(msg,"%s","Hello server aqui eh o Fly!!");
		
		//Connecta o cliente TCP ao servidor
		if(!UdpSocket)
		{
			UARTWrite(1, "Não foi possivel encontrar o servidor UDP\r\n");
		
		}
		
		
		
		if(flagErr)
		{
			UARTWrite(1,"\r\nTime error... \r\n");

		}
		
		//envia a mensagem
		
		
		UdpRxLength = UDPRxLen(UdpSocket);
		UDPWrite(UdpSocket,(BYTE*)msg,strlen(msg));
		
		sprintf(msg,"\r\nLength data: %d\r\n",UdpRxLength);
		UARTWrite(1,msg);
		
	}
		

}









