#include "Gyro.h"  
   
void mpu6500_Init(void)   
{  
    SPI2_init();
}  


uint8_t MPU6500_Init(void)  
{   
    uint8_t res, t=5;  
      
    mpu6500_Init(); 
      
    mpu6500_Write_Byte(MPU_PWR_MGMT1_REG,0X80); 
  //  delay_ms(100); //see «register map»page 42 - delay 100ms  
    //mpu6500_Write_Byte(MPU_SIGPATH_RST_REG,0X07);   //reset GYR+ACC+TEMP  
   // delay_ms(100); //page 42 - delay 100ms  
   // mpu6500_Write_Byte(MPU_USER_CTRL_REG, 0x11); //SET spi mode+Reset all gyro digital signal path, accel digital signal path, and temp  
   // delay_ms(1000);  
      
    /*res=mpu6500_Read_Byte(MPU_DEVICE_ID_REG);  
    if(res == 0x70) 
    {  
 
          
        MPU_Set_Gyro_Fsr(0);

     //   delay_ms(10);  
        MPU_Set_Accel_Fsr(0); 
		
       // delay_ms(10);  
        mpu6500_Write_Byte(MPU_CFG_REG,0X03);   

       // delay_ms(10);   
        mpu6500_Write_Byte(MPU_ACCEL_CFG2_REG,0X03);    //Acc Fs=1khz, bandtidth=41hz  
    
			// delay_ms(10);  
        //mpu6500_Write_Byte(MPU_INTBP_CFG_REG,0XA0);   //INT???????,????  
       // delay_ms(10);  
        //mpu6500_Write_Byte(MPU_INT_EN_REG,0X01);  //raw data inter open  
       // delay_ms(10);  
        //mpu6500_Write_Byte(MPU_PWR_MGMT1_REG,0X01);   //??CLKSEL,PLL X????  
       // delay_ms(10);  
        mpu6500_Write_Byte(MPU_PWR_MGMT2_REG, 0X00); //??????????  
      //  delay_ms(10);  
        MPU_Set_Rate(200);                      //??????200Hz  
        //delay_ms(10);  
    }  
    else   
    {  
        printf("ERROR! mpu6500_ADDR IS %x\n", mpu6500_Read_Byte(MPU_DEVICE_ID_REG));  
        return 1; //????  
    }  
  
    //just for test --yulong 2017/9/20  
    //loop all the time(send data to com)  
    while(1)  
    {  
        short accx_original=0, accy_original=0, accz_original=0;  
        uint16_t ACC_DATA[7];  
        uint8_t raw_datas[14]={0}; //acc*6+temp*2+gyr*6  
        uint8_t res;  
          
        res = mpu6500_Read_Byte(MPU_INT_STA_REG); //??????????????.???????????  
        //printf("int status:%x\n", res);  
       // delay_us(10);  
        if(res == 0x01) //??ready  
        {  
            mpu6500_Read_Len(MPU_ACCEL_XOUTH_REG, 8, &raw_datas[0]);  
         //   delay_us(10);  
            mpu6500_Read_Len(MPU_GYRO_XOUTH_REG, 6, &raw_datas[8]);  
           // delay_us(10);  
  
            ACC_DATA[0]=((uint16_t)raw_datas[0]<<8)|raw_datas[1];//?????  
            ACC_DATA[1]=((uint16_t)raw_datas[2]<<8)|raw_datas[3];  
            ACC_DATA[2]=((uint16_t)raw_datas[4]<<8)|raw_datas[5];  
            ACC_DATA[3]=((uint16_t)raw_datas[8]<<8)|raw_datas[9];//?????  
            ACC_DATA[4]=((uint16_t)raw_datas[10]<<8)|raw_datas[11];  
            ACC_DATA[5]=((uint16_t)raw_datas[12]<<8)|raw_datas[13];  
            ACC_DATA[6]=((uint16_t)raw_datas[6]<<8)|raw_datas[7]; //????  
            
        }  
    }  */
    return 0;  
}  

/*uint8_t MPU6500_Init(void)  
{  
    MPU6500_Init();                 
printf("success1 mpu6500_ADDR IS %x\n", mpu6500_Read_Byte(MPU_DEVICE_ID_REG));	//MPU6500 IO??SPI???  
      
    if(mpu6500_Read_Byte(MPU_DEVICE_ID_REG) == 0x70)          //?????6500???  
    {         
        mpu6500_Write_Byte(MPU_PWR_MGMT1_REG,0X80);         //????,??MPU6500  
    
        mpu6500_Write_Byte(MPU_SIGPATH_RST_REG,0X07);//??????????????  
        //Delay_Ms(100);  
        mpu6500_Write_Byte(MPU_PWR_MGMT1_REG,0X01);         //?????  
        mpu6500_Write_Byte(MPU_PWR_MGMT2_REG,0X00);         //??????????  
        mpu6500_Write_Byte(MPU_CFG_REG ,0X02);                     //????? 0x02 92hz (3.9ms delay) fs=1khz  
        mpu6500_Write_Byte(MPU_SAMPLE_RATE_REG,0X00);             //???1000/(1+0)=1000HZ  
        mpu6500_Write_Byte(MPU_GYRO_CFG_REG ,0X18);        //??????? 0X18 ??2000?  
        mpu6500_Write_Byte(MPU_ACCEL_CFG_REG,0x10);       //???????? 0X00 ??8g  
        mpu6500_Write_Byte(MPU_ACCEL_CFG2_REG,0x00);      //??????1khz ???460hz (1.94ms delay)  
        return 0;  
    }  
    else {		
			printf("ERROR! mpu6500_ADDR IS %x\n", mpu6500_Read_Byte(MPU_DEVICE_ID_REG));
			return 1;  
		}
} */ 


void MPU_Set_Gyro_Fsr(uint8_t fsr)  
{  
     mpu6500_Write_Byte(MPU_GYRO_CFG_REG, fsr<<3);//??????????    
}  
//??MPU6050???????????  
//fsr:0,±2g;1,±4g;2,±8g;3,±16g  
//???:0,????  
//    ??,????   
void MPU_Set_Accel_Fsr(uint8_t fsr)  
{  
    mpu6500_Write_Byte(MPU_ACCEL_CFG_REG, fsr<<3);//?????????????    
}  
  
void MPU_Set_LPF(uint16_t lpf)  
{  
    uint8_t data=0;  
    if(lpf>=188)data=1;  
    else if(lpf>=98)data=2;  
    else if(lpf>=42)data=3;  
    else if(lpf>=20)data=4;  
    else if(lpf>=10)data=5;  
    else data=6;   
    mpu6500_Write_Byte(MPU_CFG_REG,data);//?????????    
}  


void MPU_Set_Rate(uint16_t rate)  
{  
    uint8_t data;  
    if(rate>1000)rate=1000; 
    if(rate<4)rate=4;  
    data=1000/rate-1; //???????  
    mpu6500_Write_Byte(MPU_SAMPLE_RATE_REG,data);   
    //return MPU_Set_LPF(rate/2);   //????LPF???????  
}  
  
  

void mpu6500_Read_Len(uint8_t reg, uint8_t len,uint8_t *buf)  
{   
      
    while(len)  
    {  

       // SPI3_ReadWriteByte(reg|0x80);//r ????1  
       // *buf=SPI3_ReadWriteByte(0x00);  
	      SPI_SendByte(reg|0x80, SPI2);
			  *buf = SPI_ReadByte(SPI2);  

        len--;  
        buf++;  
        reg++;  

    }     
}  
  
  
   
//spi write a byte  
void mpu6500_Write_Byte(uint8_t reg,uint8_t data)                  
{   
   
	  SPI_SendByte(reg, SPI2);
	printf("%d",reg);
	  SPI_SendByte( data, SPI2);
   // SPI3_ReadWriteByte(reg); //w ????0  
    //SPI3_ReadWriteByte(data);  

}  
  
//spi read a byte  
uint8_t mpu6500_Read_Byte(uint8_t reg)  
{  
    uint8_t tmp=0;  
	  SPI_SendByte(reg|0x80,SPI2 );
	
	  tmp=SPI_ReadByte(SPI2);
  
    //SPI3_ReadWriteByte(reg|0x80);//r ????1  
    //tmp=SPI3_ReadWriteByte(0xff);  
 
    return tmp;  
}  