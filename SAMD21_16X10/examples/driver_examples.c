/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using USART to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_USART[12] = "Hello World!";

static void tx_cb_USART(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void USART_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&USART, USART_ASYNC_TXC_CB, tx_cb_USART);
	/*usart_async_register_callback(&USART, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&USART, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&USART, &io);
	usart_async_enable(&USART);

	io_write(io, example_USART, 12);
}

static struct timer_task Timer_task1, Timer_task2;
/**
 * Example of using Timer.
 */
static void Timer_task1_cb(const struct timer_task *const timer_task)
{
}

static void Timer_task2_cb(const struct timer_task *const timer_task)
{
}

void Timer_example(void)
{
	Timer_task1.interval = 100;
	Timer_task1.cb       = Timer_task1_cb;
	Timer_task1.mode     = TIMER_TASK_REPEAT;
	Timer_task2.interval = 200;
	Timer_task2.cb       = Timer_task2_cb;
	Timer_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&Timer, &Timer_task1);
	timer_add_task(&Timer, &Timer_task2);
	timer_start(&Timer);
}
