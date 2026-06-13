#include"stm32f407xx.h"

int main(void){
    GPIO_Handle_t GpioBtn, GpioLed;

    GpioBtn.pGPIOx = GPIOA;
    GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GpioLed.pGPIOx = GPIOD;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GpioBtn);
    GPIO_Init(&GpioLed);

    while(1){
        if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) == GPIO_PIN_SET){
            GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_15, GPIO_PIN_SET);
        }else{
            GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_15, GPIO_PIN_RESET);
        }
    }

}