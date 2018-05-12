compile:
	javac Randomness.java
	javac Card.java
	javac GameState.java
	javac Player.java
	javac PlayDominion.java
	
play:
	java Play

clean:
	rm -f *.class