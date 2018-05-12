<?php
  if (isset($_COOKIE['user'])){
    require_once 'GetWallpaper.php';
    require_once 'NavBar.php';
    require_once 'connectvarsEECS.php';
  }
  else {
    echo '<script> window.location.href = "login.html";</script>';
  }
  $user = $_COOKIE['user'];
  $connection = mysqli_connect(servername, username, password, dbname);
  if (!$connection) {
    die('Could not connect: ' . mysql_error());
  }

  $sql = "SELECT `Password` FROM `ProjectUsers` where Username = '$user'";
  $result = mysqli_query($connection,$sql);
  $row = mysqli_fetch_row($result);

  if ($_POST['OldPass'] != $row[0]){
    echo "Incorrect Old Password entered!";
    echo "<a href = ChangePass.php> Click here to try again </a>";
    die();
  }

  if ($_POST["NewPass"] != $_POST["ConfirmPass"]){
    echo "Passwords do not match! <br>";
    echo "<a href = ChangePass.php> Click here to try again </a>";
    die();
  }

  $NewPassword = $_POST["NewPass"];
  $sql = "UPDATE `ProjectUsers` SET `Password` = '$NewPassword' WHERE `ProjectUsers`.`Username` = '$user'";
  mysqli_query($connection,$sql);
  echo "Password has been changed!!";

?>
