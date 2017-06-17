# LED MATRIX

- - - - - -
## Introduction
- - - - - -

### I2C protocol

I2C (pronounced i squared c or i two c) is a serial computer bus
and data communication protocol, invented by Philips Semiconductor.

It's typically used for attaching low-speed peripheral Integrated Circuits
to processors and microcontrollers in short-distances, such as intra-board communication.

The phillips I2C protocol defines the concept of master and slave devices.
A master device is one that is in charge of the bus at the present time
and controls the clock and generates START and STOP signals.
Slaves simply listen to the bus and act on controls and data that they are sent.

The master can send data to a slave or receive data from a slave - slaves
do not transfer data between themselves.

The I2C interface uses two bi-directional lines, i.e. either device could "drive" either line.
these lines are SDA for data, and SCL for clock.


I2C basic command sequence (master writes to slave)

01. Send the START bit (S). (done by master)
02. Send the slave address (ADDR). (done by master)
03. Send the Write(W)-0 bit. (done by master)
04. Wait for an acknowledge bit (A). (done by master)
05. Send acknowledge bit (A). (done by slave)
06. Receive an acknowledge bit (A). (done by master)
07. Send the data byte (8 bits) (DATA). (done by master)
08. Send acknowledge bit (A). (done by slave)
09. Receive an acknowledge bit (A). (done by master)
10. Send the STOP bit (P).

I2C basic command sequence (master reads from slave)

01. Send the START bit (S). (done by master)
02. Send the slave address (ADDR). (done by master)
03. Send the Read(R)-1 bit. (done by master)
04. Wait for an acknowledge bit (A). (done by master)
05. Send acknowledge bit (A). (done by slave)
06. Receive an acknowledge bit (A). (done by master)
07. Receive the data byte (8 bits) (DATA). (done by master)
08. Send acknowledge bit (A). (done by master)
09. Receive an acknowledge bit (A). (done by slave)
10. Send the STOP bit (P).

In both cases, steps 7 through 9 can be repeated n times before master sends
the stop bit (P).

The acknowledge bit (A) means that the data transfer was successful, so if it's
not received, the device that sent the data can try to send it again.

The Start bit (S) can only be generated by a master device, and it means that
SCL is in a logic one and that SDA is falling from a logic one (or is in a
"falling edge")

The Stop bit (P) can only be generated by a master device, and it means that
SCL is in a logic one and that SDA is rising from a logic zero (or is in a
"rising edge")

When a slave receives a start bit (S) it resets its internal bus logic.

A slow slave device may need to stop the bus while it gathers data.
It can do this by holding the clock line (SCL) low ,forcing
the master into a wait state. The master must then wait until SCL is released
before proceeding. This can be done because the lines are "open drain"
i.e. if one device holds a line low, the other cannot try to put it into high.

The I2C standard is very attractive to manufacturers, because of its simplicity
and ease of use but requires royalties, so some
manufacturers say that their devices "use a 2 wire interface", and thus avoid
explicitly using the term I2C and having to pay royalties.

I2C may be used with VGA, DVI and HDMI ports, because they are a superset of the I2C
connectionts pinout, i.e. they include an SDA, SCL, ground (GND) and +5VDC pins, all
the necessary pins/connection lines for I2C communication.


### Hardware Drivers

Device drivers take on a special role in the Linux kernel. They are distinct “black
boxes” that make a particular piece of hardware respond to a well-defined internal
programming interface; they hide completely the details of how the device works.
User activities are performed by means of a set of standardized calls that are indepen-
dent of the specific driver; mapping those calls to device-specific operations that act
on real hardware is then the role of the device driver. This programming interface is
such that drivers can be built separately from the rest of the kernel and “plugged in”
at runtime when needed. This modularity makes Linux drivers relatively easy to write,
to the point that there are now hundreds of them available. [1]

To implement a driver for a character device, it must be programmed in the C programming
language, as a module for the kernel, and a special Makfile with the assignment for

```
obj-m
```
which uses the kernel build system, and not the "vainilla" make build process.

A few important things to keep in mind are:
*   floating point numbers are not used in kernel programming
*   testing kernel modules can be dangerous, so extreme caution is adviced, using a "sacrificial" computer to test modules on is a common practice
*   the linux kernel changes very rapidly, so programming a module for one version may not work in the next, so it is recommended to build against the kernel version of interest, or to continually update the module should the device driver API change


### The LED MATRIX Project

This project consists in developing a driver for the Linux kernel, to use an
HT16K33 controlled LED backpack (by adafruit), as a file, and call it from a
library (programmed in the C programming language) that is used by a web
application to send text and some other symbols (namely, some emoji) to display
them in the LED matrix.


- - - - - -
## Technical Specifications
- - - - - -

### Driver

The driver was programmed in the C programming language, as it is the standard
when programming device drivers, it's the most well documented, it's the
most familiar to the ones involed in the development of the project, and it
was required as an assingment for a course on Operating System Principles.

The Tools used in the development of the driver include the GNU Compiler
Collection's C language compiler, `gcc` for compiling the source code,
Sublime Text as a text editor, GNU Make to automate the build process, Git
for source version control, SSH to connect to the target machine,
and the Bourne Again Shell (bash) as a shell.


### Library

The library was programmed in the C programming language, as it is the most
familiar and comfortable to the ones involved in the development of the
project, not to mention, it's very efficient in use of resources, and very
fast to execute, which are important points in embedded device programming.

The tools used in the development of the library include the GNU Compiler
Collection's C language compiler, `gcc` for compiling the source code,
Vi IMproved (Vim) as a text editor, GNU Make to automate the build process,
Git for source version control, SSH to connect to the development machine,
ack to search the source code once it reached a few hundred lines,
ZSH as a shell, and The Terminal Multplexer (Tmux) to manage several virtual
terminal emulators to run Git, SSH. Vim, ack, and Make simultaneously.


### Web Application

The web application was programmed in HTML, JavaScript, and JQuery, with
Twitter's Bootstrap to make the application work with both desktop and mobile
web browsers, because of both a lack of familiarity with PHP, which was the
required language in the assignment, as well as familiarity with Javascript,
JQuery, Bootstrap, and Node.js with projects involving C programs.

It makes use of an emoji picker library in order to provide to the user an
easy way to use the avaliable emoji set.

- - - - - -
## Program Design
- - - - - -

### Inner Workings and Examples

The web application provides a simple interface for the user to write a
message, select emoji (if desired) from the emoji picker and send the string to
the server to be processed and printed on the LED matrix

The message is passed as a parameter to the
library wrapper, it is processed using the library and then displayed through the LED
Matrix by writting values to the files created in the device tree when the
driver is loaded in the system.

Because the driver creates a file in the file system, the library simply uses
a file open function `fopen()` to write to the device like so:

```c
/* a char* filename variable is initialized before this function is called. */
/* and fd is a FILE* varible, to write to the file after fopen() is called. */
fd = fopen ( filename, "w" ); /* here "w" is used to specify write mode. */
/* afterwards data is written to the file as text (i.e. data in a char array).*/
fprintf ( fd, data );
/* and lastly, the file is closed. */
fclose ( fd );
```


### Communication between Components

The web application front-end communicates with the web application back-end
using web api methods to send the messages put in by the user to process them,
this was easily developed in Express for the back-end, and JQuery for the
front-end

The message sent by the front-end is obtained in the back-end and sent to the
library wrapper, which is the program that prints on the LED matrix by using
the functions in the library to write to the file created by the driver

- - - - - -
## Use Instructions
- - - - - -

### Requirements

NodeJS 6.11 or newer.
npm in order to install dependencies. 

A LED matrix, and the HT16K33 controller LED backpack by adafruit were used in
the development of this project, though similar backpacks may provide similar
functionality, the steps mentioned in this document are not guaranteed to work
with other backpacks

A VGA port was used in this project, but a DVI or HDMI port will most likely
serve the same purpose

Jumper cables we used to connect the components, though any copper cable is
likely to work as well

This project was developed and tested on a system running Linux Mint Debian
Edition 2 "Betsy", though it should work on other versions of GNU/Linux,
it's not guaranteed, and the authors take no responsibility should you choose
to try to replicate what was obtained here

Node.js 6.11 or newer is required to install the dependencies of the web
application, as well as to run it.


### Set Up

*   Get a Computer with an x86 or x86_64 processor (a GB mini computer with a
single core Intel Atom CPU was used), that also has a VGA port
*   Get the HT16K33 and the LED matrix
*   Install LDME 2 on the computer, and install the build-essential, and glib2.0-dev packages
*   Install Node.js
After setting the LED matrix on the backpack, as per adafruit's instructions
(soldering is optional)
*   Connect the pin slot marked as - to GND
*   Connect the pin slot marked as + to +5VDC
*   Connect the pin slot marked as D to SDA
*   Connect the pin slot marked as C to SDC

The VGA port has 15 pin slots, that look like this

```
.....
 .....
.....
```

The only pins that are needed for I2C communication are:
*   GND (the top leftmost pin)
*   +5VDC (the middle, second leftmost pin)
*   SDC (the bottom leftmost pin)
*   and SDA (the bottom, second from the right pin)

the driver is then compiled by running
```bash
make -C /usr/src/linux-headers-$(uname -r) M=$(pwd modules)
```
in the directory for the source code of the driver

and then loaded by running
```bash
insmod ledMat.ko
```
as superuser (a.k.a. root)

after the driver has been loaded, change directory to the library directory
run `make`, and then go up a level in the source tree


```bash
.                        # user should be in this level
|-- documentation.md
|-- driver
|   |-- ledMat.c
|   `-- Makefile
|-- library
|   |-- led_mat_library.c
|   |-- led_mat_library.h
|   |-- Makefile
|   |-- text_print.c
|   |-- text_print.h
|   `-- wrapper.c
|-- LICENSE
|-- README.md
`-- server
    |-- package.json
    |-- public
    `-- server.js

```

### How To

Once the kernel module is loaded, and the library and wrapper are compile, and
the library and wrapper are compiledd, run the web application, by running in a
shell in a terminal emulator window, the command

```
nodejs server/server.js
```

then access the web application through a web browser like Mozilla Firefox or
Google Chrome, by entering the IP address of the machine in which the program
is running, and using the port 8080, e.g. `http://192.168.0.31:8080/`

- - - - - -
## Activities Log
- - - - - -

### David Cordero

```
|-- Cloned GitHub repository, read README.md and updated it, discussed project structure based on partner's previous projects for a related course [2017-06-05]
|-- Read about Linux Device Driver development (book Linux Device Drivers) [2017-06-05, 2017-06-12]
|   |-- Look at other examples of C libraries being used from PHP and Javascript [[2017-06-05]]
|   |-- Investigated about the I[2C protocol/devices/connections and implementation in software 2017-06-06]
|   |-- Tested the i[2c-tools programs 2017-06-07]
|   |-- Troubleshooted the i[2c connection from the VGA port 2017-06-08]
|   |-- Tested the LED matrix with an Arduino, using the code provided by adafruit [2017-06-09]
|   |-- Re-started i[2c-tools tests and verified pin connections 2017-06-09]
|   |-- Studied code by adafruit again to understand better how data is written to backpack micro-controller/chip from code [2017-06-11]
|   `-- Defined what characters would be supported, and rough source code structure and functions [2017-06-12]
|-- Started writing the library to control the LED matrix [2017-06-13]
|-- Tested the functionality with i2c-tools, and a single character using open(), ioctl(), and close() [2017-06-14]
|-- Added delay to simulate animation in the lighting of the LEDs [2017-06-15]
|-- Added array to contain references to all the suported characters binary arrays [2017-06-15]
|-- Added all Letters, Numbers and Emoji binary arrays defining the LEDs to be turned on [2017-06-15]
|-- Driver was completed, so refactored to use file provided by the driver, as well as fopen(), fprintf(), and fclose() instead of open(), ioctl(), and close() [2017-06-16]
|-- Refactor changed the way to write to the LED matrix, so added a conversion between byte (`uint8_t`) and numbers in char arrays [2017-06-16]
|-- LED matrix bit mappings are strange, so had to fix positioning of the turned on bits to look correct on the LED matrix [2017-06-16]
|-- Added support fir dynamic input processing, i.e. the wrapper could receive arbitrarily sized input and it would print correctly on the matrix [2017-06-16]
`-- Finish up refactoring, commenting code, and writing external documentation [2017-06-16]
```

### Manuel Zumbado

Add basic server 2017-06-05
add option to show public/index.html 2017-06-12
add main html page 2017-06-12
move server.js to its own location 2017-06-12
add option to show main page 2017-06-12
add comments to code 2017-06-13
add option to show received message 2017-06-13
fix: json response 2017-06-13
add base driver 2017-06-14
add .gitignore 2017-06-14
update driver 2017-06-15
remove probe methods, change to explicit instantiation 2017-06-15
fix error 2017-06-15
add one file for each row of the matrix 2017-06-15
fix error 2017-06-15
refractor and comment code 2017-06-16
fix typo 2017-06-16
add emoji support 2017-06-16
Add regex string replace functionality 2017-06-16
add emoji lib files 2017-06-16
add emoji lib files 2017-06-17
include child_p to communicate with library wrapper 2017-06-17
fix error 2017-06-17
update emojis 2017-06-17
add documentation 2017-06-17

- - - - - -
## State of the Project
- - - - - -

### Final state of Development (as of 2017-06-16)

Web application runs, renders properly on Desktop and Mobile Web Browsers

Library Works, can display 46 different characters/symbols on the LED Matrix

Web application can call the library wrapper program and execute its functionality

GitHub repository's feature branches are merged

### Challenges faced on Development

As there are many functionalities that are open to implementation, some
features had to be decided on, like characters supported, and how these
would be communicated from web application to the library, as well as GUI
layout, "render" delays on the matrix to make the letters appear animated, etc.

Programming and debugging kernel modules present the challenge of potentially
crashing the module at best, and up to breaking a computer's operating system,
so extreme care should be taken when loading kernel modules that contain
functions one is not familiar with, initially during the development of this
project, the module crashed and the computer had to be rebooted to completely
clear the resources allocated by the module.

Besides that, working with hardware presents its own risks, as a connection
to the wrong pin can be as "harmless" as setting a memory register to the
wrong value, or more serious damage, like burning components, or even render a
computer unusable, as well as potentially having unhelpful documentation,
datasheets with little usable information, or plain strange defaults (of which
one was encountered, because the registers of the memory of the HT16K33 don't
have a logical mapping to the LEDs on the matrix, though it may be because
the same Micro Controller is used for different models of LED matrices).

Ployglot programming presents its own set of challenges, as APIs aren't always
well defined or documented for certain combinations of Languages,
using functionality implemented in C from Javascript was an interesting
but not easy task.

And in general, software projects whose source code-bases get larger and
larger as the complexity of the implemented version increases can become
unmanagable if care is not taken to maintain the source code architecture.

- - - - - -
## Conclusions and Recommendations
- - - - - -

Device Driver programming presents a fascinating, but challenging task, and
its integration with other software components can be fun and rewarding,
but a really large knowledgebase is needed in order to properly accomplish
it, and this knowledge is not easy to acquire, as the kernel changes very
rapidly, and documentation can become obsolete very quickly, as well as
there being great differences between userspace application programming,
and kernel programming, a good understanding of the requirements of any
software, or non-software project can be the difference between a failed
and a successful project, so all efforts on getting to understand the
requirements, as well as desired results and restrictions is a great
investment in the development of any project.

- - - - - -
## References
- - - - - -

[1] Jonathan Corbet, Alessandro Rubini, and Greg Kroah-Hartman "Linux Device Drivers, 3rd ed."

[2] http://elinux.org/Interfacing_with_I2C_Devices

[3] https://linux-sunxi.org/I2Cdev

[4] https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/Documentation/i2c/dev-interface

[5] https://learn.sparkfun.com/tutorials/i2c

[6] https://www.linuxjournal.com/article/7136?page=0,1

[7] https://davideddu.org/blog/posts/graphics-card-i2c-port-howto/#use-on-linux