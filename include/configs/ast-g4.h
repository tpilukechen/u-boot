/*
 * Copyright (C) 2012-2020  ASPEED Technology Inc.
 * Ryan Chen <ryan_chen@aspeedtech.com>
 *
 * Copyright 2016 IBM Corporation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_ARCH_ASPEED
#define CONFIG_ARCH_AST2400
#define CONFIG_EXTRA_ENV_SETTINGS AST2400_ENV_SETTINGS


#define CONFIG_ARCH_CPU_INIT
#define CONFIG_MISC_INIT_R
#define CONFIG_MACH_TYPE		MACH_TYPE_ASPEED

#include <asm/arch/platform.h>

/* Misc CPU related */
#define CONFIG_CMDLINE_TAG		/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

#define CONFIG_CMDLINE_EDITING		1

/* Enable cache controller */
#define CONFIG_SYS_DCACHE_OFF		1

#define CONFIG_SYS_SDRAM_BASE		AST_DRAM_BASE
#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_INIT_RAM_SIZE	(32*1024)
#define CONFIG_SYS_INIT_RAM_END		(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_RAM_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR 	(CONFIG_SYS_INIT_RAM_END - GENERATED_GBL_DATA_SIZE)

#define CONFIG_NR_DRAM_BANKS		1

#define CONFIG_SYS_TEXT_BASE		0x00000000

#define CONFIG_SYS_MALLOC_LEN   	(0x1000 + 4*1024*1024) /* malloc() len */

#define CONFIG_ASPEED_TIMER_CLK		(1*1000*1000)	/* use external clk (1M) */

/*
 * NS16550 Configuration
 */
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE		(-4)
#define CONFIG_SYS_NS16550_CLK			24000000
#define CONFIG_SYS_NS16550_COM1			AST_UART0_BASE
#define CONFIG_SYS_LOADS_BAUD_CHANGE
#define CONFIG_SERIAL1				1
#define CONFIG_CONS_INDEX			1
#define CONFIG_BAUDRATE				115200

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_SUBNETMASK

/*
 * Environment Config
 */
#define CONFIG_BOOTDELAY		2

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size */
#define CONFIG_SYS_PROMPT		"ast# "

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_SYS_LOAD_ADDR		0x43000000	/* default load address */

#define CONFIG_BOOTARGS			"console=ttyS4,115200n8 root=/dev/ram rw"

#define CONFIG_AST_SPI_NOR    /* AST SPI NOR Flash */
#define CONFIG_FMC_CS			1
#define CONFIG_SYS_MAX_FLASH_BANKS 	(CONFIG_FMC_CS)
#define CONFIG_SYS_MAX_FLASH_SECT	(8192)		/* max number of sectors on one chip */
#define CONFIG_ENV_IS_IN_FLASH		1
#define CONFIG_ENV_ADDR			(AST_FMC_CS0_BASE + 0x60000)

#define CONFIG_ENV_OFFSET		0x60000	/* environment starts here  */
#define CONFIG_ENV_SIZE			0x20000	/* Total Size of Environment Sector */

#define CONFIG_BOOTCOMMAND	"bootm 20080000 20300000"
#define CONFIG_ENV_OVERWRITE

#define AST2400_ENV_SETTINGS \
	"verify=yes\0"	\
	"spi_dma=yes\0" \
	""

/* Ethernet */
#define CONFIG_LIB_RAND
#define CONFIG_ASPEEDNIC

/* -------------------------------------------------------------------------
 * DRAM Config
 *
 * 1. DRAM Size              //
 *    CONFIG_DRAM_512MBIT    // 512M bit
 *    CONFIG_DRAM_1GBIT      // 1G   bit (default)
 *    CONFIG_DRAM_2GBIT      // 2G   bit
 *    CONFIG_DRAM_4GBIT      // 4G   bit 
 * 2. DRAM Speed             //
 *    CONFIG_DRAM_336        // 336MHz (DDR-667)
 *    CONFIG_DRAM_408        // 408MHz (DDR-800) (default)
 * 3. VGA Mode
 *    CONFIG_CRT_DISPLAY     // define to disable VGA function
 * 4. ECC Function enable
 *    CONFIG_DRAM_ECC        // define to enable ECC function
 * 5. UART Debug Message
 *    CONFIG_DRAM_UART_OUT   // enable output message at UART5
 *    CONFIG_DRAM_UART_38400 // set the UART baud rate to 38400, default is 115200
 */

#define CONFIG_CPU_420 1
#define CONFIG_DRAM_528 1

#endif	/* __CONFIG_H */
