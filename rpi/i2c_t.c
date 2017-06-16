#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
  
char WriteBuf[2] = {0x00};  

static int check_status(int ret)
{
	int status = -1;
	if(ret == BCM2835_I2C_REASON_OK)
		status = 0;
	else
	{
		switch(ret)
		{
			case BCM2835_I2C_REASON_ERROR_NACK:
				printf("NO DEVICE ACK!\n");
				status = -1;
				break;
			case BCM2835_I2C_REASON_ERROR_DATA:
				printf("DATA ERROR\n");
				status = -1;
				break;
			defuallt:
				printf("Unknow error!\n");
				status = -1;
				break;
		}
	}
	return status;
}

int main(int argc, char **argv)  
{
	unsigned char rbuf = 0,slave_address = 0xba;
	int ret = 0;
	int delay_time = 1;	//操作延迟时间 单位毫秒

	slave_address = (unsigned char)atoi(argv[1]);
	if (!bcm2835_init())
		return 1;
	
	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(slave_address >> 1); //设置从机地址要右移一位 如从机地址是0xA0 时要设置为0x50 或者设置为 0xa0>>1
	bcm2835_i2c_set_baudrate(10000);	//速率设定  

	start:  
	{  
		WriteBuf[0] = 0x00;	//index 写入索引地址
		WriteBuf[1] = 0xE3;	//data	数据
		ret = bcm2835_i2c_write( WriteBuf , 2);
		if(check_status(ret)<0)
		{
			puts("Write index NACK");
			return -1;
			}
		bcm2835_delay(delay_time);  

		WriteBuf[0] = 0x00;	//index	读取索引地址
		ret = bcm2835_i2c_write( &WriteBuf[0] , 1);
		if(check_status(ret)<0)
		{
			puts("Read index NACK");
			return -1;
			}
		bcm2835_delay(delay_time);
/*
		WriteBuf[0] = 0x00;  
		bcm2835_i2c_write( WriteBuf , 1);  
		bcm2835_delay(500);  
*/		
		bcm2835_i2c_read(&rbuf,1);

		printf("Read data = 0x%X\n",rbuf);
    }  

	bcm2835_i2c_end();  
	bcm2835_close();  

	return 0;  
}  

