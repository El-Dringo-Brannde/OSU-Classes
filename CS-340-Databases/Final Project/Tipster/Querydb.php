<!DOCTYPE HTML>
<html>
<head>
  <?php
    require_once 'GetWallpaper.php';
    require_once 'NavBar.php';
  ?>
  <link rel="stylesheet" href="index.css">
  <style>
    table{
      margin-left: auto;
      margin-right: auto;
    }
    h1{
      text-align: center;
    }
  </style>
</head>
<body>
<?php
$servername = 'mysql.cs.orst.edu';
$username = 'cs340_dringb';
$password = '2885';
$dbname = 'cs340_dringb';

$conn = mysqli_connect($servername, $username, $password, $dbname);
if (!$conn) {
  die('Could not connect: ' . mysql_error());
}
  $address = $_POST['address'];
  $street = $_POST['street'];
  $apt = $_POST['apt'];
  if ($apt == NULL)
    $apt = NULL;

  if ($apt != NULL){
    $query = "SELECT Location.Address, Location.Street,Location.APT,Delivery.Date, Delivery.Time, Delivery.OrderTotal,Delivery.`Tip$` FROM Location, Delivery WHERE `Location`.`DeliveryID` = `Delivery`.`DeliveryID` AND
    LOWER(`Location`.`Street`) = LOWER(\"$street\") and `Location`.`Address` = $address and
    `Location`.`APT` = '$apt'";
  }
  else {
    $query = "SELECT Location.Address, Location.Street,Location.APT,Delivery.Date, Delivery.Time, Delivery.OrderTotal,Delivery.`Tip$`  FROM Location, Delivery WHERE `Location`.`DeliveryID` = `Delivery`.`DeliveryID` AND
    LOWER(`Location`.`Street`) = LOWER(\"$street\") and `Location`.`Address` = $address and
    `Location`.`APT` <=> NULL";
  }
  echo "<h1> Deliveries to $address $street $apt in the past </h1>";
  //mysql_real_escape_string($street);
  $red = mysqli_query($conn,$query);
	$fields_num = mysqli_num_fields($red);
	//echo "<h1>Table: {$table}</h1>";
	echo "<table id='t01'><tr>";
	// printing table headers
	for($i=0; $i<$fields_num; $i++) {
		$field = mysqli_fetch_field($red);
		echo "<td><b>{$field->name}</b></td>";
	}
	echo "</tr>\n";
	while($row = mysqli_fetch_row($red)) {
		echo "<tr>";
		// $row is array... foreach( .. ) puts every element
		// of $row to $cell variable
		foreach($row as $cell)
			echo "<td>$cell</td>";
		echo "</tr>\n";

  	//$result = mysqli_query($conn, $query);
  	if (!$red) {
  		die("Query to show fields from table failed");
  	}
  }
?>
<style>
  form {
    text-align: center;
    font-family: monospace;
  }
  table{
    text-align: center;
  }
  body {
    text-align: center;
  }
 </style>
</body>
</html>
