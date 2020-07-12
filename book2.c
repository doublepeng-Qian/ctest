/***********************************************
 * File name:   // book2.c
 * Author:      // doublepeng
 * Version:     // V1.0
 * Description: // 测试、验证结构体的用法。
 * Other:       // 
 * Log:         // 2020/07/10
 *              // 新建。
 * 
 ************************************************/
 #include<stdio.h> 
 #include<string.h>

 typedef unsigned char  uint8;
 typedef unsigned short uint16;
 typedef unsigned long  uint32;

 //消除内存空隙
 #pragma pack(1)
 struct msg_str{
    uint32  ID;
    uint16  length;
    uint8   data[64];
 };//为了验证字节对齐的问题，故意如此排布成员 
 
 
 int main()
 {
    struct msg_str *P_msg, CAN_msg, tmp_msg;

    printf("This is a test project!\n");
   
    /*********************************************************************************************/
    printf("int:%d \n short:%d \n char:%d \n", sizeof(int), sizeof(short), sizeof(char));

    printf("uint32:%d \n uint16:%d \n uint8:%d \n", sizeof(uint32), sizeof(uint16), sizeof(uint8));
    
    //输出结构体的大小，方式一
    printf("msg_str size: %d \n", sizeof(struct msg_str));

    //输出结构体的大小，方式二
    printf("msg_str size: %d \n", sizeof(CAN_msg));
    //总结：如果不对齐，结构体实际占用80字节；如果对齐，则实际占用74字节。
    /*********************************************************************************************/
    printf("\r\n");

    //初始化结构体变量
    memset(&CAN_msg, 0, sizeof(CAN_msg));

    CAN_msg.ID     = 0x18DA0034;
    CAN_msg.length = 8;
    strcpy(CAN_msg.data, "CAN messages.");

    printf("CAN_msg.ID:0x%08X \n", CAN_msg.ID);
    printf("CAN_msg.length:%d \n", CAN_msg.length);
    printf("CAN_msg.data:%s \n", CAN_msg.data);
    
    printf("\r\n");
    
    P_msg = &CAN_msg;
    
    P_msg->ID      = 0x18DA00DF;
    P_msg->length  = 40;
    strcpy(P_msg->data, "J1939 protocol received frames.");

    printf("P_msg->ID:0x%08X \n", P_msg->ID);
    printf("P_msg->length:%d \n", P_msg->length);
    printf("P_msg->data:%s \n", P_msg->data);
    printf("\r\n");

    //验证memcpy函数，拷贝结构体变量
    memcpy(&tmp_msg, &CAN_msg, sizeof(struct msg_str));

    printf("tmp_msg.ID:0x%08X \n", tmp_msg.ID);
    printf("tmp_msg.length:%d \n", tmp_msg.length);
    printf("tmp_msg.data:%s \n", tmp_msg.data);
    //总结：注意CAN_msg中的值已经被改变了。
    /*********************************************************************************************/
}



