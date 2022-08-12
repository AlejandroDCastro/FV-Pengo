# FV-Pengo
Individual practice of the subject of *Fundamentals of Videogames*.
<br>
[Pengo remake for MSX][1] programmed in **C++** and **SFML**, by Alejandro Castro Valero.

[1]: https://youtu.be/T3YlUYsu7u0

***

## Requirements
* **Ubuntu 16.04** operating system
* **GCC** compiler
* **CMAKE**
* **VSCode** editor

***

## Compilation

* `cd Pengo`
* `cmake -H. -Bbuild` generate the makefile
* `cd build`
* `make`
* `mv exe ..`
* `cd ..`
* `./exe`

***

## Development
Full game features.

### Done
* Ability to push/destroy blocks
* Pengo moves around the environment with the conditions of the original game.
* Pengo can remove adult Sno-Bees using blocks.
* If Pengo kills all the Sno-Bees, you go to the next level.
* The Sno-Bees appear in the environment to fill in for those that are eliminated as in the original game. However, the egg phase is not necessary.
* Pengo has three lives. Dies if collided three times with any Sno-Bee.
* Add the star blocks and their associated functionality.
* Add margin limit and its stun functionality.
* Sno-Bees eggs can be removed.
* The Sno-Bees can break blocks to get to Pengo.
* Generate random mazes.

### Future lines
* Implement the game HUD.
* Implement the escape process of the Sno-Bees.
* Transition between screens.
* Interpolated loop for rendering.

***
To see the full details of the development and requirements, click [here](https://github.com/AlejandroDCastro/FV-Pengo/blob/master/FV%20PI%202020%20Pengo.pdf);
***

## Keyboard controls

* `UP` Move up
* `LEFT` Move left
* `DOWN` Move down
* `RIGHT` Move right
* `SPACE` Push
* `G` God mode (Pengo is immortal)
* `X` Death and level restart
* `N` Go next level
* `ESC` Exit

***

## Screenshots

<img src="https://github.com/AlejandroDCastro/FV-Pengo/blob/master/Pengo/pics/pic1.png" alt="Picture 1" width="400">&nbsp;<img src="https://github.com/AlejandroDCastro/FV-Pengo/blob/master/Pengo/pics/pic2.png" alt="Picture 2" width="400">
<br>
<img src="https://github.com/AlejandroDCastro/FV-Pengo/blob/master/Pengo/pics/pic3.png" alt="Picture 3" width="400">
