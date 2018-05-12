<!DOCTYPE HTML>
<html>
<head>
    <link rel="stylesheet" href="index.css">
    <style>
    h1{
      text-align: center;
    }
    table{
      margin-left: auto;
      margin-right: auto;
    }
    #StatsList{
      text-align: center;
    }
    li{
      color: white;
    }

    </style>
</head>
<body>
  <?php
    if (isset($_COOKIE['user'])){
      require_once 'GetWallpaper.php';
      require_once 'NavBar.php';
    }
    else {
      echo '<script> window.location.href = "login.html";</script>';
    }
  ?>


<?php
$servername = 'mysql.cs.orst.edu';
$username = 'cs340_dringb';
$password = '2885';
$dbname = 'cs340_dringb';
echo "<h4>";
echo "<ul id = 'StatsList'>";
echo "Fun Random Stats for the day";
echo "</ul> </h4>";

function decimalHour($time){ //Turns 24 hour time into a decimal
    $hms = explode(":", $time);
    return($hms[0] + ($hms[1]/60) + ($hms[2]/3600));
}

// TURN ALL THESE DAMN FOR LOOPS INTO A FUNCTION!!!
$connection = mysqli_connect($servername, $username, $password, $dbname);
if (!$connection) {
  die('Could not connect: ' . mysql_error());
}
  $user = $_COOKIE["user"];
  $today = date('m/d/Y',time());

  if (!$connection) {
      die('Connection failed: '.mysqli_connect_error());
  } else {
    $sql = "SELECT min(`Time`) from `Delivery` where `Date` = '$today' and `Username` = '$user'";
    $result = $connection->query($sql);
    $fields_num = mysqli_num_fields($result);

    for ($i = 0; $i < $fields_num; ++$i) {
        $field = mysqli_fetch_field($result);
    }
    while ($row = mysqli_fetch_row($result)) {
        foreach ($row as $cell) {
            $StartTime = $cell;
            $CurHr = date("H:i:s");
            $TotalHr = $CurHr - $StartTime;
        }
    }
}

$Start = decimalHour($StartTime);
if ($Start == 0){
  echo "<h1>You have no deliveries today Dummy!</h1>";
  die();
  exit();
}

  $CurrentTime = decimalHour($CurHr);
  $Difference = $CurrentTime - $Start; //finds how many hours are worked
  $HoursWorked = "You have worked for $Difference hours today!";
  echo "<script> var textnode = document.createTextNode('$HoursWorked');";
  echo "var NewNode = document.createElement('li');";
  echo "NewNode.appendChild(textnode);";
  echo "document.getElementById('StatsList').appendChild(NewNode); </script>";


  if (!$connection) {
      die('Connection failed: '.mysqli_connect_error());
  } else {
    // Finds how many deliveries the user took on the particular day
    $sql = "SELECT count(`DeliveryID`) from `Delivery` where `Date` = '$today' and `Username` = '$user'";
    $result = $connection->query($sql);
    $fields_num = mysqli_num_fields($result);

    for ($i = 0; $i < $fields_num; ++$i) {
        $field = mysqli_fetch_field($result);
    }
    while ($row = mysqli_fetch_row($result)) {
        foreach ($row as $cell) {
            $count = $cell;
        }
    }
}
$DelivCount = "You have taken a total of $count deliveries too!";
echo "<script> var textnode2 = document.createTextNode('$DelivCount');";
echo "var NewNode2 = document.createElement('li');";
echo "NewNode2.appendChild(textnode2);";
echo "document.getElementById('StatsList').appendChild(NewNode2); </script>";

if (!$connection) {
    die('Connection failed: '.mysqli_connect_error());
} else {
  $sql = "SELECT sum(`Tip$`) from `Delivery` where `Date` = '$today' and `Username` = '$user'";
  $result = $connection->query($sql);
  $fields_num = mysqli_num_fields($result);

  for ($i = 0; $i < $fields_num; ++$i) {
      $field = mysqli_fetch_field($result);
  }
  while ($row = mysqli_fetch_row($result)) {
      foreach ($row as $cell) {
          $Sum = $cell;
      }
  }
}
$TipSum = "You have made a total of \$$Sum in tips too!";
echo "<script> var textnode3 = document.createTextNode('$TipSum');";
echo "var NewNode3 = document.createElement('li');";
echo "NewNode3.appendChild(textnode3);";
echo "document.getElementById('StatsList').appendChild(NewNode3); </script>";

  $HourAverage = $Sum / $Difference;

  $TipsByHour = "Today you averaged \$$HourAverage per hour!";
  echo "<script> var textnode4 = document.createTextNode('$TipsByHour');";
  echo "var NewNode4 = document.createElement('li');";
  echo "NewNode4.appendChild(textnode4);";
  echo "document.getElementById('StatsList').appendChild(NewNode4); </script>";

  $Gross = $Sum + ($count * 1.5) + ($Difference * 9.25);
  $GrossWage = "Today you made a gross of \$$Gross including wages and gas reimbursement!";
  echo "<script> var textnode5 = document.createTextNode('$GrossWage');";
  echo "var NewNode5 = document.createElement('li');";
  echo "NewNode5.appendChild(textnode5);";
  echo "document.getElementById('StatsList').appendChild(NewNode5); </script>";

  $DayAverage = $Sum / $count;

  $AvgTip = "Today you each delivery you took was about \$$DayAverage in tips just for you!";
  echo "<script> var textnode6 = document.createTextNode('$AvgTip');";
  echo "var NewNode6 = document.createElement('li');";
  echo "NewNode6.appendChild(textnode6);";
  echo "document.getElementById('StatsList').appendChild(NewNode6); </script>";



    //inserts into shift, with 0 hours originally, or if the user has worked previously today, updates it with the difference of the first delivery and current time.
  	$HrWorked = "INSERT INTO Shift (`Date`, `Username`, `Hours`,`TipSum`,`DeliveryCount`) VALUES('$today', '$user', 0,$Sum,$count) ON DUPLICATE Key UPDATE `Date` = '$today', `Username`= '$user', Hours=$Difference,TipSum = $Sum,DeliveryCount = $count";
  	$connection->query($HrWorked);

  //Insert the New averages, if the user has already checked this page update with new averages
  $Averages = "INSERT INTO Averages (`HourAvg`, `DayAvg`,`User`, `Date`) VALUES('$HourAverage', '$DayAverage', '$user','$today') ON DUPLICATE Key UPDATE `Date` = '$today', `User`= '$user', `HourAvg` = $HourAverage, `DayAvg` = $DayAverage";
	$connection->query($Averages);

  //Selects the hours and corresponding tips with that hour
  $sqlforchart = "SELECT mid(`Time`,1,2), `Tip$` from Delivery where `date` = '$today' and `Username` = '$user'";
  $resultforchart = $connection->query($sqlforchart);
  $fields_num = mysqli_num_fields($resultforchart);
  $EmptyArray = array();
  while ($row = mysqli_fetch_row($resultforchart)){
    $EmptyArray[] = array($row[0] => $row[1]);
  }
  //Sums up multiple deliveries within the same hour so in the new array each hour is an associative array key to the sum of deliveries for that hour.
  $sumArray = array();
  foreach ($EmptyArray as $k=>$subArray) {
    foreach ($subArray as $id=>$value) {
      $sumArray[$id]+=$value;
    }
  }
?>
<script type="text/javascript" src="https://www.google.com/jsapi"></script>
<script type="text/javascript">
google.load("visualization", "1", {packages:["corechart"]});
google.setOnLoadCallback(drawChart);
function drawChart() {
var data = google.visualization.arrayToDataTable([
['Hour', 'Tip$'],
 <?php
   foreach($sumArray as $key => $value)
     echo "['".$key."',".$value."],";
 ?>

]);

var options =
    {
      hAxis: {
        title: 'Hour(Military Time)'
      },
      vAxis: {
        title: 'Tip Money'
      }
    };
var chart = new google.visualization.LineChart(document.getElementById("columnchart"));
chart.draw(data, options);
}
</script>
<div id="columnchart" style="margin-left: auto; margin-right: auto"></div>

<?php

    $query = "SELECT Location.Address, Location.Street, Location.APT, Delivery.Time,Delivery.OrderTotal,Delivery.Tip$ from Delivery, Location where Delivery.DeliveryID = Location.DeliveryID and Delivery.Username = '$user' and Delivery.Date = '$today'";

    	$result = mysqli_query($connection, $query);
    	if (!$result) {
    		die("Query to show fields from table failed");
    	}
      $fields_num = mysqli_num_fields($result);
      echo "<h1>Deliveries Taken by $user </h1>";
      echo "<table id='t01'><tr>";
      // printing table headers
      for($i=0; $i<$fields_num; $i++) {
        $field = mysqli_fetch_field($result);
        echo "<td><b>{$field->name}</b></td>";
      }
      echo "</tr>\n";
      while($row = mysqli_fetch_row($result)) {
        echo "<tr>";
        // $row is array... foreach( .. ) puts every element
        // of $row to $cell variable
        foreach($row as $cell)
          echo "<td>$cell</td>";
        echo "</tr>\n";
      }

  	mysqli_free_result($result);
  	mysqli_close($connection);
?>
</body>
</html>
