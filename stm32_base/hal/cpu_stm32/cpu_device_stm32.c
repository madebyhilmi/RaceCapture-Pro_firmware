#include "cpu_device.h"
#include <stm32f4xx_misc.h>
#include <stdint.h>

extern uint32_t _flash_start;
static char cpu_id[25];

#define CPU_ID_REGISTER_START 0x1FFF7A10
#define CPU_ID_REGISTER_END   0x1FFF7A1C
#define ASCII(x) (((x)&0xF) < 10) ? (((x)&0xF)+'0') : (((x)&0xF)-10+'A')

static void init_cpu_id(){
    uint32_t *p = (uint32_t *) CPU_ID_REGISTER_START;
    int i = 0, j = 0;
    while (p <= (uint32_t *) CPU_ID_REGISTER_END) {
        for (i = 0; i < 8; i++)
            cpu_id[7-i+j] = ASCII(*p >> (i*4));
        p++;
        j += 8;
    }
    cpu_id[24] = 0;
}

int cpu_device_init(void){
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, _flash_start);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	init_cpu_id();
	return 1;
}

void cpu_device_reset(){

}

const char * cpu_device_get_serialnumber(void){
	return cpu_id;
}
