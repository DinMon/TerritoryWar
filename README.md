# TerritoryWar

**Original plan:** TerritoryWar Shooter is a top-down shooter where the main goal is to survive the night while monsters are attacking the player. Design patterns, data structures and other techniques will be used to build the game.

**How it turn out:** A basic top down shooter where the AI enemies path to the player to kill him/her. The planning phase where player needed to plan the layout of their territory were partly implemented but due to lack of time text files were used to read the tilemap. Player had different components such as health, damage and so on which influence by enemies or use against enemies.

## What I learn

* Designing the architecture using design pattern by weighting their pros and cons to alleviate the burden of maintening code :) . 
* Learning about different design patterns, mainly:
..* Composite and Component Pattern
..* State Pattern
* Using SFML framework to build the gameplay and simple GUI (turns out it was harder to implement everything that was planned as SFML framework was pretty much low-level.)
* Integrating a thread-pool to cater for AI enemies pathfinding causing glitches (also learn that because I was running 2 consoles 1 for output stuff on the screen and one for the game it were slowing down the game.)
* Reading gameplay variables from text files for flexibility of non-programmers.
