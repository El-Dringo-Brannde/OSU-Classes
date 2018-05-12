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

</head>
<body>
  <h1>Change your password! </h1>
  <form action = "AlterPassDB.php" method = "post">
      Old Password<input type = "text" name = "OldPass" /><br />
      New Password <input type="text" name = "NewPass" /><br />
      Confirm Password <input type="text" name = "ConfirmPass" /><br /><br />
      <input type = "submit" />
  </form>
</body>
</html>
