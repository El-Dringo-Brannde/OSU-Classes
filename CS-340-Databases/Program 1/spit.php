<!DOCTYPE html>
<html>
<body>
	<?php
		if (strlen($_POST["pass"]) <= 6) {
			echo "Need a longer password";
			echo '<a href="http://web.engr.oregonstate.edu/~dringb/CS_340/SignUp.html">Click here</a>';
			die();
		}

		elseif (strlen($_POST["user"]) >= 20){
			echo "Your username is too long!";
			echo '<a href="http://web.engr.oregonstate.edu/~dringb/CS_340/SignUp.html">Click here</a>';
			die();
		}
		elseif (empty($_POST["user"])){
			echo "Put in a user name!";
			echo '<a href="http://web.engr.oregonstate.edu/~dringb/CS_340/SignUp.html">Click here</a>';
			die();
		}
		elseif (empty($_POST["firstname"])){
			echo "Add a firstname!";
			echo '<a href="http://web.engr.oregonstate.edu/~dringb/CS_340/SignUp.html">Click here</a>';
			die();
		}
		elseif (strlen($_POST["firstname"]) >= 20) {
			echo "Holy hell you have a long first name";
			echo '<a href="http://web.engr.oregonstate.edu/~dringb/CS_340/SignUp.html">Click here</a>';
			die();
		}
		elseif (empty($_POST["lastname"])){
			echo "Add a lastname!";
			echo '<a href="http://web.engr.oregonstate.edu/~dringb/CS_340/SignUp.html">Click here</a>';
			die();
		}
		elseif (strlen($_POST["lastname"]) >= 20){
			echo "Your lastname is too long.. Oddly";
			echo '<a href="http://web.engr.oregonstate.edu/~dringb/CS_340/SignUp.html">Click here</a>';
			die();
		}
		elseif (empty($_POST["email"])){
			echo "Add an email!";
			echo '<a href="http://web.engr.oregonstate.edu/~dringb/CS_340/SignUp.html">Click here</a>';
			die();
		}
		elseif (strlen($_POST["email"]) >= 40) {
			echo "Your email is too long!";
			echo '<a href="http://web.engr.oregonstate.edu/~dringb/CS_340/SignUp.html">Click here</a>';
			die();
		}
		elseif (empty($_POST["age"])){
			echo "Add your age!";
			echo '<a href="http://web.engr.oregonstate.edu/~dringb/CS_340/SignUp.html">Click here</a>';
			die();
		}

		if (strlen($_POST["pass"]) >= 6){
			$servername = 'mysql.cs.orst.edu';
			$username = 'cs340_dringb';
			$password = '2885';
			$dbname = 'cs340_dringb';

			$connection = new mysqli($servername, $username, $password, $dbname);

			if (!$connection){
				die("Connection Fail!" . mysqli_connect_error());
			}
			else{
				echo "Connected! <br>";
				$stmt = $connection->prepare("INSERT INTO users (username, firstname, lastname, email, password, age)
				VALUES (?,?,?,?,?,?)");



				$stmt -> bind_param("sssssi", $user, $fname, $lname, $email, $pass, $age);


  			$user = $_POST["user"];
				$fname = $_POST["firstname"];
				$lname = $_POST["lastname"];
				$email = $_POST["email"];
				$pass = $_POST["pass"];
				$age = $_POST["age"];

				$stmt->execute();

				echo "stuff";
      }
    }

		$stmt -> close();
		$connection -> close();
	?>

</body>
</html>
