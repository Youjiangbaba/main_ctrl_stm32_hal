#include "user_Config.h"                 //�û�����ͷ�ļ�����������Ӳ��������Դ,λ����Ŀ�ļ�����
#include "TFT28.h"											 //TFT��صĺ�������ͷ�ļ�
#include "GUI.h"											   //TFTҺ��GUI��ͼ��������ͷ�ļ�
#include "TOUCH.h"											 //�����������ͷ�ļ�
#include "cmsis_os.h"

#define delayms  osDelay                    //HAL_Delay�ȴ�ʱ�䲻ִ�������߳�   osDelay 
extern uint8_t  TEMP;                     //��ʾ�¶�
extern  uint8_t SHI,GE;

extern uint8_t start;
extern uint8_t EN_PUT;

uint8_t cmd,flag_print = 0,flag_stop = 0;
uint xm,ym;

unsigned int Device_code;                //TFT����IC�ͺţ�2.8��ΪILI9328;

void display_init(void)
{
  Device_code=0x9320;                					//TFT����IC�ͺ�
  TFT_Initial();                     					//��ʼ��LCD
  start_7843();                      					//�򿪴�������	
  CLR_Screen(Black);               					//�ñ���ɫ����
  LCD_PutString24(110,100,"UESTC",Red,Black); //��ӭ���棬24x24��С���֣���ģ�������С���� 
	HAL_Delay(1000);
//	cmd = 15;
  CLR_Screen(White);                                       	//�ñ���ɫ����
	cmd = 0;
}

void one(uint cmd)
{
	switch(cmd)
	{
		case 0:LCD_PutString24(290,20,"0",Black,White);break;
		case 1:LCD_PutString24(290,20,"1",Black,White);break;
		case 2:LCD_PutString24(290,20,"2",Black,White);break;
		case 3:LCD_PutString24(290,20,"3",Black,White);break;
		case 4:LCD_PutString24(290,20,"4",Black,White);break;
		case 5:LCD_PutString24(290,20,"5",Black,White);break;
		case 6:LCD_PutString24(290,20,"6",Black,White);break;
		case 7:LCD_PutString24(290,20,"7",Black,White);break;
		case 8:LCD_PutString24(290,20,"8",Black,White);break;
		case 9:LCD_PutString24(290,20,"9",Black,White);break;
		case 10:LCD_PutString24(290,20,"10",Black,White);break;
		default:LCD_PutString24(290,20,"BUSY",Black,White);break;
	}
}

void my_gui(void)
{
	       GUIline(0,0,120,0,Black);   //���ߺ���
         GUIline(0,0,0,30,Black);   //���ߺ���
         GUIline(0,30,120,30,Black);   //���ߺ���
         GUIline(120,0,120,30,Black);   //���ߺ���
  //       GUIfull(0,0,120,30,Yellow);      

	
         GUIline(130,90,190,90,Black);   //���ߺ���
         GUIline(130,90,130,150,Black);   //���ߺ���
         GUIline(130,150,190,150,Black);   //���ߺ���
         GUIline(190,90,190,150,Black);   //���ߺ���
 //        GUIfull(130,90,190,150,Green); 
	
         LCD_PutString24(140,110,"START",Black,Green);
	       LCD_PutString24(1,1,"TEMP:",Black,Yellow);
          
//	       while(1)
//				 {
//					 LCD_PutSingleChar(50,1,SHI,0x0000,0XFFFF);
//					 LCD_PutSingleChar(60,1,GE,0x0000,0XFFFF);
//					 if((TEMP > 34)&&(TEMP < 40)) break;
//				 }
				if(Getpix()==1)  
				{
				 if(ly < 190 && ly > 130 && lx > 90 && lx < 150)
					 { 
						 CLR_Screen(White);  
			     while(1)
				     {		  		
							 
               GUIline(0,0,120,0,Black);   //���ߺ���
               GUIline(0,0,0,30,Black);   //���ߺ���
               GUIline(0,30,120,30,Black);   //���ߺ���
               GUIline(120,0,120,30,Black);   //���ߺ���
        
               GUIline(130,90,190,90,Black);   //���ߺ���
               GUIline(130,90,130,150,Black);   //���ߺ���
               GUIline(130,150,190,150,Black);   //���ߺ���
               GUIline(190,90,190,150,Black);   //���ߺ���
               if(EN_PUT)
                   LCD_PutString24(150,110,"PUT ",Black,White);
							 else  if(EN_PUT == 0)
                   LCD_PutString24(150,110,"BUSY",Black,White);
               LCD_PutString24(0,0,"STATE:",Black,White);	
							 
		      		 GUIline(0,180,80,180,Black);   //���ߺ���
               GUIline(0,180,0,240,Black);   //���ߺ���
               GUIline(80,180,80,240,Black);   //���ߺ���
               GUIline(0,240,80,240,Black);   //���ߺ���
        
               GUIline(260,180,320,180,Black);   //���ߺ���
               GUIline(260,180,260,240,Black);   //���ߺ���
               GUIline(320,180,320,240,Black);   //���ߺ���
               GUIline(260,240,320,240,Black);   //���ߺ���
					
               GUIline(280,0,320,0,Black);   //���ߺ���
               GUIline(280,0,280,40,Black);   //���ߺ���
               GUIline(280,40,320,40,Black);   //���ߺ���
               GUIline(320,0,320,40,Black);   //���ߺ���
					
				       LCD_PutString24(270,200,"PRINT",Black,White);
               LCD_PutString24(20,200,"STOP",Black,White);
							 one(cmd);

	            if(Getpix()==1)  
				        {
									delayms(100);
                 if(ly < 320 && ly > 260 && lx > 180 && lx < 240)
					       {    
						        flag_print++;  //dayin
                 }
					       if(ly < 60 && ly > 0 && lx > 180 && lx < 240)
						     {
									 flag_stop = 1; //stop
								 }
								 
								 if(ly < 190 && ly > 130 && lx > 90 && lx < 150)
					       {    
						          cmd++;
									    start = cmd;                                           //�Ƿ��Ƭ
									    one(cmd);
                 }
								 
               }								
			      }
//				      CLR_Screen(White); 
           }       
        }  
}