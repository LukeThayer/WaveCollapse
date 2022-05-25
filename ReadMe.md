

# 2-D Wave collapse function

## Goal:
 given an NxM size grid the algorthim will populate the grid with tiles using the wave collapse function

## Input 
 User must provide a set of tiles labeled with sockets in the form JSON


### Algorthim
The program first assigns every space of the grid a superposition containing all possible tiles then at random chooses a tile
and gives a random tile. Then iterates the superposition of the surrounding tiles to only contain valid superposition values bbased on the sockets of the 
placed tile.