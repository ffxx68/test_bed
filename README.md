# test_bed
Testing programs for the Sharp CE-140F emulator projects

Referring to the project at

https://github.com/ffxx68/Sharp_ce140f_emul

an issue has been raised (Issue #4 there), as some board-device combinations aren't working. Can't tell why...
This is a basic (both in language and functionalities!) test program and firmware, that I hope would help narrow down and, eventually, solve the issue!

On your Nucleo board, upload the firmware attached here (test_bed.NUCLEO_L432KC.bin).
Note how this would overwrite the CE-140F emulator fw, but you can always download the original emulator firmware .bin from here:
https://github.com/ffxx68/Sharp_ce140f_emul/releases/tag/PCB_v1_tested

To run your tests, first attach the board, still unplugged from USB, to the Sharp PC, then turn on Sharp and plug the USB power.
If you can, start a serial terminal on the COM-port exposed on the USB by the Nucleo board: standard 9600 baud. Putty, or similar terminal programs would do the job. But that isn't mandatory, at least to run the input test (DEF-C).

The input test (`DEF-C`) would show either 0 or 128 as the return value, changed by a button press (or any key, over serial terminal).
The output test (`DEF-D`) would show a number of raise/fall messages, either with 'f' or '0' values, with last two showing '4' instead (see video).

Better than describing how to use it, let me show it with a brief video...

https://youtu.be/3NJVXnl8p5Y
