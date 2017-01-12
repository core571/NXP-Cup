#include "common.h"
#include "include.h"

void uart4_handler(void)
{
    char ch;
    int P_Integer, I_Integer, D_Integer;
    if(uart_query    (UART4) == 1)  
    {
        uart_getchar   (UART4, &ch); 
		if(ch=='1')
			sptr->Proportion+=0.05;
		else if(ch=='2')
			sptr->Proportion-=0.05;
		else if(ch=='4')
			sptr->Integral+=0.1;
		else if(ch=='5')
			sptr->Integral-=0.1;
		else if(ch=='7')
			sptr->Derivative+=0.1;
		else if(ch=='8')
			sptr->Derivative-=0.1;
        
       P_Integer =(int) sptr->Proportion;//整数部分
       I_Integer =( int) sptr->Integral;//整数部分
       D_Integer =( int) sptr->Derivative;//整数部分
       printf("\t%d.%03d",(int) sptr->Proportion,(int)((sptr->Proportion-(int) sptr->Proportion)*1000));
       printf("\t%d.%04d",( int) sptr->Integral,(int)((sptr->Integral-( int) sptr->Integral)*10000));
       printf("\t%d.%04d",( int) sptr->Derivative,(int)((sptr->Derivative-( int) sptr->Derivative)*10000));
       printf("\n");
       
    //sptr->SetPoint =100;    //目标是 100 

                          
    }
}

void main()
{
    set_vector_handler(UART4_RX_TX_VECTORn,uart4_handler);	 
	uart_rx_irq_en (UART4); 
    
    /************************ LCD 液晶屏 初始化  ***********************/
    LCD_init();

    

    motor_init();
    
    
    while(1)
    {
        deal_key_event();
    }

}


