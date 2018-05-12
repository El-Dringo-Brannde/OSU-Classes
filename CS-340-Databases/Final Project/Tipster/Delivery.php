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
    $user = $_COOKIE['user'];

    $date = date('m/d/Y H:i:s', time());
    $datearr = str_split($date);
    $dumbdate = [];
    for ($i = 0; $i < 10; ++$i) {
        $dumb[] = $datearr[$i];
    }
    $dumbtime = [];
    for ($i = 11; $i < 22; ++$i) {
        $dumbtime[] = $datearr[$i];
    }
    $today = implode('', $dumb);
    $time = implode('', $dumbtime);
    echo '<br> <br> <br>';

  echo "<form action = 'adddata.php' method = 'POST'>";

    echo '<h1> Enter your delivery data </h1>';
    echo "Address: <input type = 'number' name = 'address'> <br> ";
    echo "Street: <input type = 'text' name = 'street'> <br>";
    echo "Apartment:<input type = 'text' name = 'apt'> <br>";
    echo "Total: <input type = 'number' step = '0.01' name = 'total'> <br>";
    echo "Tip: <input type = 'number' step = '0.01' name = 'tip'> <br>";
    echo "<input type = 'hidden' name = 'username' value = '{$user}'>";
    echo "<input type = 'hidden' name = 'date' value = '{$today}'>";
    echo "<input type = 'hidden' name ='time' value = '{$time}'><br /><br />";

    echo "<input type = 'submit'> <br>";

  echo '</form> <br> <br> <br>';
  echo '<script>';
      echo 'function getLocation() {';
          echo 'if (navigator.geolocation) {';
              echo 'navigator.geolocation.getCurrentPosition(showPosition);';
          echo '}}';

      echo 'function showPosition(position) {';
        echo  ' latitude = position.coords.latitude;';
          echo 'longitude = position.coords.longitude;';
          echo "var url = 'https://maps.googleapis.com/maps/api/geocode/json?latlng=' + latitude + ',' + longitude + '&key=AIzaSyBkimdhfvcKYEzYRWDY_gfEvA2Gl_PGZcg';";
          echo 'var xhr = new XMLHttpRequest();';
          echo 'xhr.open("GET", url, false);';
          echo 'xhr.send();';
          echo 'var reply = JSON.parse(xhr.responseText);';
          echo "var Street_Address = reply.results[0].formatted_address.split(',');";
          echo 'console.log(Street_Address);';
          echo "Street_Address = Street_Address[0].substr(Street_Address[0].indexOf(' ')+1);";
          echo "var address = reply.results[0].formatted_address.split(' ')[0];";
          echo "document.getElementsByName('address')[0].value = address;";
          echo "document.getElementsByName('street')[0].value = Street_Address;";
      echo '}';
      echo 'window.onload = getLocation';

  echo '</script>';

    $servername = 'mysql.cs.orst.edu';
    $username = 'cs340_dringb';
    $password = '2885';
    $dbname = 'cs340_dringb';

    $connection = new mysqli($servername, $username, $password, $dbname);

 if (!$connection) {
     die('Connection failed: '.mysqli_connect_error());
 } else {
     $user = $_COOKIE['user'];
     $sql = "SELECT Location.Address, Location.Street, Location.APT, Delivery.Date,Delivery.Time,Delivery.OrderTotal,Delivery.`Tip$` FROM Location JOIN Delivery on Location.DeliveryID = (SELECT MAX(Location.DeliveryID)) AND Delivery.DeliveryID = Location.DeliveryID AND Delivery.Username = '$user' ORDER BY Location.DeliveryID DESC LIMIT 1";
     $result = $connection->query($sql);
 }
    echo '<div> Latest Delivery <br>';
    $fields_num = mysqli_num_fields($result);

    for ($i = 0; $i < $fields_num; ++$i) {
        $field = mysqli_fetch_field($result);
        echo "<b> {$field->name} </b>";
    }
    echo '<br>';
    while ($row = mysqli_fetch_row($result)) {
        echo '<tr>';
        foreach ($row as $cell) {
            echo "<td>|$cell| </td>";
        }
        echo "</tr>\n";
    }
        echo'</div>';
 ?>
 <style>
 	div {text-align: center;}
  #banner {background-color: white;}

	form {
		text-align: center;
		font-family: monospace;
	}
</style>
</body>

</html>
