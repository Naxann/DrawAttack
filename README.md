# DrawAttack

Network drawing game. One player is drawing, others are guessing. The first player who found the word win.

# Server

How to create a server ?

Section will be updated soon

If you own a server and want to add your server in the official list, please add a new issue

# Release

| DrawAttack 1.4 | Link |
| Server | x86 version x64 version |


# Compilation

This project is using cpp3ds, so it is possible to emulate the app before testing it on the 3DS.

If you want to compile the emulated app, you have to get a recent Ubuntu. Recommended OS is XUbuntu 17.04.

To edit and compile the project, first get the git project with recursive command :
```bash
git clone --recursive https://github.com/Naxann/DrawAttack
```

You can use a Virtual Machine with VirtualBox and shared folder. It allows you to develop on your host system, whatever it is, and handle only the compilation in the guest.
Here is a link of a VM file already pre-installed with all the tools needed :

Just change the shared folder to the folder containing the project, and check that the name is **Homebrew3DS**

Then in a terminal (in the VM if you are using it), use this command to install all the prerequisites :
```bash
./dev/install.sh
```

If you want to use the emulation mode, use also this command : 
```bash
./dev/install-emu.sh
```

Then to compile only the 3DS app
```
./build.sh
```
To compile only the server
```
./build.sh --without-3DS -with-server
```
To compile everything, with the emulated app
```
./build.sh --with-server --with-emu
```

# Credits

**Original game** - Cruel

**RichText class** - [skyrpex](https://github.com/skyrpex/RichText)

**Spanish translation** - Garcia98, JJTapia19, fmkid

**German translation** - SignZ

**Dutch translation** - Games&Stuff, Tjessx
