#include "common.h"
#include "include.h"
#include "data.h"

int16 AD_valu[ADCCOUNT] = {0};
int16 max_valu[ADCCOUNT] = {0};
int16 min_valu[ADCCOUNT] = {0};
int16 AD_N[ADCCOUNT] = {0};//归一化后值

/*中值滤波 均值滤波*/
void Read_ADC(void)
{
     int16  i,j,k,z,temp;
     int16  ad_valu[ADCCOUNT][3],ad_mid[ADCCOUNT][4];
     
     
     //中值滤波
     for(z=0;z<4;z++)
     {
         for(i=0;i<3;i++)
         {
             ad_valu[0][i]=adc_once(AMP1,ADC_8bit);
             ad_valu[1][i]=adc_once(AMP2,ADC_8bit);
//             ad_valu[2][i]=adc_once(AMP3,ADC_8bit);
//             ad_valu[3][i]=adc_once(AMP4,ADC_8bit);
//             ad_valu[4][i]=adc_once(AMP5,ADC_8bit);
//             ad_valu[5][i]=adc_once(AMP6,ADC_8bit);
         }
    //冒泡排序
         for(i = 0; i < ADCCOUNT; i++)
         {
            for(j=0;j<2;j++)
            {
               for(k=0;k<2-j;k++)
               {
                  if(ad_valu[i][k] > ad_valu[i][k+1])
                  {
                     temp = ad_valu[i][k+1];
                     ad_valu[i][k+1] = ad_valu[i][k];
                     ad_valu[i][k] = temp;
                  }
               }
            }
         }
         
         //取中值
         for(i=0;i<ADCCOUNT;i++)
             ad_mid[i][z]=ad_valu[i][1];
     }
     
     
//均值滤波
     for(i=0;i<ADCCOUNT;i++)
         AD_valu[i]=0;
     
     for(i=0;i<ADCCOUNT;i++)
     {
         for(j=0;j<4;j++)
            AD_valu[i]+=ad_mid[i][j];
         AD_valu[i]/=4;
     }
}

//标定
void calibrate_max_min(void)
{
     int16 i,j;
     
     for(i=0;i<ADCCOUNT;i++)
     {
        max_valu[i]=0;
        min_valu[i]=10;
     }
     
     if(key_check(KEY_B) == KEY_DOWN)
     {
         while(key_check(KEY_A) == KEY_UP)
         {
             led(LED2,LED_ON);
             Read_ADC();
             
             for(j=0;j<ADCCOUNT;j++)
             {
                 if(AD_valu[j] > max_valu[j])
                    max_valu[j] = AD_valu[j];
                 
                 if(AD_valu[j] < min_valu[j])
                    min_valu[j] = AD_valu[j];
             }
             DELAY_MS(1);

             for(i=0;i<ADCCOUNT;i++)
             {
               printf("%d\t",max_valu[i]);
               printf("%d\t",min_valu[i]);
             }
             printf("\n");
         }
         
         flash_erase_sector(SECTOR_NUM3_MAX);
         flash_erase_sector(SECTOR_NUM4_MIN);
         for(i=0;i<ADCCOUNT;i++)
         {
             flash_write(SECTOR_NUM3_MAX, i*4, max_valu[i]);
             flash_write(SECTOR_NUM4_MIN, i*4, min_valu[i]);
         }
         led(LED2, LED_OFF);
     }
     
     else
     {
         for(i=0;i<ADCCOUNT;i++)
         {
             max_valu[i]=flash_read(SECTOR_NUM3_MAX,i*4,int16);
             min_valu[i]=flash_read(SECTOR_NUM4_MIN,i*4,int16);
         }
     }
}

//归一化处理
void normalize(void)
{
    int i;
    
    Read_ADC();
    
    for(i=0;i<ADCCOUNT;i++)
    {
         AD_N[i] = (int)(((float)(AD_valu[i] - min_valu[i])/(float)(max_valu[i] - min_valu[i]))*100); 
         if(AD_N[i] < 0)  AD_N[i] = 0 ;
         if(AD_N[i] > 100)  AD_N[i] = 100 ;
    }

}