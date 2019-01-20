<p align="center">
  <a href="http://turtlerover.com" alt="Turtle Rover"><img src="https://avatars3.githubusercontent.com/u/36553642?s=84&v=4" alt="Turtle Rover" /></a>
</p>
<h1 align="center">Firmware: Shield</h1>
<h4 align="center">This is software for microprocessor on <a href="https://github.com/TurtleRover/electronics-shield">electronics-shield</a></h4>

<p align="center">
  <a href="https://travis-ci.org/TurtleRover/firmware-shield">
    <img src="https://travis-ci.org/TurtleRover/firmware-shield.svg?branch=master" alt="Build Status">
  </a>
  <a href="https://github.com/TurtleRover/firmware-shield/releases">
    <img src="https://img.shields.io/github/release/TurtleRover/firmware-shield.svg" alt="Release"></a>
  <a href="https://github.com/TurtleRover/firmware-shield/blob/master/LICENSE">
      <img src="https://img.shields.io/github/license/TurtleRover/firmware-shield.svg">
  </a>
  <a href="https://twitter.com/TurtleRover">
    <img src="https://img.shields.io/twitter/follow/TurtleRover.svg?style=social&label=Follow">
  </a>
</p>
<p align="center">
  <a href="http://turtlerover.com" alt="Website">Website</a> |
  <a href="https://www.facebook.com/TurtleRover/" alt="Facebook">Facebook</a> |
  <a href="https://www.youtube.com/channel/UCxukvEct3wP0S5FACa3uelA" alt="YouTube">YouTube</a>
</p>

## Data frames in HEX

| Prefix | Body | Postfix | Description |
| --- | --- | --- | --- |
| `00` | `00` `00` `00` `00` | `0d0a` | Returns name of the robot |
| `01` | `00` `00` `00` `00` | `0d0a` | Returns version of firmware |
| `10` | ⬆️`00` `00` `00` `00` : `7f` `7f` `7f` `7f`<br>⬇️`80` `80` `80` `80` : `ff` `ff` `ff` `ff`| `0d0a` | Motors speed set simultaneously for all wheels. The first range is for moving forward, the second - backward, accordingly. |
| `30` | `00` `00` `00` `00` | `0d0a` | Returns battery voltage in float with 2 decimal points |
| `41` | `slave_addres << 1` `data_1` `data_2` `data_3` | `0d0a` | Send data to I2C connector. |
| `42` | `slave_addres << 1` `size_of_data` `00` `00` | `0d0a` | Recieve data from I2C connector. |
| `43` | `slave_addres << 1` `memory_addres` `size_of_memory` `data` | `0d0a` | Write to register. |
| `44` | `slave_addres << 1` `memory_addres` `size_of_memory` `00` | `0d0a` | Read from register. |
| `81` | `(duty >> 8) & 0xff` `duty & 0xff` `00` `00` | `0d0a` | Set servo 1 duty |
| `82` | `(duty >> 8) & 0xff` `duty & 0xff` `00` `00` | `0d0a` | Set servo 2 duty |
| `83` | `(duty >> 8) & 0xff` `duty & 0xff` `00` `00` | `0d0a` | Set servo 3 duty (redundant with 94)|
| `84` | `(axis_1 >> 8) & 0xff` `axis_1 & 0xff` `(axis_2 >> 8) & 0xFF` `axis_2 & 0xff` | `0d0a` | Set manipulator orientation (only axis without gripper)	- 2 bytes MSB first. |
| `94` | `(gripperPosition >> 8) & 0xFF` `gripperPosition & 0xFF ` | `0d0a` | Set gripper value.|
| `FF` | `01 or 00` `00` `00` `00` | `0d0a` | Enable / disable watchdog. 0x01 is default setting |

Notice: All messages from microcontroller ends with \r\n character

## Example frame
|:-------:|:-----------:|:-----------:|:-----------:|:-----------:|:-------:|:-------:|
|   0x10  |     0x50    |     0x50    |     0x50    |     0x50    |   0x0d  |   0x0a  |
| Prefix  | Motor speed | Motor speed | Motor speed | Motor speed | Postfix | Postfix |


## Install toolchain

Below steps for Unix systems:

```
sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
sudo apt-get update 
sudo apt-get install gcc-arm-embedded
```
## Code editing 

Install System Workbench for STM32.

Import project to workspace.

Check your linker flags (project properties > C/C++ Build > Setings > Tool Settings (TAB) > MCU GCC Linker > Miscellaneous > Linker flags), 
if you are using nanolib “-specs=nano.specs” you need to add “-u _printf_float” to enable float printf.

