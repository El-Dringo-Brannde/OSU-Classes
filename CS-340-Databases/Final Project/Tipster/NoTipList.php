<html>
<head>
  <link rel="stylesheet" href="index.css">

  <?php
  require_once 'NavBar.php';
  require_once 'GetWallpaper.php';

?>
</head>
<body>
  <?php
  $servername = 'mysql.cs.orst.edu';
  $username = 'cs340_dringb';
  $password = '2885';
  $dbname = 'cs340_dringb';

  $connection = mysqli_connect($servername, $username, $password, $dbname);
  if (!$connection) {
    die('Could not connect: ' . mysql_error());
  }

  $sql = "SELECT Location.Address,Location.Street,Location.APT,Delivery.OrderTotal,Delivery.`Tip$` FROM `Delivery`, Location where `Tip$` = 0 and Delivery.DeliveryID = Location.DeliveryID order by Location.Street";
  $result = mysqli_query($connection,$sql);
  echo "<h1>DANGER, THEY STIFF!</h1>";
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
   <style>
    h1{
      text-align: center;
    }
    table{
      text-align: center;
      margin-left: auto;
      margin-right: auto;
    }
   </style>
</body>
</html>
