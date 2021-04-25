#Ultimate Pong

####Description
Ultimate Pong is a recreation of classic Atari game Pong with some added features/hacks sure to enhance the game play. 
The game is built upon the Cinder graphics library 
and is meant for 2 players, with one person controlling the WASD keys and the other player controlling the arrow keys.

####Standard Controls
Key | Action
-----|---------
W | Move left paddle upwards
S | Move left paddle downwards
Up | Move right paddle upwards
Down | Move right paddle downwards
C | Start game
R | Reset/Restart game

####Cheat Controls 
Key | Action
-----|---------
A | Shrink left paddle
D | Grow left paddle
Left | Shrink right paddle
Right | Grow right paddle
Space | Reverse pong ball's horizontal velocity (switch directions)
Q | Reduce right player's score
E | Increase left player's score
, | Reduce left player's score
. | Increase right player's score

####Project Setup
#####You must have MacOS to run this project
To run the graphics portion of the game, users will need to download the [Cinder library](https://libcinder.org/download) for MacOS
and download it onto their home directory. Once downloaded, users will also need to download the [font](http://www.mattlag.com/bitfonts/)
 used for the game to their Font Book application. From there, users can run the executable "sketchpad-classifier" to start the game and 
 play using the controls listed above. If there are configurations that users wish to modify, there are constant values (e.g. kDefaultBallSpeed) 
 in the project's headers files (final-project-ARG-02/include/core) that have constant values which can be modified to the user's liking - feel free to 
 experiment and find a configuration you like!

(If you are having trouble opening the code or don't know how to run it, try downloading an IDE
such as [CLion](https://www.jetbrains.com/clion/download/#section=mac), opening the project through 
the IDE, and running the game from there using the instructions above!)


