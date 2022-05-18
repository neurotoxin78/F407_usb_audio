/*
 * audioplay.c
 *
 *  Created on: Feb 5, 2021
 *      Author: HOME
 */

#include "audioplay.h"
#include "usbd_audio_if.h"

extern DMA_HandleTypeDef hdma_spi2_tx;
extern I2S_HandleTypeDef hi2s2;

#define DMA_MAX_SZE                     0xFFFF
#define DMA_MAX(_X_)                (((_X_) <= DMA_MAX_SZE)? (_X_):DMA_MAX_SZE)
#define AUDIODATA_SIZE                  2   /* 16-bits audio data size */

void Audio_Player_Play(uint8_t* pBuffer, uint32_t Size)
{
	if(Size > 0xFFFF) {
		Size = 0xFFFF;
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	}
	HAL_I2S_Transmit_DMA(&hi2s2, (uint16_t*)pBuffer, Size);
//	HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t*)pBuffer, DMA_MAX(Size/AUDIODATA_SIZE));
}

void Audio_Player_Pause(void)
{
	HAL_I2S_DMAPause(&hi2s2);
}

void Audio_Player_Resume(void)
{
	HAL_I2S_DMAResume(&hi2s2);
}

void Audio_Player_Stop(void)
{
	HAL_I2S_DMAStop(&hi2s2);
}

void Audio_Player_VolumeCtl(uint8_t vol)
{
//	WM8978_VolumeCtl(vol);
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	HalfTransfer_CallBack_FS();
}


void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	TransferComplete_CallBack_FS();
}


