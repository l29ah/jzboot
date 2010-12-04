/* This file is based on code by Ingenic Semiconductor Co., Ltd. */

#ifndef __INGENIC__H__
#define __INGENIC__H__

#include <stdint.h>

#define VR_GET_CPU_INFO		0x00
#define VR_SET_DATA_ADDRESS	0x01
#define VR_SET_DATA_LENGTH	0x02
#define VR_FLUSH_CACHES		0x03
#define VR_PROGRAM_START1	0x04
#define VR_PROGRAM_START2	0x05
#define VR_NOR_OPS		0x06
#define VR_NAND_OPS		0x07
#define VR_SDRAM_OPS		0x08
#define VR_CONFIGRATION		0x09
#define VR_GET_NUM		0x0a

typedef struct {
	void (*cmdset_change)(void *arg);
} ingenic_callbacks_t;

void *ingenic_open(void *usb_hndl);
void ingenic_close(void *hndl);
void ingenic_set_callbacks(void *hndl, const ingenic_callbacks_t *callbacks, void *arg);

int ingenic_redetect(void *hndl);
int ingenic_cmdset(void *hndl);
int ingenic_type(void *hndl);

int ingenic_rebuild(void *hndl);
int ingenic_loadstage(void *hndl, int id, const char *filename);

#define CMDSET_SPL	1
#define CMDSET_USBBOOT	2

#define INGENIC_STAGE1	1
#define INGENIC_STAGE2	2

#define STAGE1_BASE	0x2000
#define SDRAM_BASE	0x80000000

typedef struct {
	/* CPU ID */
	uint32_t cpu_id;

	/* PLL args */
	uint8_t ext_clk;
	uint8_t cpu_speed;
	uint8_t phm_div;
	uint8_t use_uart;
	uint32_t baudrate;

	/* SDRAM args */
	uint8_t bus_width;
	uint8_t bank_num;
	uint8_t row_addr;
	uint8_t col_addr;
	uint8_t is_mobile;
	uint8_t is_busshare;

	/* debug args */
	uint8_t debug_ops;
	uint8_t pin_num;
	uint32_t start;
	uint32_t size;
} __attribute__((packed)) firmware_config_t;

#endif