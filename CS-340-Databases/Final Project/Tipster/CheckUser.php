<?php
    $user = $_POST["Username"];
    $pass = $_POST["Password"];
    $servername = 'mysql.cs.orst.edu';
    $username = 'cs340_dringb';
    $password = '2885';
    $dbname = 'cs340_dringb';
    $connection = new mysqli($servername, $username, $password, $dbname);

    if (!$connection) {
         die("Connection failed: " . mysqli_connect_error());
     }
     else{
        $sql = "SELECT * FROM ProjectUsers";
        if($result = mysqli_query($connection, $sql)) {
          while ($row = mysqli_fetch_row($result)){
             if ($user == $row[0] && $pass == $row[1]){
                $founduser = 1;
             }
           }
        if ($founduser != 1){
              echo "Username / Password Not found please try again <br> ";
              echo "<a href = login.html>Click here to try again </a>";
          die();
        }
        else{
          $value = setcookie("user",$user, time()+43200, "/");
          echo '<script> window.location.href = "homepage.php";</script>';
        }
      }
    }
?>
<!DOCTYPE HTML>
<html>
<head>
</head>
</html>
