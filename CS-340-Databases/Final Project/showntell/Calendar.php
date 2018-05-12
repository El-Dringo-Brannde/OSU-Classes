<html>
  <head>
    <?php

       require_once 'connectvarsEECS.php';
       $connection = mysqli_connect(servername, username, password, dbname);
       $sql = "SELECT HourAvg, Date FROM `Averages` where Averages.User = 'admin'";

       if (!$connection) {
           die('connection to SQL server failed!');
       }
       $DateArr = array();
       $AvgArr = array();

       $results = $connection->query($sql);
       while ($row = mysqli_fetch_row($results)) {
           $DateArr[] = $row[1];
           $AvgArr[] = $row[0];
       }
      for ($i = 0; $i < count($DateArr); ++$i) {
          $DateArr[$i] = substr_replace($DateArr[$i], $DateArr[$i] - 1, 0,2); //negates by 1
          if ($DateArr[$i][1] == '/') //If there is a / in the tens column append 0 to front
            $DateArr[$i] = substr_replace($DateArr[$i],0,0,0);
      }


    ?>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">
      google.charts.load("current", {packages:["calendar"]});
      google.charts.setOnLoadCallback(drawChart);

   function drawChart() {
       var dataTable = new google.visualization.DataTable();
       dataTable.addColumn({ type: 'date', id: 'Date' });
       dataTable.addColumn({ type: 'number', id: 'Won/Loss' });
       dataTable.addRows([
         <?php
         for ($i = 0; $i < count($DateArr); ++$i) {
             $temp = str_replace('/', ' ', $DateArr[$i]);
             echo '[new Date('.substr($temp, 6, 9).','.
              substr($temp, 0, 2).','.substr($temp, 3, 3).'),'.
               substr($AvgArr[$i], 0, 4) .'],';

         }
         ?>
        ]);


       var chart = new google.visualization.Calendar(document.getElementById('calendar_basic'));

       var options = {
         title: "Hourly Tip Avg",
         height: 350,
         calendar: {
    monthLabel: {
      fontName: 'Times-Roman',
      fontSize: 12,
      color: 'Black',
      bold: true,
      italic: true
    },
    monthOutlineColor: {
      stroke: '#981b48',
      strokeOpacity: 0.8,
      strokeWidth: 2
    },
    unusedMonthOutlineColor: {
      stroke: '#bc5679',
      strokeOpacity: 0.8,
      strokeWidth: 1
    },
    underMonthSpace: 16,
  }

       };

       chart.draw(dataTable, options);
   }
    </script>
  </head>
  <body>
    <div id="calendar_basic" style="width: 1000px; height: 500px; margin-left:auto; margin-right: auto;"></div>
  </body>
</html>
