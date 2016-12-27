#ifndef _MOTOR_H_
#define _MOTOR_H_



//***************************************************** 
//定义 PID 结构体 
//***************************************************** 
typedef struct   
{   
    int SetPoint; //设定目标  Desired Value   
    double Proportion; //比例常数  Proportional Const   
    double Integral; //积分常数  Integral Const   
    double Derivative; //微分常数  Derivative Const   
    int LastError; //Error[-1]   
    int PrevError; //Error[-2]   
} PID;

//电机相关定义
#define MOTOR_FTM   FTM0
#define Forward_PWM  FTM_CH3
#define Backward_PWM  FTM_CH4

#define MOTOR_HZ    500//Hz
#define MOTOR_DUTY  80

//***************************************************** 
//PID定义相关宏 
//***************************************************** 
#define P_DATA 100 
#define I_DATA 0.6 
#define D_DATA 1 

void PIT0_IRQHandler(void);
void IncPIDInit(void);
int16 IncPIDCalc(int16 NextPoint);

extern void motor_init(void);

#endif /* _MOTOR_H_ */