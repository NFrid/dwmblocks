# rootblocks

Modular status bar for xsetroot/command output written in c.

# muh fork

Slightly refactored dwmblocks I suppose...

Made a signal subscriber that will automatically send a signal to update a block.
Examples are in config.h (make also sure that when you kill a rootblock process
by violence a.k.a. killall and stuff you also kill all instances of subtosignal).

# usage

To use rootblocks first run 'make' and then install it with 'sudo make install'.
After that you can put rootblocks in your xinitrc or other startup script.

`-p` flag makes it work in command output mode.

# modifying blocks

The statusbar is made from text output from commandline programs.

Blocks are added and removed by editing the config.h header file as well as some
other settings represented there.

There's no config.def.h. If I update and you pull it, you gonna figure out what
you need to change. 

Well, there's no point using diy stuff if you don't like to play with it anyways...
