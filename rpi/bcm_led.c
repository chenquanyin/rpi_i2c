#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>

#define PIN RPI_GPIO_P1_11

int main()
{
    if(!bcm2835_init())
    {
        printf("bcm2835 初始化失败\n\r");
        return 1;
    }
    //配置输出模式
    bcm2835_gpio_fsel(PIN,BCM2835_GPIO_FSEL_OUTP);
    while(1)
    {
        bcm2835_gpio_write(PIN,HIGH);
        bcm2835_delay(100);
        bcm2835_gpio_write(PIN,LOW);
        bcm2835_delay(100);
    }
    bcm2835_close();
    return 0;
}

