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
  				setcookie("user",$user, time()+43200, "/", "", 0);
  				$founduser = 1;
             }
           }
    		if ($founduser != 1){
              echo "Username / Password Not found please try again <br> ";
              echo "<a href = login.html>Click here to try again </a>";
    		  die();
    		}
      }
    }
?>

<!DOCTYPE HTML>
<html>
<head>
  <?php
   require_once 'Mobile_Detect.php';
    $detect = new Mobile_Detect;
   if ($detect ->isMobile()){
     echo "<style>";
     echo "body{";
        echo "background-image: url(\"http://i.imgur.com/qTYKHsp.jpg\");";
        echo "background-size: cover;";
        echo "background-repeat: no-repeat;";
        echo "color: #FF8C00;}";
     echo "</style>";
      echo "<meta name= \"viewport\" content= \"width=device-width, initial-scale=1, maximum-scale=1 \"/>";
      echo "<meta name= \"HandheldFriendly\" content= \"true \" />";
      echo "<meta name=\"MobileOptimized\" content=\"320 \" />";
  }
  else {
    echo "<style>";
    echo "body{";
    echo "background-image: url(\"http://i.imgur.com/OoLriho.jpg\");";
    echo "background-size: cover;";
    echo "background-repeat: no-repeat;";
    echo "color: #FF8C00;}";
    echo "</style>";
  }

    ?>
<script>
	function gotodeliv(){
		var url = "http://web.engr.oregonstate.edu/~dringb/CS340_Project/Delivery.php";
		location.href = url;
	}
	function gotoEOD(){
		var url = "http://web.engr.oregonstate.edu/~dringb/CS340_Project/EOD.php";
		location.href = url;
	}
</script>
</head>

<body>
<?php
    $user = $_COOKIE["user"];
	echo "<div> <h1>Hello! " . $_COOKIE["user"] . "</h1>". "</div>";
	echo "<br> <br>";
	echo "<div> <button onClick='gotodeliv()'> Deliveries </button> </div> ";
	echo "<br> <br> <br>";
	echo "<div> <button onClick = 'gotoEOD()'> End of Day </button> </div>";

?>
<style>
	form {
		width: 50%;
		height: 50%;
	}
	div {
		font-family: monospace;
		text-align: center;
	}
	button {
    border-radius: 25px;
    background-color: grey;
		height: 100px;
		width: 100px;
		margin: 0 auto;
	}
</style>
</body>
</html>
