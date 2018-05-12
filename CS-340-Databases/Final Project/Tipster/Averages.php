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

 <?php
    $servername = 'mysql.cs.orst.edu';
    $username = 'cs340_dringb';
    $password = '2885';
    $dbname = 'cs340_dringb';

    $connection = mysqli_connect($servername, $username, $password, $dbname);
    if(!$connection)
      die("connection to SQL server failed!");

    $user = $_COOKIE['user'];
    $sql = "SELECT avg(Shift.Hours) From Shift where Username = '$user'";
    $result = $connection -> query($sql);
    $TotalHrAvg = mysqli_fetch_row($result);
    $shortenedTotalHrAvg = substr($TotalHrAvg[0],0,5);

    $sql = "SELECT Avg(HourAvg) FROM `Averages` where User = '$user'";
    $result = $connection -> query($sql);
    $TotalHourlyTipAvg = mysqli_fetch_row($result);
    $shortenedHourlyTipAvg = substr($TotalHourlyTipAvg[0],0,5);

    $sql = "SELECT Avg(DayAvg) from `Averages` where User = '$user'";
    $result = $connection -> query($sql);
    $TotalDailyTipAvg = mysqli_fetch_row($result);
    $shortenedDailyTipAvg = substr($TotalDailyTipAvg[0],0,5);

    $TotalTipMadePerDay = $TotalHrAvg[0] * $TotalHourlyTipAvg[0];
    $shortTotalTipPerDay = substr($TotalTipMadePerDay,0,5);

    $GrossWagePerDay = $shortTotalTipPerDay + ($shortenedTotalHrAvg * 9.25);
    $GrossWagePerHour = $shortenedHourlyTipAvg + 9.25;

    echo "<h1>Overall Average stats</h1>";
    echo "<ul>";
    echo "<li><h4>Each hour you make roughly <strong>\$$shortenedHourlyTipAvg</strong> in just tips</h4></li>";
    echo "<li><h4>Each shift you typically work around <strong>$shortenedTotalHrAvg</strong> hours from your first delivery</h4></li>";
    echo "<li><h4>Every delivery you take you get roughly <strong>\$$shortenedDailyTipAvg</strong> for a tip</h4></li>";
    echo "<li><h4>Each day you make roughly <strong>\$$shortTotalTipPerDay</strong> in just tips</h4></li>";
    echo "<li><h4>So Each day you typically make a gross of <strong>\$$GrossWagePerDay</strong> per day before the government takes some!</h4></li>";
    echo "<li>
    <h4>Every hour you make roughly <strong>\$$GrossWagePerHour</strong> take home!</h4>
    </li>";
    echo "</ul>";

    $sqlforchart = "SELECT Date,HourAvg  FROM `Averages` where User = '$user'";
    $resultforchart = $connection->query($sqlforchart);
    $fields_num = mysqli_num_fields($resultforchart);
    $EmptyArray = array();
    while ($row = mysqli_fetch_row($resultforchart)){
      $EmptyArray[] = array($row[0] => $row[1]);
    }
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
         title: 'Date'
       },
       vAxis: {
         title: 'Hourly Tip Average'
       }
     };
 var chart = new google.visualization.LineChart(document.getElementById("columnchart"));
 chart.draw(data, options);
 }
 </script>
 <div id="columnchart" style="margin-left: auto; margin-right: auto"></div>


 <style>
 strong{
   color: black;
 }
  h4,h1{
    text-align: center;
  }
    body,ul{
      text-align: center;
      color: white;
    }
 </style>
</head>
</html>
