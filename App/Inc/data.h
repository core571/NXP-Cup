#ifndef _DATA_H_
#define _DATA_H_


//***************************************************** 
//定义 SERVO_PID 结构体 
//***************************************************** 
typedef struct   
{   
    float Proportion; //比例常数  Proportional Const   
    float Derivative; //微分常数  Derivative Const  
    float A;          //P=A * x^2 + C
    float C;
    int Error; //Error[-1]   
}PD;

//***************************************************** 
//PD定义相关宏 
//***************************************************** 
#define A_DATA 0.4
#define C_DATA 10.5
#define SD_DATA 10.6

#define AMP1     ADC0_SE8        //PTB0右边
#define AMP2     ADC0_SE9        //PTB1
#define AMP3     ADC0_SE12       //PTB2
#define AMP4     ADC0_SE13       //PTB3
#define AMP5     ADC1_SE10       //PTB4
#define AMP6     ADC1_SE11       //PTB5

#define ADCCOUNT 6 //sensor count

//flash
#define SECTOR_NUM3_MAX  (FLASH_SECTOR_NUM-3)
#define SECTOR_NUM4_MIN  (FLASH_SECTOR_NUM-4)
#define SECTOR_NUM5_PD  (FLASH_SECTOR_NUM-5)

extern int16 AD_valu[ADCCOUNT];
extern int16 AD_N[ADCCOUNT];
extern PD S_PD;
extern PD *SPointer;
extern int32 SA_Integer, SC_Integer, SD_Integer;


void Read_ADC(void);
void calibrate_max_min(void);
void normalize(void);
int16 get_bias(void);
int16 Servo_PD(int16 bias);
void Servo_PD_Init(void);
char OutlineFlag();

#endif /* _DATA_H_ */