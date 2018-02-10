# Chess
Chess application built using SDL2 and C++. Has functioning GUI as well as valid move checked. 

To run, download SDL2 and SDL_image and link them appropiately. You will also need to download chess piece sprites. This app wasn't fully 
finished and I would likely want to rewrite it later. The changes I would make would be rewriting the Piece class to be an abstract class
with the generateMoves() function as a virtual function. Additionally, I would colour key the sprites so that they show the background 
tiles. 

Finally, I would like to create a simple AI after all of these changes using a minmax algorithm with depth. 
