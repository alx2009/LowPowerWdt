# LowPower Library
[![Build Status](https://app.travis-ci.com/LowPowerLab/LowPower.svg)](https://app.travis-ci.com/LowPowerLab/LowPower)
[![GitHub release](https://img.shields.io/github/release/LowPowerLab/LowPower.svg)](https://github.com/LowPowerLab/LowPower)
[![GitHub issues](https://img.shields.io/github/issues/LowPowerLab/LowPower.svg)](https://github.com/LowPowerLab/LowPower/issues)
[![GitHub pull requests](https://img.shields.io/github/issues-pr/LowPowerLab/LowPower.svg)](https://github.com/LowPowerLab/LowPower/pulls)

Lightweight low power library for AVR/SAMD21 Moteino boards. Compared to LowPower it supports using the watchdog timer for both interrupt (while sleeping or power down) and reset (when the CPU is running). The timeout for the two modes can be set independently.
<br/>
By Felix Rusu,
<br/>
Forked from [LowPowerLab.com](http://LowPowerLab.com).

Date: 2022-03-05

Devices Supported:
* ATMega168
* ATMega328P (tested) 
* ATMega32U4
* ATMega644P
* ATMega1284P
* ATMega2560
* ATMega256RFR2
* ATSAMD21 (untested, may not work)
