Program tested on flip1 (flip1.engr.oregonstate.edu) test on other school servers at your own risk.
Normally, this wouldn't be a problem, but since strings in C are a ticking time bomb who knows!


How to run:
-------------------------
Clientside:

    I've included the compiled c++ files in the .zip, but if you want to build from scratch just run

        g++ chat.cpp CLI.cpp main.cpp -o build

    Followed by..

        build flip1.engr.oregonstate.edu 55554

    The latter CLA, you can specify any open port on that you can find.

Serverside:

    IMPORTANT - I wrote this in Python3

    type ..

        python3 index.py 55554

    Again, you can specify any port that you would like.

How to use:
----------------------------------
Start up the server first, then create a handle for the server name to whatever you want.
Start up the client side, and again, create a handle for what you want your prompt to be.

FIRST MESSAGE MUST BE SENT FROM CLIENT - After that you can take turns between client and server, exchanging messages.
That is until someone types \quit per assignment requirements
