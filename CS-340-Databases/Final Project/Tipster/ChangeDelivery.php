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
<html>
<head>
  <link rel="stylesheet" href="index.css">
  <style>
    h1,form,table{
      text-align: center;
      margin-left: auto;
      margin-right: auto;
    }
  </style>
</head>
<body>
  <?php
    $DeliveryIDNumber = substr($_POST["Edit"],6,12);
    $user = $_COOKIE['user'];
    $connection = mysqli_connect(servername, username, password, dbname);
    if (!$connection) {
      die('Could not connect: ' . mysql_error());
    }

      $sql = "SELECT
        Location.Address,Location.Street,Location.APT,Delivery.OrderTotal,Delivery.`Tip$`,Delivery.Time,Delivery.Date FROM `Delivery`, Location where Delivery.DeliveryID = $DeliveryIDNumber and Delivery.DeliveryID = Location.DeliveryID";
      $result = mysqli_query($connection,$sql);
      $fields_num = mysqli_num_fields($result);
      echo "<table id='t01'><tr>";
      // printing table headers
      echo "<h1>Delivery to change!</h1>";
      for($i=0; $i<$fields_num; $i++) {
        $field = mysqli_fetch_field($result);
        echo "<td><b>{$field->name}</b></td>";
      }
      echo "</tr>\n";
      while($row = mysqli_fetch_row($result)) {
        echo "<tr>";
        foreach($row as $cell)
          echo "<td>$cell</td>";
        echo "</tr>\n";
      }
      echo "</table><br />";


      $sql = "SELECT
      Location.Address,Location.Street,Location.APT, Delivery.OrderTotal,Delivery.`Tip$`,Delivery.Time FROM `Delivery`, Location where Delivery.DeliveryID = $DeliveryIDNumber and Delivery.DeliveryID = Location.DeliveryID";
      $result = mysqli_query($connection,$sql);
      $ValByRow = mysqli_fetch_row($result);
      echo $ValByRow[0];
      echo $ValByRow[1];
      echo $ValByRow[2];
      echo $ValByRow[3];
      echo $ValByRow[4];

  ?>


<form action="ActuallyEdit.php" method="post">
  <input type = "hidden" name ="DeliveryID" value = <?php echo "\"$DeliveryIDNumber\"";?> />

  Address: <input type = "number" name="Address" /><br />
  <input type = "hidden" name = "PrevAddress" value = <?php echo "\"$ValByRow[0]\""?>/>

  Street: <input type ="text" name = "Street" /><br />
  <input type = "hidden" name = "PrevStreet" value = <?php echo "\"$ValByRow[1]\"";?> />


  Apt #: <input type = "text" name = "Apt" /><br />
  <input type = "hidden" name = "PrevApt" value = <?php echo "\"$ValByRow[2]\""?> />

  OrderTotal: <input type="number" name = "OrderTotal" /><br />
  <input type = "hidden" name = "PrevOrderTotal" value = <?php echo "\"$ValByRow[3]\""?> />

  Tip$: <input type = "number" name = "Tip$" /><br /><br />
  <input type = "hidden" name = "PrevTip$" value = <?php echo "\"$ValByRow[4]\""?> />
  <input type = "submit" />

</form>

</body>
</html>
