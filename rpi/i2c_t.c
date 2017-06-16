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
	int delay_time = 1;	//�����ӳ�ʱ�� ��λ����

	slave_address = (unsigned char)atoi(argv[1]);
	if (!bcm2835_init())
		return 1;
	
	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(slave_address >> 1); //���ôӻ���ַҪ����һλ ��ӻ���ַ��0xA0 ʱҪ����Ϊ0x50 ��������Ϊ 0xa0>>1
	bcm2835_i2c_set_baudrate(10000);	//�����趨  

	start:  
	{  
		WriteBuf[0] = 0x00;	//index д��������ַ
		WriteBuf[1] = 0xE3;	//data	����
		ret = bcm2835_i2c_write( WriteBuf , 2);
		if(check_status(ret)<0)
		{
			puts("Write index NACK");
			return -1;
			}
		bcm2835_delay(delay_time);  

		WriteBuf[0] = 0x00;	//index	��ȡ������ַ
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

