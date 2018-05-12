<!DOCTYPE HTML>
<html>
<head>
  <link rel="stylesheet" href="index.css" />
  <style>
    table{
      text-align: center;
      margin-left: auto;
      margin-right: auto;
    }
    h1{
      text-align: center;
    }

    </style>
  <?php
    if (isset($_COOKIE['user'])){
      require_once 'GetWallpaper.php';
      require_once 'NavBar.php';
      require_once 'connectvarsEECS.php';
    }
    else {
      echo '<script> window.location.href = "login.html";</script>';
    }
  ?>
<?php
  $connection = mysqli_connect(servername, username, password, dbname);
  if (!$connection) {
    die('Could not connect: ' . mysql_error());
  }
  $sql = "SELECT Delivery.Date,Delivery.Time,`Delivery`.`Tip$`,Location.Address,Location.Street FROM `Delivery`,Location where `Tip$` > 10 and Delivery.DeliveryID = Location.DeliveryID";
  $result = mysqli_query($connection,$sql);
  echo "<h1>Best customers evar!</h1>";
  $fields_num = mysqli_num_fields($result);
  echo "<table id='t01'><tr>";
  // printing table headers
  for($i=0; $i<$fields_num; $i++) {
    $field = mysqli_fetch_field($result);
    echo "<td><b>{$field->name}</b></td>";
  }
  echo "</tr>\n";
  while($row = mysqli_fetch_row($result)) {
    echo "<tr>";
    // $row is array... foreach( .. ) puts every element
    // of $row to $cell variable
    foreach($row as $cell)
      echo "<td>$cell</td>";
    echo "</tr>\n";
  }
?>
</head>
</html>
