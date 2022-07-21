#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
int main(void)
{

    HANDLE hComm;                       // Handle to the Serial port
    char ComPortName[] = "COM4"; // Name of the Serial port(May Change) to be opened,
    BOOL Status;
    DWORD dwEventMask;                  // Event mask to trigger
    char TempChar;                      // Temperory Character
    char SerialBuffer[256];             // Buffer Containing Rxed Data
    DWORD NoBytesRead;                  // Bytes read by ReadFile()
    int i = 0;
    
    
    printf("## WELCOME TO GTU ARDUINO LAB ##\n## STUDENT NAME: ABDULLAH MUHAMMET YIGIT ##\n## PLEASE SELECT FROM THE FOLLOWING ##\n## MENU :");
    printf("\n(1) TURN ON LED ON ARDUINO\n(2) TURN OFF LED ON ARDUINO\n(3) FLASH ARDUINO LED 3 TIMES");
    printf("\n(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO\n(5) Button press counter (bonus item)\n(0) EXIT\nPLEASE SELECT:\n");

    hComm = CreateFile(ComPortName,                  // Name of the Port to be Opened
                       GENERIC_READ | GENERIC_WRITE, // Read/Write Access
                       0,                            // No Sharing, ports cant be shared
                       NULL,                         // No Security
                       OPEN_EXISTING,                // Open existing port only
                       0,                            // Non Overlapped I/O
                       NULL);                        // Null for Comm Devices

    DCB dcbSerialParams = {0}; // Initializing DCB structure
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    Status = GetCommState(hComm, &dcbSerialParams); //retreives  the current settings

    dcbSerialParams.BaudRate = CBR_9600;   // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;          // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT; // Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY;     // Setting Parity = None

    Status = SetCommState(hComm, &dcbSerialParams); //Configuring the port according to settings in DCB

    COMMTIMEOUTS timeouts = {0};

    timeouts.ReadIntervalTimeout = 100;
    timeouts.ReadTotalTimeoutConstant = 100;
    timeouts.ReadTotalTimeoutMultiplier = 20;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    char lpBuffer[5] ;       // lpBuffer should be  char or byte array, otherwise write wil fail
 	
	DWORD dNoOFBytestoWrite;     // No of bytes to write into the port
	DWORD dNoOfBytesWritten = 0; // No of bytes written to the port

    int input = 1,count = 0,j=0,b;  
	char tempBuffer[5],a;
        
    while(input != 0){
    	
		if(count == 0){
			printf("Choice : ");
			scanf("%d",&input);
		}
    	
    	switch(input){
    		
    		case 1: lpBuffer[0] = 'a' ;
    				dNoOFBytestoWrite = sizeof(lpBuffer); // Calculating the no of bytes to write into the port

                	Status = WriteFile(hComm, lpBuffer, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);
                    
                    if(count != 0) input = 2;
                    
    				break;
    			
    		
    		case 2: lpBuffer[0] = 'b' ;

    				dNoOFBytestoWrite = sizeof(lpBuffer);

                	Status = WriteFile(hComm, lpBuffer, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);
                        
                    if(count != 0){
                        input = 1;
                        count--;
					}
                        
    				break;
    				
     		case 3: count = 3;
					input = 1;
    				break;  
					
			case 4: lpBuffer[0] = 'd' ;
					dNoOFBytestoWrite = sizeof(lpBuffer);
					Status = WriteFile(hComm, lpBuffer, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);
					
					printf("Number = ");
					scanf("%s",&tempBuffer);					

    				dNoOFBytestoWrite = sizeof(tempBuffer);
                	Status = WriteFile(hComm, tempBuffer, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);

    				Status = SetCommMask(hComm, EV_RXCHAR);
					Status = WaitCommEvent(hComm, &dwEventMask, NULL); 				

				    i = 0;
				    /*This do-while gets the square of number's digits last to first and fills them into an array*/
				     do
				    {
				       	Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
				        SerialBuffer[i] = TempChar;				            
				        i++;
				    } while (SerialBuffer[i-1] >= 0);
				        
				    printf("Square of number is = ");
				    if(tempBuffer[0]-48 == 0)printf("0");
				    else{						
					    while((i-2) >= 0){
					      	printf("%d",SerialBuffer[i-2]);
					       	i--;
						}
					}
					printf("\n");
					break;
					
			case 5: lpBuffer[0] = 'e' ;
					dNoOFBytestoWrite = sizeof(lpBuffer);
					
					int button_number = 0;
					
					printf("Button number is : %d\n",button_number);
					
					while(button_number < 10){					
						Status = WriteFile(hComm, lpBuffer, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);
						
	    				Status = SetCommMask(hComm, EV_RXCHAR);
						Status = WaitCommEvent(hComm, &dwEventMask, NULL); 	
						
						Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);								
				
						printf("Button number is : %d\n",button_number = TempChar);
					}
					break;
			
			default:if(input != 0)printf("Please enter a valid input : "); 
					break;    				
		}
    	
    	for(j=0;j<5;j++) lpBuffer[j] = '\0';
    	
	}

    CloseHandle(hComm); 
    
    return 0;
}
