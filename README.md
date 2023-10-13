# WFC
Simple implementation of WFC

Inspiration from https://github.com/What42Pizza/WFC-Tiles-Processing

You can find examples of final results in [examples](examples) 

### Description of algorithm
Chooses a random tile and random texture. Afterwards it checks surrounding tiles and removes any that don't fit the connection rules and adds them to pending list.
Then it chooses tile with lowest entropy from the pending list and checks neighbours. Repeats until whole grid is filled.

You can specify which folder to use in Game::LoadTiles().
