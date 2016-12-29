#include "common.h"
#include "include.h"
#include "motor.h"


//***************************************************** 
//声明 PID 实体 
//***************************************************** 
PID sPID;   
PID *sptr = &sPID;
int16 PWMOUT = 0;


void motor_init(void)
{
    //motor init
    ftm_pwm_init(MOTOR_FTM, Forward_PWM,MOTOR_HZ,0);      //初始化 电机 PWM
    ftm_pwm_init(MOTOR_FTM, Backward_PWM,MOTOR_HZ,0);      //初始化 电机 PWM
    
    //PIDInit
    IncPIDInit();
    
    //encoder init
    ftm_quad_init(FTM2);									//FTM2 正交解码初始化（所用的管脚可查 port_cfg.h ）
	pit_init_ms(PIT0, 20); 								//初始化PIT0，定时时间为： 10ms
	set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);		//设置PIT0的中断服务函数为 PIT0_IRQHandler
	enable_irq (PIT0_IRQn); 								//使能PIT0中断
}

/*!
 *	@brief		PIT0中断服务函数
 *	@since		v5.0
 */
void PIT0_IRQHandler(void)
{
    int16 val;
    val = ftm_quad_get(FTM2);		   //获取FTM 正交解码 的脉冲数(负数表示反方向)
    ftm_quad_clean(FTM2);
    
    PWMOUT += IncPIDCalc(val);
    
    if(PWMOUT>99||PWMOUT<-99) 
    {
        PWMOUT=PWMOUT>0?99:-99;
    }
    
    if(PWMOUT > 0)
    {
        ftm_pwm_duty(MOTOR_FTM,Forward_PWM,PWMOUT);		 
        ftm_pwm_duty(MOTOR_FTM,Backward_PWM,0);
    }
	else
    {
    	ftm_pwm_duty(MOTOR_FTM,Forward_PWM,0); 
        ftm_pwm_duty(MOTOR_FTM,Backward_PWM,-PWMOUT);
    }
    
    //printf("%d\n",val);

    vcan_sendware((uint8_t *)&val, sizeof(val));//virtual oscilloscope

    PIT_Flag_Clear(PIT0);		//清中断标志位
}

//***************************************************** 
//PID 参数初始化 
//***************************************************** 
void IncPIDInit(void)
{   
    sptr->LastError = 0; //Error[-1]   
    sptr->PrevError = 0; //Error[-2]   
    sptr->Proportion = P_DATA; //比例常数  Proportional Const   
    sptr->Integral = I_DATA; //积分常数 Integral Const   
    sptr->Derivative = D_DATA; //微分常数  Derivative Const   
    sptr->SetPoint =100;    //目标是 100 
}

//***************************************************** 
//增量式 PID 控制设计   
//***************************************************** 
int16 IncPIDCalc(int16 NextPoint)
{   
    int16 iError, iIncpid; //当前误差   
    iError = sptr->SetPoint - NextPoint; //增量计算   

/*    //△Uk=A*e(k)+B*e(k-1)+C*e(k-2) 
    iIncpid = sptr->Proportion * iError //E[k]项   
            - sptr->Integral * sptr->LastError //E[k－1]项   
            + sptr->Derivative * sptr->PrevError; //E[k－2]项  
*/
    
// PID original function
    iIncpid = sptr->Proportion * (iError - sptr->LastError) //E[k]项   
            + sptr->Integral * iError //E[k－1]项   
            + sptr->Derivative * (iError - 2 * sptr->LastError + sptr->PrevError); //E[k－2]项   
    sptr->PrevError = sptr->LastError;      //存储误差，用于下次计算   
    sptr->LastError = iError;   
    return(iIncpid);                        //返回增量值   
} 
