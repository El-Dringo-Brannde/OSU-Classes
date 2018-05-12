<!DOCTYPE HTML>
<html>
<head>
  <link rel="stylesheet" href="index.css">
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
    h1 {text-align: center;}
    table{
      margin-left: auto;
      margin-right: auto;
      color: black;
    }
    ul{
      color: white;
      text-align: center;
    }
    li{
      color:black;
      text-align: center;
    }

  </style>
</head>
<body>
  <?php
  function decimalHour($time){ //Turns 24 hour time into a decimal
      $hms = explode(":", $time);
      return($hms[0] + ($hms[1]/60) + ($hms[2]/3600));
  }

$PrevDate = $_POST["datepicker"];
$user = $_COOKIE["user"];

$servername = 'mysql.cs.orst.edu';
$username = 'cs340_dringb';
$password = '2885';
$dbname = 'cs340_dringb';
$connection = mysqli_connect($servername, $username, $password, $dbname);

// Finds how many deliveries the user took on the particular day
  $sql = "SELECT count(`DeliveryID`) from `Delivery` where `Date` = '$PrevDate' and `Username` = '$user'";
  $result = $connection -> query($sql);
$DeliveryCount = mysqli_fetch_row($result);
if ($DeliveryCount[0] == 0){
  echo "<h1 text-align: center;>You didn't do anything that day!</h1>";
  die();
}

echo "<h4>";
echo "<ul id = 'StatsList'>";
echo "Fun Stats for the day";
echo "</ul> </h4>";

     $connection = mysqli_connect($servername, $username, $password, $dbname);
     if (!$connection) {
       die('Could not connect: ' . mysql_error());
     }
       $user = $_COOKIE["user"];

       $query = "SELECT Location.Address, Location.Street, Location.APT, Delivery.Time,Delivery.OrderTotal,Delivery.Tip$ from Delivery, Location where Delivery.DeliveryID = Location.DeliveryID and Delivery.Username = '$user' and Delivery.Date = '$PrevDate'";

         $result = mysqli_query($connection, $query);
         if (!$result) {
           die("Query to show fields from table failed");
         }
         $fields_num = mysqli_num_fields($result);
         if ($fields_num == 0){
           echo "You didn't do anything that day silly.";
           die();
         }
         echo "<h1>Deliveries Taken by $user on $PrevDate </h1>";
         echo "<table id='t01' class= inlineTable><tr>";
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

         //Get 24 hour time of first delivery
         $sql = "SELECT min(`Time`) from `Delivery` where `Date` = '$PrevDate' and `Username` = '$user'";
         $result = $connection->query($sql);
         $fields_num = mysqli_num_fields($result);

         for ($i = 0; $i < $fields_num; ++$i) {
             $field = mysqli_fetch_field($result);
         }
         while ($row = mysqli_fetch_row($result))
             foreach ($row as $cell)
                 $StartTime = $cell;

        $StartDec = decimalHour($StartTime);
        //Get 24 hour time of last delivery
        $sql = "SELECT max(`Time`) from `Delivery` where `Date` = '$PrevDate' and `Username` = '$user'";
        $result = $connection->query($sql);
        $fields_num = mysqli_num_fields($result);

        for ($i = 0; $i < $fields_num; ++$i) {
            $field = mysqli_fetch_field($result);
        }
        while ($row = mysqli_fetch_row($result))
            foreach ($row as $cell)
                $EndTime = $cell;

        $EndDec = decimalHour($EndTime);
        $FixedHoursWorked = $EndDec - $StartDec;

        $sql = "SELECT sum(`Tip$`) from `Delivery` where `Date` = '$PrevDate' and `Username` = '$user'";
        $result = $connection->query($sql);
        $fields_num = mysqli_num_fields($result);
        for ($i = 0; $i < $fields_num; ++$i)
            $field = mysqli_fetch_field($result);
          while ($row = mysqli_fetch_row($result))
            foreach ($row as $cell)
              $TipSum = $cell;


           $sql = "SELECT mid(`Time`,1,2), `Tip$` from Delivery where `date` = '$PrevDate' and `Username` = '$user'";
           $result = $connection->query($sql);
           $fields_num = mysqli_num_fields($result);
           $EmptyArray = array();
           while ($row = mysqli_fetch_row($result)){
             $EmptyArray[] = array($row[0] => $row[1]);
           }

           $TextHoursWorked = "On $PrevDate you worked $FixedHoursWorked hours";
           echo "<script> var textnode = document.createTextNode('$TextHoursWorked');";
           echo "var NewNode = document.createElement('li');";
           echo "NewNode.appendChild(textnode);";
           echo "document.getElementById('StatsList').appendChild(NewNode); </script>";

           $TextCount = "You have taken a total of $DeliveryCount[0] deliveries too!";
           echo "<script> var textnode2 = document.createTextNode('$TextCount');";
           echo "var NewNode2 = document.createElement('li');";
           echo "NewNode2.appendChild(textnode2);";
           echo "document.getElementById('StatsList').appendChild(NewNode2); </script>";

           $TextSum = "You have made a total of \$$TipSum in tips too!";
           echo "<script> var textnode3 = document.createTextNode('$TextSum');";
           echo "var NewNode3 = document.createElement('li');";
           echo "NewNode3.appendChild(textnode3);";
           echo "document.getElementById('StatsList').appendChild(NewNode3); </script>";

           $HourAverage = $TipSum / $FixedHoursWorked;

           $TextTipsByHour = "Today you averaged \$$HourAverage in just tips per hour!";
           echo "<script> var textnode4 = document.createTextNode('$TextTipsByHour');";
           echo "var NewNode4 = document.createElement('li');";
           echo "NewNode4.appendChild(textnode4);";
           echo "document.getElementById('StatsList').appendChild(NewNode4); </script>";

           $GrossWage = $HourAverage + 9.25;
           $TextGrossWage = "Today you made roughly \$$GrossWage take home per hour!";
           echo "<script> var textnode7 = document.createTextNode('$TextGrossWage');";
           echo "var NewNode7 = document.createElement('li');";
           echo "NewNode7.appendChild(textnode7);";
           echo "document.getElementById('StatsList').appendChild(NewNode7); </script>";


           $Gross = $TipSum + ($DeliveryCount[0] * 1.5) + ($FixedHoursWorked * 9.25);
           $TextGrossWage = "Today you made a gross of \$$Gross including wages and gas reimbursement!";
           echo "<script> var textnode5 = document.createTextNode('$TextGrossWage');";
           echo "var NewNode5 = document.createElement('li');";
           echo "NewNode5.appendChild(textnode5);";
           echo "document.getElementById('StatsList').appendChild(NewNode5); </script>";

           $DayAverage = $TipSum / $DeliveryCount[0];

           $AvgTip = "Today you each delivery you took was about \$$DayAverage in tips just for you!";
           echo "<script> var textnode6 = document.createTextNode('$AvgTip');";
           echo "var NewNode6 = document.createElement('li');";
           echo "NewNode6.appendChild(textnode6);";
           echo "document.getElementById('StatsList').appendChild(NewNode6); </script>";

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


</body>
</html>
