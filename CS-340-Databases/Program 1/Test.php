<!DOCTYPE html>
<html>
<body>
<?php
$servername = "mysql.cs.orst.edu";
$username = "CS_340_dringb";
$pass = "2885";

$conn = mysqli_connect($servername, $username, $pass);

if ($conn ->connect_error){
  die ("Connection Failed" . $conn -> connect_error);
}
    echo "Success";
?>


</body>
</html>
