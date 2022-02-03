# Pong Plus Plus

WINDOWS ONLY

This is a version of pong built using pure C++ (no game engines or libraries) to improve my understanding of the language. I gained a more in depth understanding of features I have previously used in game engines (e.g. rendering to a window, tracking delta time, managing collision detection using bounding boxes).
I also improved my C++ skills and gained became more familiar with programming games from scratch.

<img src="https://github.com/JACPro/JACPro.github.io/blob/main/images/PongGame.gif" title="Picking up Fuel" width="32%"></img>
<img src="https://github.com/JACPro/JACPro.github.io/blob/main/images/PongOptions.gif" title="Score Multipliers" width="32%"></img>
<img src="https://github.com/JACPro/JACPro.github.io/blob/main/images/PongMainMenu.png" title="Out of Fuel" width="32%"></img>
<img src="https://github.com/JACPro/JACPro.github.io/blob/main/images/PongGame.png" title="Start Screen" width="32%"></img>
<img src="https://github.com/JACPro/JACPro.github.io/blob/main/images/PongPlayerMenu.png" title="Finish Line" width="32%"></img> 
<img src="https://github.com/JACPro/JACPro.github.io/blob/main/images/PongOptionsMenu.png" title="Level Complete" width="32%"></img> 

___
This game was made with help from an excellent YouTube tutorial series by Dan Zaidan, which can be found [here.](https://www.youtube.com/playlist?list=PL7Ej6SUky135IAAR3PFCFyiVwanauRqj3)
___

After completing the tutorial, I was able to harness my learning to develop my own improvements to the game:
* Even text spacing regardless of letter width
* Ball speed increases the longer a round continues (and player move speed increases to compensate)
* Choice of colour/theme options
* Tiny paddles mode
* Add SFX (random C major note played on each ball hit using Windows' Beep() function)

<!---
* TODO - AI tries to hit the ball with the end of the pad instead of the middle to throw the player off
* TODO - Different AI difficulties
* TODO - Hard AI difficulty calculates the position it needs to be in to hit the ball as soon as the player hits it (rather than chasing the ball based only on its current position)
* TODO - Round paddles mode
* TODO - Graphics mode
-->
