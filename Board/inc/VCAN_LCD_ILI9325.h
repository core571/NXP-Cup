/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       VCAN_LCD_ILI9325.h
 * @brief      LCD ILI9325函数库
 * @author     山外科技
 * @version    v5.0
 * @date       2013-09-03
 */
#ifndef _VCAN_LCD_ILI9325_H_
#define _VCAN_LCD_ILI9325_H_

#include "VCAN_LCD.h"
#include "MK60_flexbus.h"


//用户配置
#define ILI9325_DIR_DEFAULT     1      //定义默认方向 (0~3)


#if (USE_LCD == LCD_ILI9325)

/*********************** API接口 ******************************/
//提供API接口给LCD调用

#define LCD_H                   ILI9325_get_h()                 //高
#define LCD_W                   ILI9325_get_w()                 //宽

#define LCD_INIT()              LCD_ILI9325_init()              //初始化
#define LCD_PTLON(site,size)    LCD_ILI9325_ptlon(site,size)    //开窗
#define LCD_RAMWR()             LCD_ILI9325_WR_CMD(0x22)        //写模式
#define LCD_WR_DATA(data)       LCD_ILI9325_WR_DATA(data)       //写数据
#define LCD_WR_CMD(cmd)         LCD_ILI9325_WR_CMD(cmd)         //命令
#define LCD_SET_DIR(opt)        LCD_ILI9325_dir(opt)            //方向

#define LCD_DIR                 ILI9325_get_dir()               //获取方向

#endif //(USE_LCD == LCD_ILI9325)

/********************* ILI9325内部实现 ***********************/

#define LCD_ILI9325_CMD_ADDR                    FB_8080_CMD
#define LCD_ILI9325_DATA_ADDR                   FB_8080_DATA

#define LCD_ILI9325_WR_CMD(cmd)         do{LCD_ILI9325_CMD_ADDR  = cmd ;}while(0)
#define LCD_ILI9325_WR_DATA(data)       do{LCD_ILI9325_DATA_ADDR = data;}while(0)


extern void     LCD_ILI9325_init();
extern void     LCD_ILI9325_dir(uint8 option);
extern void     LCD_ILI9325_ptlon(Site_t site, Size_t size);
extern uint16   ILI9325_get_h();
extern uint16   ILI9325_get_w();
extern uint8    ILI9325_get_dir();




#endif //   _VCAN_LCD_ILI9325_H_