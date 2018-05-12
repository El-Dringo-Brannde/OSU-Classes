<html>
<head>

  <?php
     require_once 'connectvarsEECS.php';
     $connection = mysqli_connect(servername, username, password, dbname);
     if (!$connection) {
         die('connection to SQL server failed!');
     }

     $sql = "SELECT avg(Shift.Hours) From Shift where Username = 'admin'";
     $result = $connection->query($sql);
     $TotalHrAvg = mysqli_fetch_row($result);
     $shortenedTotalHrAvg = substr($TotalHrAvg[0], 0, 5);

     $sql = "SELECT Avg(HourAvg) FROM `Averages` where User = 'admin'";
     $result = $connection->query($sql);
     $TotalHourlyTipAvg = mysqli_fetch_row($result);
     $shortenedHourlyTipAvg = substr($TotalHourlyTipAvg[0], 0, 5);

     $sql = "SELECT Avg(DayAvg) from `Averages` where User = 'admin'";
     $result = $connection->query($sql);
     $TotalDailyTipAvg = mysqli_fetch_row($result);
     $shortenedDailyTipAvg = substr($TotalDailyTipAvg[0], 0, 5);



     $sql = "SELECT count(`DeliveryID`) from `Delivery`";
     $result = $connection->query($sql);
   $DeliveryCount = mysqli_fetch_row($result);
   echo $DeliveryCount[0];





     $TotalTipMadePerDay = $TotalHrAvg[0] * $TotalHourlyTipAvg[0];
     $shortTotalTipPerDay = substr($TotalTipMadePerDay, 0, 5);

     $GrossWagePerDay = $shortTotalTipPerDay + ($shortenedTotalHrAvg * 9.25);
     $GrossWagePerHour = $shortenedHourlyTipAvg + 9.25;

     echo '<h1>Overall Average stats</h1>';
     echo '<ul>';
     echo "<li><h4>Each hour you make roughly <strong>\$$shortenedHourlyTipAvg</strong> in just tips</h4></li>";
     echo "<li><h4>Each shift you typically work around <strong>$shortenedTotalHrAvg</strong> hours from your first delivery</h4></li>";
     echo "<li><h4>Every delivery you take you get roughly <strong>\$$shortenedDailyTipAvg</strong> for a tip</h4></li>";
     echo "<li><h4>Each day you make roughly <strong>\$$shortTotalTipPerDay</strong> in just tips</h4></li>";
     echo "<li><h4>So Each day you typically make a gross of <strong>\$$GrossWagePerDay</strong> per day before the government takes some!</h4></li>";
     echo "<li>
     <h4>Every hour you make roughly <strong>\$$GrossWagePerHour</strong> take home!</h4>
     </li>";
     echo '</ul>';

     $sqlforchart = "SELECT Date,HourAvg  FROM `Averages` where User = 'admin'";
     $resultforchart = $connection->query($sqlforchart);
     $fields_num = mysqli_num_fields($resultforchart);
     $EmptyArray = array();
     while ($row = mysqli_fetch_row($resultforchart)) {
         $EmptyArray[] = array($row[0] => $row[1]);
     }
     $sumArray = array();
     foreach ($EmptyArray as $k => $subArray) {
         foreach ($subArray as $id => $value) {
             $sumArray[$id] += $value;
         }
     }

     //This is all used to get Avg Tip sum by hour
     $avgSql = 'SELECT substring(Delivery.Time,1,2),Delivery.`Tip$` from Delivery';
     $results = $connection->query($avgSql);
     $EmptyAvgArray = array();

     while ($row = mysqli_fetch_row($results)) {
         $EmptyAvgArray[] = array($row[0] => $row[1]);
     }

     //Actually the sum of each hour
     $sumByHour = array();
     $EmptyAvg = array();
     foreach ($EmptyAvgArray as $k1 => $subArray1) {
         foreach ($subArray1 as $id1 => $value1) {
             $sumByHour[$id1] += $value1;
             $countArray[] += $id1;
         }
     }
     //print_r($sumByHour);

  $parsedCountArray = array_count_values($countArray);
  ksort($sumByHour);
  ksort($parsedCountArray);
  //print_r($parsedCountArray);
  $avgTipSumByHour = array();
  for ($i = 10; $i < 10 + count($sumByHour); ++$i) {
      $value = $sumByHour[$i] / $parsedCountArray[$i];
      $avgTipSumByHour[$i] = $value;
  }
  //print_r($sumByHour);
  //print_r($avgTipSumByHour);


  foreach($sumByHour as $index => $val){
    echo "Hour: " . $index . " Something " .  $val . "This is the avg: " . $avgTipSumByHour[$index] . "</br>";
  }




  ?>
  <script type="text/javascript" src="https://www.google.com/jsapi"></script>
  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
  <script>
  google.charts.load("current", {packages:["corechart"]});
  google.charts.setOnLoadCallback(drawChart);
  function drawChart() {
  var data = google.visualization.arrayToDataTable([
  ['Hour', 'Tip$'],
   <?php
     foreach ($sumArray as $key => $value) {
         echo "['".$key."',".$value.'],';
     }
   ?>
  ]);

  var options =
      {
        pointSize: 5,
        hAxis: { title: 'Date'},
        vAxis: { title: 'Hourly Tip Average' },
      };
  var chart = new google.visualization.LineChart(document.getElementById("columnchart"));
  chart.draw(data, options);
  }

  // Chart for tip sum per hour
  google.charts.load("current", {packages:["corechart"]});
  google.charts.setOnLoadCallback(drawChart1);
  function drawChart1() {
  var data1 = google.visualization.arrayToDataTable([
  ['Hour', 'Tip Sum', 'Overall Avg/Hr'],
   <?php
     foreach ($sumByHour as $key1 => $value1) {
         echo "['".$key1."',".$value1. ",".$avgTipSumByHour[$key1] .'],';
     }
   ?>
  ]);

  var options1 =
      {
        pointSize: 5,
        hAxis: { title: 'Hour'},
        vAxis: { title: 'Tip Total' },
      };
  var chart1 = new google.visualization.LineChart(document.getElementById("SumChart"));
  chart1.draw(data1, options1);
  }



  google.charts.load("current", {packages:["corechart"]});
  google.charts.setOnLoadCallback(drawChart2);
  function drawChart2() {
  var data2 = google.visualization.arrayToDataTable([
  ['Hour', 'Avg/Delivery'],
   <?php
     foreach ($avgTipSumByHour as $key2 => $value2) {
         echo "['".$key2."',".$value2.'],';
     }
   ?>
  ]);

  var options2 =
      {
        pointSize: 5,
        hAxis: { title: 'Hour'},
        vAxis: { title: 'Avg Tip / Delivery' },
      };
  var chart2 = new google.visualization.LineChart(document.getElementById("AvgDeliv"));
  chart2.draw(data2, options2);
  }




         google.charts.load("current", {packages:["corechart"]});
         google.charts.setOnLoadCallback(drawChart2);
         function drawChart2() {
         var data2 = google.visualization.arrayToDataTable([
         ['Hour', 'Avg/Delivery'],
          <?php
            foreach ($avgTipSumByHour as $key2 => $value2) {
                echo "['".$key2."',".$value2.'],';
            }
          ?>
         ]);

         var options2 =
             {
               pointSize: 5,
               hAxis: { title: 'Hour'},
               vAxis: { title: 'Avg Tip / Delivery' },
             };
         var chart2 = new google.visualization.LineChart(document.getElementById("AvgDeliv"));
         chart2.draw(data2, options2);
         }


         google.charts.load("current", {packages:["corechart"]});
         google.charts.setOnLoadCallback(drawChart3);
         function drawChart3() {
         var data3 = google.visualization.arrayToDataTable([
         ['Hour', 'Delivery Count'],
          <?php
            foreach ($parsedCountArray as $key3 => $value3) {
                echo "['".$key3."',".$value3.'],';
            }
          ?>
         ]);

         var options3 =
             {
               pointSize: 5,
               hAxis: { title: 'Hour'},
               vAxis: { title: 'Delivery Count' },
             };
         var chart3 = new google.visualization.LineChart(document.getElementById("Delivcount"));
         chart3.draw(data3, options3);
         }

         google.charts.load('current', {'packages':['corechart']});
              google.charts.setOnLoadCallback(drawChart);
              function drawChart() {

                var data = google.visualization.arrayToDataTable([
                  ['Hour', 'TipSum', 'Tip/Hr'],
                  <?php
                    foreach ($sumByHour as $key1 => $value1) {
                        echo "['".$key1."',".$value1. ','. $avgTipSumByHour[$key1] .'],';
                    }
                  ?>
                ]);

                var options = {
                  title: 'My Daily Activities'
                };

                var chart = new google.visualization.PieChart(document.getElementById('piechart'));

                chart.draw(data, options);
              }




  </script>
  <div id="piechart"  height = "50%" width = "50%"></div><br />
  <div id="columnchart" style="margin-left: auto; margin-right: auto" height = "100%" width = "100%"></div><br />
  <div id ="SumChart" height = "100%" width = "100%"> </div>
  <br />
  <div id = "Delivcount" height = "100%" width = "100%">
  </div><br />
  <div id = "AvgDeliv" height = "100%" width = "100%">
  </div>


  <style>
  strong{
    color: black;
  }
   h4,h1{
     text-align: center;
   }
     body,ul{
       text-align: center;
       color: black;
     }
  </style>
  </head>
  </html>
