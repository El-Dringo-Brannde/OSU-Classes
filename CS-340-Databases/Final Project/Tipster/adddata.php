<!DOCTYPE HTML>
<html>
<head>
<?php
		$servername = 'mysql.cs.orst.edu';
    $username = 'cs340_dringb';
    $password = '2885';
    $dbname = 'cs340_dringb';

    $connection = new mysqli($servername, $username, $password, $dbname);
	if (!$connection){
        die("Connection failed: " . mysqli_connect_error());
	}
	else{
		$stmt = $connection->prepare("INSERT INTO Delivery (`DeliveryID`,`Date` ,`Time`, `Username`,`OrderTotal`,`Tip$`)
		 VALUES (DEFAULT,?,?,?,?,?)");
		$stmt -> bind_param("sssdd",$date,$time,$username,$total,$tip);

		$total = $_POST["total"];
		$tip = $_POST["tip"];
		$username = $_POST["username"];
		$date = $_POST["date"];
		$time = $_POST["time"];

		$stmt -> execute();
		$insertID = $connection -> insert_id;
		$stmt -> close();

		$stmt = $connection -> prepare ("INSERT INTO Location(`DeliveryID`, `Address`,`Street`,`APT`)
		VALUES ($insertID,?,?,?)");
		$stmt -> bind_param("iss", $add,$street,$apt);

		$add = $_POST["address"];
		$apt = $_POST["apt"];
		if ($apt == "")
			$apt = NULL;
		$street = $_POST["street"];
		$stmt -> execute();
		$stmt -> close();
		$connection -> close();
		echo '<script> window.location.href = "Delivery.php";</script>';
	}
	?>
</head>
</html>
