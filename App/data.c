#include "common.h"
#include "include.h"
#include "data.h"

int16 AD_valu[ADCCOUNT];

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