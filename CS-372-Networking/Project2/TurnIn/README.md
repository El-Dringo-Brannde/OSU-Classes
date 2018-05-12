# IMPORTANT
Since we can't have folders in our .zip turn in project, I was unsure how to prove that my file streaming was actually working. Since we use 1 folder, we can't really prove that there was a new file created. So I had created a .mp4 video for a demo in the .zip. This also shows that the program works fine on my machine

## Video Link
https://media.oregonstate.edu/media/t/0_oznycslx

# Build / Compile
To build the server-side C project simply use ` gcc main.c -o build `.

The client side project was written in Python3, no building needed.

# Running
Connect 2 instances to FLIP of some sort then..

To run the server side project use ` build 12345 ` (Or whatever port you can find available).

To run the client-side to connect use ` python3 index.py localhost {Connecting Port} {Option} {(Optional)Filename} {Receiving port}`

# Extra credit WAS done

Only the binary file section though, so theoretically you can FTP any type of file via the CLI. Just specify what you want in the filename


# Notes

Since I figured it'd be bad if clients could kill the server running on purpose. To kill the server merely just hit ctrl+c.

Duplicate file names do not occur, they merely over write eachother