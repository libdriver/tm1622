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
 * @file      main.c
 * @brief     main source file
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

#include "driver_tm1622_write_test.h"
#include "driver_tm1622_output_test.h"
#include "driver_tm1622_basic.h"
#include "driver_tm1622_output.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>
#include <math.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];             /**< uart buffer */
volatile uint16_t g_len;        /**< uart buffer length */

/**
 * @brief     tm1622 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t tm1622(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    char short_options[] = "hipe:t:";
    struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"div", required_argument, NULL, 2},
        {"freq", required_argument, NULL, 3},
        {"operator", required_argument, NULL, 4},
        {"num", required_argument, NULL, 5},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    tm1622_freq_t div = TM1622_FREQ_F1;
    tm1622_tone_freq_t freq = TM1622_TONE_FREQ_2K;
    tm1622_bool_t enable = TM1622_BOOL_TRUE;
    uint8_t addr = 0;
    uint8_t num = 0;

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }

    /* init 0 */
    optind = 0;

    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);

        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");

                break;
            }

            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");

                break;
            }

            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");

                break;
            }

            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);

                break;
            }

            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);

                break;
            }

            /* addr */
            case 1 :
            {
                /* set the address */
                addr = (uint8_t)atol(optarg);
                if (addr > 31)
                {
                    return 1;
                }

                break;
            }

            /* div */
            case 2 :
            {
                if (strcmp("1", optarg) == 0)
                {
                    div = TM1622_FREQ_F1;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    div = TM1622_FREQ_F2;
                }
                else if (strcmp("4", optarg) == 0)
                {
                    div = TM1622_FREQ_F4;
                }
                else if (strcmp("8", optarg) == 0)
                {
                    div = TM1622_FREQ_F8;
                }
                else if (strcmp("16", optarg) == 0)
                {
                    div = TM1622_FREQ_F16;
                }
                else if (strcmp("32", optarg) == 0)
                {
                    div = TM1622_FREQ_F32;
                }
                else if (strcmp("64", optarg) == 0)
                {
                    div = TM1622_FREQ_F64;
                }
                else if (strcmp("128", optarg) == 0)
                {
                    div = TM1622_FREQ_F128;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* freq */
            case 3 :
            {
                if (strcmp("2k", optarg) == 0)
                {
                    freq = TM1622_TONE_FREQ_2K;
                }
                else if (strcmp("4k", optarg) == 0)
                {
                    freq = TM1622_TONE_FREQ_4K;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* operator */
            case 4 :
            {
                if (strcmp("on", optarg) == 0)
                {
                    enable = TM1622_BOOL_TRUE;
                }
                else if (strcmp("off", optarg) == 0)
                {
                    enable = TM1622_BOOL_FALSE;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* num */
            case 5 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                num = hex_data & 0xFF;
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }

            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_write", type) == 0)
    {
        /* run the write test */
        if (tm1622_write_test() != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_output", type) == 0)
    {
        /* run the output test */
        if (tm1622_output_test() != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_write", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = tm1622_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        tm1622_interface_debug_print("tm1622: write address 0x%02X 0x%02X.\n", addr, num);
        
        /* write data */
        res = tm1622_basic_write(addr, &num, 1);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_tone", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = tm1622_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        if (freq == TM1622_TONE_FREQ_2K)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: enable 2k tone.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: disable 2k tone.\n");
            }
        }
        else
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: enable 4k tone.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: disable 4k tone.\n");
            }
        }
        
        /* set tone freq */
        res = tm1622_basic_set_tone_freq(freq);
        if (res != 0)
        {
            return 1;
        }
        
        if (enable == TM1622_BOOL_TRUE)
        {
            res = tm1622_basic_enable_tone();
            if (res != 0)
            {
                return 1;
            }
        }
        else
        {
            res = tm1622_basic_disable_tone();
            if (res != 0)
            {
                return 1;
            }
        }
        
        return 0;
    }
    else if (strcmp("e_clock", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = tm1622_output_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        if (div == TM1622_FREQ_F1)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 1 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 1 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F2)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 2 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 2 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F4)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 4 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 4 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F8)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 8 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 8 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F16)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 16 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 16 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F32)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 32 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 32 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F64)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 64 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 64 and stop.\n");
            }
        }
        else
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 128 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 128 and stop.\n");
            }
        }
        
        /* set div */
        res = tm1622_output_set_freq(div);
        if (res != 0)
        {
            return 1;
        }
        
        /* set timer */
        res = tm1622_output_set_timer(enable);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_watchdog", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = tm1622_output_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* output */
        if (div == TM1622_FREQ_F1)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 1 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 1 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F2)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 2 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 2 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F4)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 4 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 4 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F8)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 8 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 8 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F16)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 16 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 16 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F32)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 32 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 32 and stop.\n");
            }
        }
        else if (div == TM1622_FREQ_F64)
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 64 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 64 and stop.\n");
            }
        }
        else
        {
            if (enable == TM1622_BOOL_TRUE)
            {
                tm1622_interface_debug_print("tm1622: div 128 and start.\n");
            }
            else
            {
                tm1622_interface_debug_print("tm1622: div 128 and stop.\n");
            }
        }
        
        /* set div */
        res = tm1622_output_set_freq(div);
        if (res != 0)
        {
            return 1;
        }
        
        /* set watchdog */
        res = tm1622_output_set_watchdog(enable);
        if (res != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        tm1622_interface_debug_print("Usage:\n");
        tm1622_interface_debug_print("  tm1622 (-i | --information)\n");
        tm1622_interface_debug_print("  tm1622 (-h | --help)\n");
        tm1622_interface_debug_print("  tm1622 (-p | --port)\n");
        tm1622_interface_debug_print("  tm1622 (-t write | --test=write)\n");
        tm1622_interface_debug_print("  tm1622 (-t output | --test=output)\n");
        tm1622_interface_debug_print("  tm1622 (-e write | --example=write) [--addr=<address>]\n");
        tm1622_interface_debug_print("         [--num=<hex>]\n");
        tm1622_interface_debug_print("  tm1622 (-e tone | --example=tone)\n");
        tm1622_interface_debug_print("         [--freq=<2k | 4k>] [--operator=<on | off>]\n");
        tm1622_interface_debug_print("  tm1622 (-e clock | --example=clock)\n");
        tm1622_interface_debug_print("         [--div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>] [--operator=<on | off>]\n");
        tm1622_interface_debug_print("  tm1622 (-e watchdog | --example=watchdog)\n");
        tm1622_interface_debug_print("         [--div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>] [--operator=<on | off>]\n");
        tm1622_interface_debug_print("\n");
        tm1622_interface_debug_print("Options:\n");
        tm1622_interface_debug_print("      --addr=<address>                   Set the start address and the range is 0-31.([default: 0])\n");
        tm1622_interface_debug_print("      --div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>\n");
        tm1622_interface_debug_print("                                         Set the clock division.([default: 1])\n");
        tm1622_interface_debug_print("  -e <write | tone | clock | watchdog>, --example=<write | tone | clock | watchdog>\n");
        tm1622_interface_debug_print("                                         Run the driver example.\n");
        tm1622_interface_debug_print("      --freq=<2k | 4k>                   Set the tone frequency.([default: 2k])\n");
        tm1622_interface_debug_print("  -h, --help                             Show the help.\n");
        tm1622_interface_debug_print("  -i, --information                      Show the chip information.\n");
        tm1622_interface_debug_print("      --operator=<on | off>              Enable or disable the operator.([default: on])\n");
        tm1622_interface_debug_print("  -p, --port                             Display the pin connections of the current board.\n");
        tm1622_interface_debug_print("      --num=<hex>                        Set display number.([default: 0x00])\n");
        tm1622_interface_debug_print("  -t <write | output>, --test=<write | output>\n");
        tm1622_interface_debug_print("                                         Run the driver test.\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        tm1622_info_t info;

        /* print tm1622 info */
        tm1622_info(&info);
        tm1622_interface_debug_print("tm1622: chip is %s.\n", info.chip_name);
        tm1622_interface_debug_print("tm1622: manufacturer is %s.\n", info.manufacturer_name);
        tm1622_interface_debug_print("tm1622: interface is %s.\n", info.interface);
        tm1622_interface_debug_print("tm1622: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tm1622_interface_debug_print("tm1622: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tm1622_interface_debug_print("tm1622: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tm1622_interface_debug_print("tm1622: max current is %0.2fmA.\n", info.max_current_ma);
        tm1622_interface_debug_print("tm1622: max temperature is %0.1fC.\n", info.temperature_max);
        tm1622_interface_debug_print("tm1622: min temperature is %0.1fC.\n", info.temperature_min);

        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        tm1622_interface_debug_print("tm1622: GPIO interface DATA connected to GPIOA PIN8.\n");
        tm1622_interface_debug_print("tm1622: GPIO interface WR connected to GPIOA PIN0.\n");
        tm1622_interface_debug_print("tm1622: GPIO interface RD connected to GPIOB PIN1.\n");
        tm1622_interface_debug_print("tm1622: GPIO interface CS connected to GPIOB PIN2.\n");

        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;

    /* stm32f407 clock init and hal init */
    clock_init();

    /* delay init */
    delay_init();

    /* uart init */
    uart_init(115200);

    /* shell init && register tm1622 function */
    shell_init();
    shell_register("tm1622", tm1622);
    uart_print("tm1622: welcome to libdriver tm1622.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("tm1622: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("tm1622: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("tm1622: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("tm1622: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("tm1622: param is invalid.\n");
            }
            else
            {
                uart_print("tm1622: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
