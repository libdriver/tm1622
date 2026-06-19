### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

GPIO Pin: DATA/WR/RD/CS GPIO17/GPIO27/GPIO5/GPIO22.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(tm1622 REQUIRED)
```

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
./tm1622 -i

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
./tm1622 -p

tm1622: GPIO interface DATA connected to GPIO17(BCM).
tm1622: GPIO interface WR connected to GPIO27(BCM).
tm1622: GPIO interface RD connected to GPIO5(BCM).
tm1622: GPIO interface CS connected to GPIO22(BCM).
```

```shell
./tm1622 -t write

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
./tm1622 -t output

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
./tm1622 -e write --addr=0 --num=0x0F

tm1622: write address 0x00 0x0F.
```
```shell
./tm1622 -e tone --freq=2k --operator=on

tm1622: enable 2k tone.
```
```
./tm1622 -e clock --div=128 --operator=on

tm1622: div 128 and start.
```
```shell
./tm1622 -e watchdog --div=1 --operator=on

tm1622: div 1 and start.
```
```shell
./tm1622 -h

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
