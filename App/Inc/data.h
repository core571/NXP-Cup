#ifndef _DATA_H_
#define _DATA_H_

#define AMP1     ADC0_SE8        //PTB0ср╠ъ
#define AMP2     ADC0_SE9        //PTB1
#define AMP3     ADC0_SE12       //PTB2
#define AMP4     ADC0_SE13       //PTB3
#define AMP5     ADC1_SE10       //PTB4
#define AMP6     ADC1_SE11       //PTB5

#define ADCCOUNT 2 //sensor count

//flash
#define SECTOR_NUM3_MAX  (FLASH_SECTOR_NUM-3)
#define SECTOR_NUM4_MIN  (FLASH_SECTOR_NUM-4)

extern int16 AD_valu[ADCCOUNT];

extern void Read_ADC(void);
extern void calibrate_max_min(void);
extern void normalize(void);

#endif /* _DATA_H_ */