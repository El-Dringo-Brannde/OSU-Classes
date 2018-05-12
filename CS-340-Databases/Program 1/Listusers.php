<!DOCTYPE html>
<html>
<head>
  <title>MySQL Table Viewer</title>
  <link rel="stylesheet" href="index.css">
</head>
<body>

<?php
  $servername = 'mysql.cs.orst.edu';
  $username = 'cs340_dringb';
  $password = '2885';
  $dbname = 'cs340_dringb';

  $connect = mysqli_connect($servername, $username, $password, $dbname);
  if (!$connect){
    echo "ERROR";
  }
  else {
    $query = "SELECT username, firstname, email FROM users";

    $request = mysqli_query($connect, $query);
    if (!$request){
      echo "Can't access DB! <br>";
      die();
    }
    else
      //Borrowed kindfully from ShowTable.php (given to us)
      //Why reinvent the wheel?

      $fields_num = mysqli_num_fields($request);
      echo "<h1>Table: users</h1>";
      echo "<table id='t01'><tr>";

      // printing table headers
      for($i=0; $i<$fields_num; $i++) {
        $field = mysqli_fetch_field($request);
        echo "<td><b>{$field->name}</b></td>";
      }
      echo "</tr>\n";
      while($row = mysqli_fetch_row($request)) {
        echo "<tr>";

        // $row is array... foreach( .. ) puts every element
        // of $row to $cell variable
        foreach($row as $cell)
          echo "<td>$cell</td>";
        echo "</tr>\n";
      }
  }
?>

</body>
</html>
