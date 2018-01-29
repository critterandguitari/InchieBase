/*
 * InchiePot.cpp
 *
 *  Created on: Oct 3, 2015
 *      Author: owen
 */


#include "InchiePot.h"

extern "C" {
#include "BlinkLed.h"
}

InchiePot::InchiePot(SLIPEncodedSerial &serial)
: slipSerial(serial)
{
	index = 254;
	pollCount = 0;
	potVal = 0;
	changed = false;
}

void InchiePot::init (void){
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	/* ADC1 DeInit */
	ADC_DeInit(ADC1);

	/* GPIOC Periph clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	/* ADC1 Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	/* Configure as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Initialize ADC structure */
	ADC_StructInit(&ADC_InitStructure);

	/* Configure the ADC1 in continuous mode withe a resolution equal to 12 bits  */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_10b;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv = 0;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
	ADC_Init(ADC1, &ADC_InitStructure);

	/* Convert the ADC1 Channel11 and channel10 with 55.5 Cycles as sampling time */
	ADC_ChannelConfig(ADC1, ADC_Channel_0, ADC_SampleTime_55_5Cycles);

	/* ADC Calibration */
	ADC_GetCalibrationFactor(ADC1);

	/* Enable the ADC peripheral */
	ADC_Cmd(ADC1, ENABLE);

	/* Wait the ADRDY flag */
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY))
		;

	/* ADC1 regular Software Start Conv */
	ADC_StartOfConversion(ADC1);

}

void InchiePot::respond (const uint8_t *buf){

}

void InchiePot::perform (void){

	uint8_t buf[3];

	buf[0] = 0;  // address of brain
	buf[1] = index;

	pollCount++;
	if (pollCount >= 10){
		pollCount = 0;
		/* Test EOC flag */
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

		/* Get ADC1 converted data */
		int16_t v = ADC_GetConversionValue(ADC1);
		//make it 8 bit
		v >>= 2;

		// smooth it out
		if(v==0 || v==255) {
			// allow extremes
			changed |= v != potVal;
			potVal = v;
		} else {
			// 75% new value, 25% old value
			int16_t nv = (v >> 1) + (v >> 2) + (potVal >> 2);
			int diff = nv - potVal;
			if(diff>1 || diff <-1) {
				changed = true;
				potVal = nv;
			}
		}

		if (changed){
			changed = false;
	        buf[2] = potVal;
	        slipSerial.sendPacket(buf, 3);
		}
	}
}



