# backlight

Simple program for controlling backlight of notebook main screen


Make sure you execute following commands to be able to access config files as a regular user:

	sudo su -c 'echo SUBSYSTEM==\"backlight\", RUN+=\"/bin/chmod 0666 /sys/class/backlight/%k/brightness /sys/class/backlight/%k/bl_power\" > /etc/udev/rules.d/99-backlight.rules'
	sudo reboot


## Installation
	
	git clone https://github.com/ceskyDJ/backlight.git
	cd backlight
	make
	sudo make install

## Usage
	
	backlight [option]
	
		up:	increases brightness by 10%
		down:	decreases brightness by 10%
		max:	sets brightness to 100%
		min:	sets brightness to 0%
		on:	turns the screen on
		off:	turns the screen off



Thanks for using this program. Feel free to modify, improve, and share. Open source spirit.
