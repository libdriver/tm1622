/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_tm1622_output_test.c
 * @brief     driver tm1622 output test source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2026-05-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2026/05/31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */
 
#include "driver_tm1622_output_test.h"

/**
 * @brief tm1622 var definition
 */
static tm1622_handle_t gs_handle;        /**< tm1622 handle */

/**
 * @brief  output test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t tm1622_output_test(void)
{
    uint8_t res;
    tm1622_info_t info;

    /* link interface function */
    DRIVER_TM1622_LINK_INIT(&gs_handle, tm1622_handle_t); 
    DRIVER_TM1622_LINK_DATA_GPIO_INIT(&gs_handle, tm1622_interface_data_gpio_init);
    DRIVER_TM1622_LINK_DATA_GPIO_DEINIT(&gs_handle, tm1622_interface_data_gpio_deinit);
    DRIVER_TM1622_LINK_DATA_GPIO_WRITE(&gs_handle, tm1622_interface_data_gpio_write);
    DRIVER_TM1622_LINK_DATA_GPIO_READ(&gs_handle, tm1622_interface_data_gpio_read);
    DRIVER_TM1622_LINK_WR_GPIO_INIT(&gs_handle, tm1622_interface_wr_gpio_init);
    DRIVER_TM1622_LINK_WR_GPIO_DEINIT(&gs_handle, tm1622_interface_wr_gpio_deinit);
    DRIVER_TM1622_LINK_WR_GPIO_WRITE(&gs_handle, tm1622_interface_wr_gpio_write);
    DRIVER_TM1622_LINK_RD_GPIO_INIT(&gs_handle, tm1622_interface_rd_gpio_init);
    DRIVER_TM1622_LINK_RD_GPIO_DEINIT(&gs_handle, tm1622_interface_rd_gpio_deinit);
    DRIVER_TM1622_LINK_RD_GPIO_WRITE(&gs_handle, tm1622_interface_rd_gpio_write);
    DRIVER_TM1622_LINK_CS_GPIO_INIT(&gs_handle, tm1622_interface_cs_gpio_init);
    DRIVER_TM1622_LINK_CS_GPIO_DEINIT(&gs_handle, tm1622_interface_cs_gpio_deinit);
    DRIVER_TM1622_LINK_CS_GPIO_WRITE(&gs_handle, tm1622_interface_cs_gpio_write);
    DRIVER_TM1622_LINK_DELAY_US(&gs_handle, tm1622_interface_delay_us);
    DRIVER_TM1622_LINK_DELAY_MS(&gs_handle, tm1622_interface_delay_ms);
    DRIVER_TM1622_LINK_DEBUG_PRINT(&gs_handle, tm1622_interface_debug_print);
    
    /* get information */
    res = tm1622_info(&info);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        tm1622_interface_debug_print("tm1622: chip is %s.\n", info.chip_name);
        tm1622_interface_debug_print("tm1622: manufacturer is %s.\n", info.manufacturer_name);
        tm1622_interface_debug_print("tm1622: interface is %s.\n", info.interface);
        tm1622_interface_debug_print("tm1622: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tm1622_interface_debug_print("tm1622: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tm1622_interface_debug_print("tm1622: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tm1622_interface_debug_print("tm1622: max current is %0.2fmA.\n", info.max_current_ma);
        tm1622_interface_debug_print("tm1622: max temperature is %0.1fC.\n", info.temperature_max);
        tm1622_interface_debug_print("tm1622: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start output test */
    tm1622_interface_debug_print("tm1622: start output test.\n");
    
    /* tm1622 init */
    res = tm1622_init(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: init failed.\n");
        
        return 1;
    }
    
    /* set clock */
    res = tm1622_set_clock(&gs_handle, TM1622_CLOCK_RC_32K);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set clock failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable oscillator */
    res = tm1622_set_oscillator(&gs_handle, TM1622_BOOL_TRUE);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set oscillator failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable lcd bias */
    res = tm1622_set_lcd_bias(&gs_handle, TM1622_BOOL_TRUE);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set lcd bias failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set normal mode */
    res = tm1622_set_mode(&gs_handle, TM1622_MODE_NORMAL);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set mode failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable tone */
    res = tm1622_set_tone(&gs_handle, TM1622_BOOL_FALSE);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set tone failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable timer */
    res = tm1622_set_timer(&gs_handle, TM1622_BOOL_FALSE);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set timer failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear timer */
    res = tm1622_clear_timer(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear timer failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable watchdog */
    res = tm1622_set_watchdog(&gs_handle, TM1622_BOOL_FALSE);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear watchdog */
    res = tm1622_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable interrupt */
    res = tm1622_set_irq(&gs_handle, TM1622_BOOL_TRUE);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set irq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear segment */
    res = tm1622_clear_segment(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear segment failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 1hz, wdt 4s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F1);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable timer */
    res = tm1622_set_timer(&gs_handle, TM1622_BOOL_TRUE);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set timer failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 1hz test */
    tm1622_interface_debug_print("tm1622: clock 1hz test.\n");
    
    /* delay 5000ms */
    tm1622_interface_delay_ms(5000);
    
    /* set freq clock 2hz, wdt 2s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F2);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 2hz test */
    tm1622_interface_debug_print("tm1622: clock 2hz test.\n");
    
    /* delay 5000ms */
    tm1622_interface_delay_ms(5000);
    
    /* set freq clock 4hz, wdt 1s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F4);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 4hz test */
    tm1622_interface_debug_print("tm1622: clock 4hz test.\n");
    
    /* delay 5000ms */
    tm1622_interface_delay_ms(5000);
    
    /* set freq clock 8hz, wdt 1/2s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F8);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 8hz test */
    tm1622_interface_debug_print("tm1622: clock 8hz test.\n");
    
    /* delay 5000ms */
    tm1622_interface_delay_ms(5000);
    
    /* set freq clock 16hz, wdt 1/4s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F16);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 16hz test */
    tm1622_interface_debug_print("tm1622: clock 16hz test.\n");
    
    /* delay 5000ms */
    tm1622_interface_delay_ms(5000);
    
    /* set freq clock 32hz, wdt 1/8s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F32);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 32hz test */
    tm1622_interface_debug_print("tm1622: clock 32hz test.\n");
    
    /* delay 5000ms */
    tm1622_interface_delay_ms(5000);
    
    /* set freq clock 64hz, wdt 1/16s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F64);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 64hz test */
    tm1622_interface_debug_print("tm1622: clock 64hz test.\n");
    
    /* delay 5000ms */
    tm1622_interface_delay_ms(5000);
    
    /* set freq clock 128hz, wdt 1/32s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F128);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clock 128hz test */
    tm1622_interface_debug_print("tm1622: clock 128hz test.\n");
    
    /* delay 5000ms */
    tm1622_interface_delay_ms(5000);
    
    /* disable timer */
    res = tm1622_set_timer(&gs_handle, TM1622_BOOL_FALSE);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set timer failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear timer */
    res = tm1622_clear_timer(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear timer failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable watchdog */
    res = tm1622_set_watchdog(&gs_handle, TM1622_BOOL_TRUE);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear watchdog */
    res = tm1622_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 1hz, wdt 4s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F1);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 4s test */
    tm1622_interface_debug_print("tm1622: wdt 4s test.\n");
    
    /* delay 5000ms */
    tm1622_interface_delay_ms(5000);
    
    /* clear watchdog */
    res = tm1622_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 2hz, wdt 2s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F2);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 2s test */
    tm1622_interface_debug_print("tm1622: wdt 2s test.\n");
    
    /* delay 3000ms */
    tm1622_interface_delay_ms(3000);
    
    /* clear watchdog */
    res = tm1622_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 4hz, wdt 1s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F4);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1s test */
    tm1622_interface_debug_print("tm1622: wdt 1s test.\n");
    
    /* delay 2000ms */
    tm1622_interface_delay_ms(2000);
    
    /* clear watchdog */
    res = tm1622_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 8hz, wdt 1/2s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F8);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1/2s test */
    tm1622_interface_debug_print("tm1622: wdt 1/2s test.\n");
    
    /* delay 1000ms */
    tm1622_interface_delay_ms(1000);
    
    /* clear watchdog */
    res = tm1622_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 16hz, wdt 1/4s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F16);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1/4s test */
    tm1622_interface_debug_print("tm1622: wdt 1/4s test.\n");
    
    /* delay 1000ms */
    tm1622_interface_delay_ms(1000);
    
    /* clear watchdog */
    res = tm1622_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 32hz, wdt 1/8s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F32);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1/8s test */
    tm1622_interface_debug_print("tm1622: wdt 1/8s test.\n");
    
    /* delay 1000ms */
    tm1622_interface_delay_ms(1000);
    
    /* clear watchdog */
    res = tm1622_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 64hz, wdt 1/16s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F64);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1/16s test */
    tm1622_interface_debug_print("tm1622: wdt 1/16s test.\n");
    
    /* delay 1000ms */
    tm1622_interface_delay_ms(1000);
    
    /* clear watchdog */
    res = tm1622_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set freq clock 128hz, wdt 1/32s */
    res = tm1622_set_freq(&gs_handle, TM1622_FREQ_F128);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set freq failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wdt 1/32s test */
    tm1622_interface_debug_print("tm1622: wdt 1/32s test.\n");
    
    /* delay 1000ms */
    tm1622_interface_delay_ms(1000);
    
    /* disable watchdog */
    res = tm1622_set_watchdog(&gs_handle, TM1622_BOOL_FALSE);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: set watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear watchdog */
    res = tm1622_clear_watchdog(&gs_handle);
    if (res != 0)
    {
        tm1622_interface_debug_print("tm1622: clear watchdog failed.\n");
        (void)tm1622_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish output test */
    tm1622_interface_debug_print("tm1622: finish output test.\n");
    (void)tm1622_deinit(&gs_handle);
    
    return 0;
}
