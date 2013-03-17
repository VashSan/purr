Purr Music Player
=================
* Author: Alexander Schwoch
* Email: vashsan@gmail.com
* Date: 2013-03-15
* Revision: 1

Purpose
-------

I am dissatisfied with the available desktop music players. Those that
exist run either on Linux or Windows. Those that run on both are unstable
or do not comfort my requirements for a small, fast, decent player. What
you find are fat beasts cluttered with eye candy. Most of them come with
a shop that tempts you to spend your money.

Nothing of this is what I need. I need something simple, a player I can
rely on, which means it does not place commercials in its next release. If
it is capable playing MP3 and maybe OGG I am happy. That is what you will
get if you try out *Purr*.

License
-------

If you want to use, modify or distribute *Purr* you must agree to
following terms and conditions.

* You may use *Purr* free of charge at your own risk.
* You may distribute the unmodified source files and binary packages
  free of charge at your own risk.
* You may change the source files for your private and non commercial
  purposes without restriction.
* If you want to distribute modified sources or binaries you must
  * do so free of charge.
  * attribute the original work to the authors of *Purr* by providing a
    link to the project page on Github.
  * release the modified sources to the public.
* You must accept that there are no warranties tied to the sources or
  binaries. Any harm caused by this piece of software comes
  unintentionally.
* You must respect the terms of any dependent 3rd party sources, tools
  or libraries which are required to run *Purr*.
* If you want to take legal actions against the authors or maintainers of
  *Purr* you are not allowed to use, distribute or modify Purr. If you
  already started using, distributing or modifying *Purr* or any part of
  its sources you must stop immediately.

Installation
------------

### Windows
*Purr* for Windows comes in three variants. If you consider yourself an
unexperienced user chose the first one.

1. A self extracting archive which contains all files you need to run it.
   You will need to specify a folder where you want to extract the files. I
   recommend to extract the contents into the Program Files folder. A folder
   called 'purr' will be created automatically. I also recommend to place a
   shortcut to the executable on your desktop, the start menu or task bar
   for convenience. But this is up to you. A desktop link can be created by
   dragging purr.exe to the desktop while holding the ALT-key.
2. A 7zip file containing the executable and purr specific libraries. Use
   this if you have a previous installation of *Purr*. Then you just need
   to replace the files contained in the archive.
3. A 7zip file containing the QT framework libraries only. This is not the
   complete framework, just the files which are needed to run *Purr*.
   Extract them to the same location where you will find the purr.exe. This
   is optional if you have the QT 5.0.1 framework already installed. Note
   that Purr must be able to find all DLLs in the folder declared in the
   search paths.

### Linux
For the time being you will need to build the player yourself, see
instructions below. If you created or want to create a package for
a distribution let me know so I can add the information here.

### Mac
You need to figure out yourself if this works since I do not have access
to this platform so there will be no official support by me. You may help
by building the player yourself or making a donation to the Alex-needs-
a-Mac-Foundation ;-)

### Building the player
The source are available at [github](https://github.com/VashSan/purr).

You need the [Qt framework 5.0.1](http://qt-project.org/). I guess the
easiest way is to download it, start QtCreator, open the project file,
selec release mode and hit the build button. This works under Windows
and Linux and should also work with a Mac.

If you do not want to use QtCreator you will need to know how to use
*qmake*. In this case you are on your own until I have time to amend this
section.

On Windows I built the source succesfully with
[MinGW](http://www.mingw.org/) however the MSVC compiler should work as
well. On Linux I use GCC, please let me know if you have issues should you
use a different compiler. Regarding Mac: see above.

Using Purr
----------

*Purr* is quite simple and self explaining. I will add some
FAQ here if there are issues to be explained.

Contributing
------------

As you may have noticed you will find the sources on github. I will add
some coding guidelines later, however I think you will notice my style
as soon as you see the code.

The development organization done on [Trello]
(https://trello.com/board/purr-player/512d0240c91efcb743011e60). Feel
free to add some comments or vote for your favorite features. Contact me
if I missed something you think I should add to *Purr*.

Features
--------

*Purr* is very slender right now. However development just started
so be excited for new features. It can

* Play MP3 files from a playlist you create
* Save or load a playlist to/from a textfile
* The player displays
  * the current position and total time
  * the file currently playing
* Change the track position with the slider
* Change the volume of the players music output using the dial
* The playlist displays
  * the file path of the mp3 file
  * or artist and title from the ID3v1 tag if available

Upcoming
--------

These features are already in my mind. Please contact me if you
want to see more stuff inside Purr.

* improved playlist with columns
* possibility to rearrange tracks in the playlist
* adding a complete folder recursively to the playlist

Changelog
---------

* Published the first release 0.1.0
