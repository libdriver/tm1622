### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

GPIO Pin: DATA/WR/RD/CS PA8/PA0/PB1/PB2.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. TM1622

#### 3.1 Command Instruction

1. Show tm1622 chip and driver information.

    ```shell
    tm1622 (-i | --information)  
    ```

2. Show tm1622 help.

    ```shell
    tm1622 (-h | --help)        
    ```

3. Show tm1622 pin connections of the current board.

    ```shell
    tm1622 (-p | --port)        
    ```

4. Run tm1622 write test.

    ```shell
    tm1622 (-t write | --test=write)
    ```

5. Run tm1622 output test.

    ```shell
    tm1622 (-t output | --test=output)
    ```
    
6. Run tm1622 write function,  address is the start address and the range is 0 - 31, hex is the set data.

    ```shell
    tm1622 (-e write | --example=write) [--addr=<address>] [--num=<hex>]
    ```
    
7. Run tm1622 tone function.

    ```shell
    tm1622 (-e tone | --example=tone) [--freq=<2k | 4k>] [--operator=<on | off>]
    ```

8. Run tm1622 clock function.

    ```shell
    tm1622 (-e clock | --example=clock) [--div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>] [--operator=<on | off>]
    ```
9. Run tm1622 watchdog function.

    ```shell
    tm1622 (-e watchdog | --example=watchdog) [--div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>] [--operator=<on | off>]
    ```

#### 3.2 Command Example

```shell
tm1622 -i

tm1622: chip is Titan Micro Electronics TM1622.
tm1622: manufacturer is Titan Micro Electronics.
tm1622: interface is GPIO.
tm1622: driver version is 1.0.
tm1622: min supply voltage is 2.7V.
tm1622: max supply voltage is 5.2V.
tm1622: max current is 4.50mA.
tm1622: max temperature is 85.0C.
tm1622: min temperature is -20.0C.
```

```shell
tm1622 -p

tm1622: GPIO interface DATA connected to GPIOA PIN8.
tm1622: GPIO interface WR connected to GPIOA PIN0.
tm1622: GPIO interface RD connected to GPIOB PIN1.
tm1622: GPIO interface CS connected to GPIOB PIN2.
```

```shell
tm1622 -t write

tm1622: chip is Titan Micro Electronics TM1622.
tm1622: manufacturer is Titan Micro Electronics.
tm1622: interface is GPIO.
tm1622: driver version is 1.0.
tm1622: min supply voltage is 2.7V.
tm1622: max supply voltage is 5.2V.
tm1622: max current is 4.50mA.
tm1622: max temperature is 85.0C.
tm1622: min temperature is -20.0C.
tm1622: start write test.
tm1622: write segment test.
tm1622: 2k tone test.
tm1622: 4k tone test.
tm1622: finish write test.
```

```shell
tm1622 -t output

tm1622: chip is Titan Micro Electronics TM1622.
tm1622: manufacturer is Titan Micro Electronics.
tm1622: interface is GPIO.
tm1622: driver version is 1.0.
tm1622: min supply voltage is 2.7V.
tm1622: max supply voltage is 5.2V.
tm1622: max current is 4.50mA.
tm1622: max temperature is 85.0C.
tm1622: min temperature is -20.0C.
tm1622: start output test.
tm1622: clock 1hz test.
tm1622: clock 2hz test.
tm1622: clock 4hz test.
tm1622: clock 8hz test.
tm1622: clock 16hz test.
tm1622: clock 32hz test.
tm1622: clock 64hz test.
tm1622: clock 128hz test.
tm1622: wdt 4s test.
tm1622: wdt 2s test.
tm1622: wdt 1s test.
tm1622: wdt 1/2s test.
tm1622: wdt 1/4s test.
tm1622: wdt 1/8s test.
tm1622: wdt 1/16s test.
tm1622: wdt 1/32s test.
tm1622: finish output test.
```

```shell
tm1622 -e write --addr=0 --num=0x0F

tm1622: write address 0x00 0x0F.
```
```shell
tm1622 -e tone --freq=2k --operator=on

tm1622: enable 2k tone.
```
```
tm1622 -e clock --div=128 --operator=on

tm1622: div 128 and start.
```
```shell
tm1622 -e watchdog --div=1 --operator=on

tm1622: div 1 and start.
```
```shell
tm1622 -h

Usage:
  tm1622 (-i | --information)
  tm1622 (-h | --help)
  tm1622 (-p | --port)
  tm1622 (-t write | --test=write)
  tm1622 (-t output | --test=output)
  tm1622 (-e write | --example=write) [--addr=<address>]
         [--num=<hex>]
  tm1622 (-e tone | --example=tone)
         [--freq=<2k | 4k>] [--operator=<on | off>]
  tm1622 (-e clock | --example=clock)
         [--div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>] [--operator=<on | off>]
  tm1622 (-e watchdog | --example=watchdog)
         [--div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>] [--operator=<on | off>]

Options:
      --addr=<address>                   Set the start address and the range is 0-31.([default: 0])
      --div=<1 | 2 | 4 | 8 | 16 | 32 | 64 | 128>
                                         Set the clock division.([default: 1])
  -e <write | tone | clock | watchdog>, --example=<write | tone | clock | watchdog>
                                         Run the driver example.
      --freq=<2k | 4k>                   Set the tone frequency.([default: 2k])
  -h, --help                             Show the help.
  -i, --information                      Show the chip information.
      --operator=<on | off>              Enable or disable the operator.([default: on])
  -p, --port                             Display the pin connections of the current board.
      --num=<hex>                        Set display number.([default: 0x00])
  -t <write | output>, --test=<write | output>
                                         Run the driver test.
```
