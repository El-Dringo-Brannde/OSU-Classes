<?php
  if (isset($_COOKIE['user'])){
    require_once 'GetWallpaper.php';
    require_once 'NavBar.php';
  }
  else {
    echo '<script> window.location.href = "login.html";</script>';
  }
?>

<html>
<head>
  <link rel="stylesheet" href="index.css">
</head>
<body>
  <?php
    $DeliveryID = $_POST["DeliveryID"];
    $Address = $_POST["Address"];
    if ($Address == NULL){
      echo "The Address wasn't supplied!";
      $Address = $_POST["PrevAddress"];
      echo "The new address is $Address";
      echo "<br />";
    }
    $Street = $_POST["Street"];
    if ($Street == NULL){
      echo "Street not supplied!";
      $Street = $_POST["PrevStreet"];
      echo "New street is $Street <br />";
    }
    $Apt = $_POST["Apt"];
    if ($Apt == NULL){
      echo "Apt not supplied!";
      $Apt = $_POST["PrevApt"];
      echo "New Apt# is $Apt <br />";
    }
    echo "The Apt # is $Apt";
    $OrderTotal = $_POST["OrderTotal"];
    if ($OrderTotal == NULL){
      echo "Total not supplied!";
      $OrderTotal = $_POST["PrevOrderTotal"];
      echo "New Total is $OrderTotal <br />";
    }
    $Tip = $_POST["Tip$"];
    if ($Tip == NULL){
      echo "Tip not supplied!";
      $Tip = $_POST["PrevTip$"];
      echo "New Tip is $Tip <br />";
    }
    require_once 'connectvarsEECS.php';
    $connection = mysqli_connect(servername, username, password, dbname);
    if (!$connection) {
      die('Could not connect: ' . mysql_error());
    }
    $user = $_COOKIE['user'];

    $sql = "UPDATE Delivery Set OrderTotal = $OrderTotal,`Tip$` = $Tip where DeliveryID = $DeliveryID";
    $connection->query($sql);
    $sql = "UPDATE Location Set Address = '$Address', Street = '$Street', APT = '$Apt' where DeliveryID = $DeliveryID";
    $connection->query($sql);


    echo "<h1>The new value for the Entry is</h1>";
    $sql = "SELECT * from Delivery, Location Where Delivery.DeliveryID = $DeliveryID and Delivery.DeliveryID = Location.DeliveryID";
    $result = mysqli_query($connection, $sql);
    if (!$result) {
      die("Query to show fields from table failed");
    }
    $fields_num = mysqli_num_fields($result);
    echo "<h1>Deliveries Taken by $user </h1>";
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
</body>
</html>
