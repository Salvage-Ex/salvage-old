
Debian
====================
This directory contains files used to package nitrousd/nitrous-qt
for Debian-based Linux systems. If you compile nitrousd/nitrous-qt yourself, there are some useful files here.

## nitrous: URI support ##


nitrous-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install nitrous-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your nitrousqt binary to `/usr/bin`
and the `../../share/pixmaps/nitrous128.png` to `/usr/share/pixmaps`

nitrous-qt.protocol (KDE)

