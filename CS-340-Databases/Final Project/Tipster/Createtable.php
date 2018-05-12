<!DOCTYPE html>
<html>
<body>

<?php
  $servername = 'mysql.cs.orst.edu';
  $username = 'cs340_dringb';
  $password = '2885';
  $dbname = 'cs340_dringb';

  $connect = mysqli_connect($servername, $username, $password, $dbname);
  if (!$connect){
    die('Failed to connect!' . mysqli_connect_error());
  }
  else{
    $sql = "CREATE TABLE ProjectUsers(
      Username VARCHAR(20) PRIMARY KEY,
      firstname VARCHAR(20) NOT NULL,
      lastname VARCHAR(20) NOT NULL,
      email VARCHAR(40) NOT NULL,
      password VARCHAR(20) NOT NULL,
      age INT(6)
    )";

    if (mysqli_query($connect, $sql)){
      echo "Table created successfully!";
    }
    else {
      echo "ERROR" .mysqli_error($connect);
    }
    mysqli_close($connect);
  }
?>


</body>
</html>
