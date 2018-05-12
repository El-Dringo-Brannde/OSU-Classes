<!DOCTYPE html>
<html>
<body>
<?php
    if (strlen($_POST["Username"]) == 0 ){
      echo "ENTER A USERNAME DUMMY!";
      echo "<a href = Signup.html> Click here to try again </a>";
      die();
    }
    else if (strlen($_POST["Password"]) == 0){
      echo "Don't make me hit you.";
      echo "<a href = Signup.html> Click here to try again </a>";
      die();
    }
    else if ($_POST["Password"] != $_POST["confirm"]){
      echo "Passwords do not match! <br>";
      echo "<a href = Signup.html> Click here to try again </a>";
      die();
    }

    $servername = 'mysql.cs.orst.edu';
    $username = 'cs340_dringb';
    $password = '2885';
    $dbname = 'cs340_dringb';
    $connection = new mysqli($servername, $username, $password, $dbname);

   if (!$connection) {
        die("Connection failed: " . mysqli_connect_error());
    }
    else{
      $sql = "SELECT Username FROM `ProjectUsers`";
      $result = $connection->query($sql);
      $fields_num = mysqli_num_fields($result);

      for ($i = 0; $i < $fields_num; ++$i) {
          $field = mysqli_fetch_field($result);
      }
      while ($row = mysqli_fetch_row($result)) {
          foreach ($row as $cell) {
            if ($_POST["Username"] == $cell){
              echo "I'm sorry, that username has already been taken";
              echo "<br />";
              echo "<a href = \"./Signup.html\">Please try again</a>";
              die();

            }
          }
      }

		$stmt = $connection->prepare("INSERT INTO ProjectUsers (`Username`, `Password`, `Store Location`)
		VALUES (?,?,?)");

		$stmt -> bind_param("sss", $user, $pass,$store);

		$user = $_POST["Username"];
		$pass = $_POST["Password"];
		$store = $_POST["store"];
		$stmt->execute();

		$stmt -> close();
		$connection -> close();
		echo '<script>window.location.href = "login.html";</script>';

    }
?>

</body>
</html>
