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
  <img src ="http://i.imgur.com/WPEwR9C.jpg?4" width = "200px" height = "200px" />
  <h1><?php echo $_COOKIE['user']?></h1>
  <style>
  img{
    border-radius: 50%;
    display: block;
    margin: 0 auto;
  }
  h1,div,li{
    text-align: center;
    margin-left: auto;
    margin-right: auto;
    margin: 0 auto;
  }
  body {
    color: white;
  }
  button{
    color: black;
  }
  </style>
</head>
<body>
  <div><br />
  <script>
    function ChangePage(){
      window.location.href = "ChangePass.php";
    }
  </script>
  <button onclick="ChangePage()"> Edit Password</button><br /><br />
  </div>
  <h1>Overall history </h1>
  <?php
    require_once 'connectvarsEECS.php';
    $user = $_COOKIE['user'];
    $connection = mysqli_connect(servername, username, password, dbname);
    if (!$connection) {
      die('Could not connect: ' . mysql_error());
    }
    $sql = "SELECT COUNT(DeliveryID) FROM `Delivery` where Username = '$user'";
    $result = $connection->query($sql);
    $TotalDeiveriesTaken = mysqli_fetch_row($result);

    $sql = "SELECT Sum(`Tip$`) FROM `Delivery` where Username = '$user'";
    $result = $connection->query($sql);
    $TotalTipsMade = mysqli_fetch_row($result);

    echo "<li>Overall you have taken a Total of $TotalDeiveriesTaken[0] Deliveries </li>";
    echo "<li>
    And you have made a total of \$$TotalTipsMade[0] in just tips!
    </li>";

  ?>

</body>
</html>
