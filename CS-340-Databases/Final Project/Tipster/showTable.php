<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="index.css">
	</head>
<body>

	<?php
    if (isset($_COOKIE['user'])){
      require_once 'GetWallpaper.php';
      require_once 'NavBar.php';
    }
    else {
      echo '<script> window.location.href = "login.html";</script>';
    }
	include 'connectvarsEECS.php';
	$conn = mysqli_connect(servername, username, password, dbname);
	if (!$conn) {
		die('Could not connect: ' . mysql_error());
	}
	$user = $_COOKIE['user'];
	$query = "SELECT D.DeliveryID,D.Date,D.Time,D.OrderTotal,D.`Tip$`,L.Address,L.Street,L.Apt FROM Delivery D,Location L where D.DeliveryID=L.DeliveryID And D.Username = '$user'";

	$result = mysqli_query($conn, $query);
	if (!$result) {
		die("Query to show fields from table failed");
	}

	$fields_num = mysqli_num_fields($result);
	echo "<h1>Table: {$table}</h1>";
	echo "<table id='t01'><tr>";
	// printing table headers
	for($i=0; $i<$fields_num; $i++) {
		$field = mysqli_fetch_field($result);
		echo "<td><b>{$field->name}</b></td>";
	}
	echo "<td>Edit</td>";
	echo "</tr>\n";
	while($row = mysqli_fetch_row($result)) {
		echo "<form action=\"./ChangeDelivery.php\" method=\"POST\"";
		echo "<tr>";
		// $row is array... foreach( .. ) puts every element
		// of $row to $cell variable

		foreach($row as $cell)
			echo "<td>$cell</td>";
		echo"<td><input type=\"submit\" name=\"Edit\" value = \"Edit #$row[0]\"/></td>";
		echo "</tr>\n";

	}
	echo "</form>";

	mysqli_free_result($result);
	mysqli_close($conn);
	?>
</body>

</html>
