/***********************************************
 * File name:   // book3.c
 * Author:      // doublepeng
 * Version:     // V1.0
 * Description: // 测试、验证结构体数组、指针的用法。
 * Other:       // 
 * Log:         // 2020/07/12
 *              // 新建。
 * 
 ************************************************/

#include<stdio.h> 
#include<string.h>
#include<stdlib.h> 

#define ERASE_PARAMETER_SIZE   (16U)
#define VERIFY_PARAMETER_SIZE  (40U)

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long  uint32;


#define ConfigIDType   uint32

typedef struct{
	uint16  RID;
	uint8   size;
	uint8   par[ERASE_PARAMETER_SIZE];
}EraseParameter_ST;

typedef struct{
	uint16  RID;
	uint8   size;
	uint8   par[VERIFY_PARAMETER_SIZE];
}VerifyParameter_ST;

typedef struct{
	ConfigIDType        config_ID;
	EraseParameter_ST   erase_par;
	VerifyParameter_ST  verify_par;
	uint32              FD_blocks;
}FlashDriverBlock_ST;

typedef struct{
	ConfigIDType        config_ID;
	EraseParameter_ST   erase_par;
	VerifyParameter_ST  verify_par;
	uint32              FD_blocks;
}DTConfigArray_ST;

FlashDriverBlock_ST m_flashdriverconfig;

DTConfigArray_ST * m_dataconfigArray;

uint8 check_flashdriver_config_info(uint8 *infodata)
{
    uint8 result = 0;

    if((m_flashdriverconfig.erase_par.size > 0) &&
	   (m_flashdriverconfig.erase_par.size < 14))
	{
		memcpy(&m_flashdriverconfig.erase_par.par, &infodata[7],
			   m_flashdriverconfig.erase_par.size);
	}
	else
	{
		return result;
	}
}

int main()
{   
    uint8 tempdata[40];
    uint8 i, j, k;

    //随意赋初值
    for(i = 0; i < 40; i++)
    {
        *(tempdata + i) = i;
    }
    m_flashdriverconfig.erase_par.size = 13U;

    //info函数的参数是指针变量，用于指向实参的地址，则传入一个数组的地址即可，
    //tempdata既是数组名也是数组的首地址，此处不用加取地址符&，要注意。
    check_flashdriver_config_info(tempdata);

    printf("The erase_par.size is: %d \n", m_flashdriverconfig.erase_par.size);
    for(j = 0; j < m_flashdriverconfig.erase_par.size; j++)
    {
        printf("The erase_par is:0x%x \n", m_flashdriverconfig.erase_par.par[j]);
    }
    /*********************************************************************************************/
    printf("\r\n");

    //这个结构体数组的大小，在定义的时候并不知道，程序在执行中才能确定，当确定后，就可以通过malloc函数
    //给它分配大小了。
    m_dataconfigArray = (DTConfigArray_ST *)malloc(sizeof(DTConfigArray_ST) * 20);

    for(k = 0; k < 20U; k++)
    {
        m_dataconfigArray[k].config_ID = k;


        printf("The m_dataconfigArray.config_ID is:0x%x \n", m_dataconfigArray[k].config_ID);
    }
    /*********************************************************************************************/
}