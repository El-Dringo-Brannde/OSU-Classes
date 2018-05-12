<!DOCTYPE HTML>
<html>
<head>
  <?php
    if (isset($_COOKIE['user'])){
      require_once 'GetWallpaper.php';
      require_once 'NavBar.php';
    }
    else {
      echo '<script> window.location.href = "login.html";</script>';
    }
  ?>
</head>
<body>
<?php
  echo "<h1>Enter the address for the delivery </h1> <br />";
  echo "<form action = 'Querydb.php' method = 'POST'>";
    echo "Address: <input type = 'number' name = 'address' /> <br />";
    echo "Street: <input type = 'text' name = 'street' /> <br  />";
    echo "Apartment: <input type = 'text' name = 'apt' /> <br /> ";
    echo "<input type = 'submit' /> <br /> ";
  echo "</form> <br /> <br /> <br /> ";
?>
<style>
  h1{text-align: center;}
  form {
    text-align: center;
    font-family: monospace;
  }
 </style>
</body>
</html>
