thanks to Batman313v for this contribution :-)

MCU: https://www.gigadevice.com/product/mcu/arm-cortex-m3/gd32f130c8t6


# A Board
## Buzzer
PB8

# B Board
## MOSFETs
#### Driver A (G)
PA10 -> HIN
PB15 -> LIN

#### Driver B (B)
PA9   -> HIN
PB14 -> LIN

#### Driver C (Y)
PA8   -> HIN
PB13 -> LIN


## BLE Speaker
TODO

## HALL
HALL C (Y) -> PB4
HALL B (B) -> PB5
HALL A (G) -> PB0

## UNPOP 1 (LED 0)
**PINS**
`  0  |  1   |   2  |  3 `
`NULL | NULL | NULL | V+`

**MCU**
0 -> PC13
1 -> PC14
2 -> PC15

## UNPOP 2
LED 0 PINS rotated 90° CC

## LED 1
**PINS**
`  0  |     1     |   2  |  3 `
`NULL | GREEN LED | NULL | V+`

**MCU**
0 -> PF0 (RED)
1 -> PF1 (GREEN)
2 -> PB2 (BLUE)

## TO MASTER
` 0  | 1 | 2 | 3 `
0 -> V+
1 -> PA2
2 -> PA3
3 -> GND

## UNPOP 3
` 0 | 1 `
0 -> V+
1 -> PA7
