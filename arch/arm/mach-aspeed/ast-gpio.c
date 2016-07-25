/*
 *
 */

#include <common.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <asm/arch/ast_scu.h>
#include <asm/arch/platform.h>
#include <asm/arch/aspeed.h>


/* AST2400 */
#define MAX_GPIO					304
#define SGPIO_START_PIN				224
#define BANK_EXTGPIO_DATA_OFFSET	3	// E,F,G,H   bank(04~07)
#define BANK_SIMPLE_GPIO4_OFFSET	23  // Y,Z,AA,AB

// Standard (A,B,C,D)
#define GPIO_DATA_OFFSET		0x00
#define GPIO_PIN_DIR_OFFSET		0x04
#define GPIO_INT_EN_OFFSET		0x08
#define GPIO_INT_SEN_TYPE0_OFFSET	0x0C
#define GPIO_INT_SEN_TYPE1_OFFSET	0x10
#define GPIO_INT_SEN_TYPE2_OFFSET	0x14
#define GPIO_INT_STATUS_OFFSET		0x18
#define GPIO_RESET_TOLERANT_OFFSET	0x1C
// Extended (E,F,G,H)
#define EXTGPIO_DATA_OFFSET		0x20
#define EXTGPIO_PIN_DIR_OFFSET		0x24
#define EXTGPIO_INT_EN_OFFSET		0x28
#define EXTGPIO_INT_SEN_TYPE0_OFFSET	0x2C
#define EXTGPIO_INT_SEN_TYPE1_OFFSET	0x30
#define EXTGPIO_INT_SEN_TYPE2_OFFSET	0x34
#define EXTGPIO_INT_STATUS_OFFSET	0x38
#define EXTGPIO_RESET_TOLERANT_OFFSET	0x3C
// Simple GPIO 4 (Y,Z,AB,AA)
#define SIMPLE_GPIO4_DATA_OFFSET 	0x01E0
#define SIMPLE_GPIO4_DIR_OFFSET  	0x01E4
#define SIMPLE_GPIO4_INT_EN_OFFSET	0x0178
// Configuration
#define GPIO_DEBOUNCE_SET1		0x40
#define GPIO_DEBOUNCE_SET2		0x44
#define EXTGPIO_DEBOUNCE_SET1		0x48
#define EXTGPIO_DEBOUNCE_SET2		0x4C
#define GPIO_DEBOUNCE_TIME1		0x50
#define GPIO_DEBOUNCE_TIME2		0x54
#define GPIO_DEBOUNCE_TIME3		0x58
#define GPIO_CMD_SOURCE0		0x60
#define GPIO_CMD_SOURCE1		0x64
#define EXTGPIO_CMD_SOURCE0		0x68
#define EXTGPIO_CMD_SOURCE1		0x6C


#define MAX_GPIO_IDX			(MAX_GPIO - 1)

#define GPIO_DIR_OUT			0x01
#define GPIO_DIR_IN			0x00


void ast_gpio_set_dir(int gpio, int dir)
{
	int bank,tpin;
	volatile uint32_t Addr;
	volatile uint32_t Value;
	
	if ( gpio > MAX_GPIO_IDX )
	{
		printf ("[error] ast_gpio_dir :%d\n", gpio);	
		return;
	}
	
	/* this driver don't support sgpio */
	if ( gpio >= SGPIO_START_PIN )
	{
		printf ("[error] ast_gpio_dir :%d\n", gpio);	
		return;
	}
	
	/* Get the register Addr  */
	bank = (gpio / 8);
	tpin = (gpio % 32);	

	if(bank >= BANK_EXTGPIO_DATA_OFFSET)
		Addr = (uint32_t) AST_GPIO_BASE + EXTGPIO_PIN_DIR_OFFSET;
	else if (bank >=BANK_SIMPLE_GPIO4_OFFSET)
		Addr = (uint32_t) AST_GPIO_BASE + SIMPLE_GPIO4_DATA_OFFSET;
	else
		Addr = (uint32_t) AST_GPIO_BASE + GPIO_PIN_DIR_OFFSET;

	Value = readl(Addr);

	if ( dir )
		Value = Value | ( 0x01 << tpin );
	else
		Value = Value & ~ ( 0x01 << tpin );

	writel(Value, Addr);	
}


void ast_gpio_set_val(int gpio, int val)
{
	int bank,tpin;
	volatile uint32_t Addr;
	volatile uint32_t Value;
	
	if ( gpio > MAX_GPIO_IDX )
	{
		printf ("[error] ast_gpio_set :%d\n", gpio);	
		return;
	}
	
	/* this driver don't support sgpio */
	if ( gpio >= SGPIO_START_PIN )
	{
		printf ("[error] ast_gpio_set :%d\n", gpio);
		return;
	}

	/* Get the register Addr  */
	bank = (gpio / 8);
	tpin = (gpio % 32);	

	if(bank >= BANK_EXTGPIO_DATA_OFFSET)
		Addr = (uint32_t) AST_GPIO_BASE + EXTGPIO_DATA_OFFSET;
	else if (bank >=BANK_SIMPLE_GPIO4_OFFSET)
		Addr = (uint32_t) AST_GPIO_BASE + SIMPLE_GPIO4_DATA_OFFSET;
	else
		Addr = (uint32_t) AST_GPIO_BASE + GPIO_DATA_OFFSET;

	Value = readl(Addr);

	if ( val )
		Value = Value | ( 0x01 << tpin );
	else
		Value = Value & ~ ( 0x01 << tpin );

	writel(Value, Addr);
}

int ast_gpio_get_val(int gpio)
{
	int bank,tpin;
	volatile uint32_t Addr;
	volatile uint32_t Value;
	
	if ( gpio > MAX_GPIO_IDX ) return -1;
	
	/* this driver don't support sgpio */
	if ( gpio >= SGPIO_START_PIN ) return -1;

	/* Get the register Addr  */
	bank = (gpio / 8);
	tpin = (gpio % 32);	
	
	if(bank >= BANK_EXTGPIO_DATA_OFFSET)
		Addr = (uint32_t) AST_GPIO_BASE + EXTGPIO_DATA_OFFSET;
	else if (bank >=BANK_SIMPLE_GPIO4_OFFSET)
		Addr = (uint32_t) AST_GPIO_BASE + SIMPLE_GPIO4_DATA_OFFSET;
	else
		Addr = (uint32_t) AST_GPIO_BASE + GPIO_DATA_OFFSET;
	
	/* Get the particular bit */
	Value = readl(Addr);
	Value &=  ( 0x01 << tpin );
	Value >>= tpin ;

	//printf ("ast_gpio_get(%d.%08Xh) :%d\n",bank,( 0x01 << tpin ), Value);	

	return Value;
}

void ast_scu_gpio_init()
{
#ifdef AST_SOC_G4  /* AST2400 */
	//Set BMC LIVE LED GPIOY0 192 to out
	ast_gpio_set_dir(192, 1);
	
#endif
}
