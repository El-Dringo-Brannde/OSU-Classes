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
<style>
	form {
		font-family: monospace;
		text-align: center;
		margin-top: auto;
		margin-bottom: auto;
	}
  h1 {
    text-align: center;
  }
</style>


</head>
<body>
  <h1>Choose the date to look up</h1>
  <form action ='gotoDate.php' method = 'POST'>
  Date: <input type = 'text' name  ='datepicker' placeholder="mm/dd/yyyy">
   <br />
   <input type = 'submit' />
 </form>

</body>
</html>
