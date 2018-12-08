My main function is in scrabble.cpp
Dictionary.cpp includes Dictionary.h
I do not have cpp files for Square and Tile
I also did not use ExchangeMove and PassMove so I deleted those classes and also the Move superclass. I made PlaceMove its own class without inheritance.

I use the following command to compile the executable:

make

To run the executable use the command:

./scrabble config.txt

or to use another config file:

./scrabble <config file>

To delete all o files and the executable use:

make clean
