#include "common.h"
#include "include.h"

#define MOTOR_FTM   FTM0
#define Forward_PWM  FTM_CH3
#define Backward_PWM  FTM_CH4

#define MOTOR_HZ    500//Hz
#define MOTOR_DUTY  80

void PIT0_IRQHandler(void);

void main()
{

    ftm_pwm_init(MOTOR_FTM, Forward_PWM,MOTOR_HZ,0);      //初始化 电机 PWM
    ftm_pwm_init(MOTOR_FTM, Backward_PWM,MOTOR_HZ,20);      //初始化 电机 PWM
    
    ftm_quad_init(FTM2);									//FTM2 正交解码初始化（所用的管脚可查 port_cfg.h ）
	pit_init_ms(PIT0, 20); 								//初始化PIT0，定时时间为： 10ms
	set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);		//设置PIT0的中断服务函数为 PIT0_IRQHandler
	enable_irq (PIT0_IRQn); 								//使能PIT0中断

    while(1)
    {
/*
        ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,100);
        ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,70);
        ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,70);
        ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM,100);
        DELAY_MS(1000);


        ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,70);
        ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,100);
        ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,100);
        ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM,70);
        DELAY_MS(1000);
*/

    }

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
    
    if(val>=0)
    {
        printf("\n正转：%d",val);
    }
    else
    {
        printf("\n反转：%d",-val);
    }

    PIT_Flag_Clear(PIT0);		//清中断标志位
}