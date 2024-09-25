# find your board with the 'interactive search' on the [Wiki](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/wiki) here :-)

# study the [Wiki](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/wiki) before opening a new issue !
***

### code moved to [Hoverboard-Firmware-Hack-Gen2.x-GD32](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x-GD32) !!
### MM32 port go here [Hoverboard-Firmware-Hack-Gen2.x-MM32](https://gitlab.com/ailife8881/Hoverboard-Firmware-Hack-Gen2.x-MM32)) (uartBus protocol, pinFinder)
#### MM32 EFeru FOC port go here [MM32SPIN05_Hoberboard_hack](https://github.com/trondin/MM32SPIN05_Hoberboard_hack) (no foc,but EFeru uart protocol)
both MM32 firmwares run on this $4.4 (+$5 shipping) pair of Gen2.4.2 boards: https://www.aliexpress.com/item/1005005959910034.html (tell me if you find a likewise offer that ships to Germany/EU)
***

### 2024/02/18: board numbering changed from Gen2.x to Gen2.t.v
Gen2.1.4xf = split board . target 1 . version 4 x=64kb, f=FOC capable.

The s(32kB)/x(64kB) flag and the f flag are for information only.

Targets are the Keil targets:
- 1 gd32f130 
- 2 gd/stm32f103 
- 3 gd32e230 
- 4 mm32spin0x 
- 5 lks32

![grafik](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/assets/12238841/63038831-7bfc-46c6-b59f-c2ccb016b637)

## 2024/1/10 the following layouts are ready to use (99%):

- Gen2.1.1 (ex2.0)
- Gen2.1.3 (ex2.2) https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/5
- Gen2.1.4 (ex2.3) https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/20
- Gen2.1.7.1 (ex2.6.1) https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/49
- Gen2.1.8 (ex2.10) https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/25
- Gen2.1.11 (ex2.13) https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/33
- Gen2.1.16 (ex2.18) https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/40

layouts worth testing (with a 2A cc constant current power supply / dcdc-step-down converter | 1.5 42V charger):

- Gen2.1.2 (ex2.1) this repo here was a fork from a running 2.1 firmware
- Gen2.1.5 (ex2.4) https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/3
- Gen2.3.1 (ex2.7) https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/16
- Gen2.1.9 (ex2.11) https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/27
- Gen2.1.13 (ex2.15) https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/38
- Gen2.1.18 (ex2.20) https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/58
  
### Update 2.x:
- This is a fork from https://github.com/krisstakos/Hoverboard-Firmware-Hack-Gen2.1
- with different defines_2-x.h for two different board layouts :-) 
- Simply set `#define LAYOUT x` to your 2.x board in `Inc/config.h` :-))
- You can download compiled binaries [here](BinariesReadyToFlash/) (the Dummy-firmwares will ignore uart speed and will repeat speed from -300 to 300 instead)
- Binaries probably not yet working: [BinariesToTest/](BinariesToTest/)
- Make sure your board is one of the supported layouts ! **Wrong pin assignments can shortcut the battery and kill the mosfets !!**


#### Update 2.1:
- That's a fork from https://github.com/flo199213/Hoverboard-Firmware-Hack-Gen2
- Compiles with Keil version 6 :-))
