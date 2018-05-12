<?php
  echo "<meta charset=\"utf-8\">";
  echo "<meta name=\"viewport\" content= \"width=device-width, initial-scale=1\">";
  echo "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\">";
  echo "<script src= \"https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js\"></script>";
  echo "<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js\"></script>";
  echo "</head>";
  echo "<body>";

  echo "<nav class=\"navbar navbar-inverse\">";
  echo "<div class=\"container-fluid\">";
  echo "<div class=\"navbar-header\">";
  echo "<button type=\"button\" class=\"navbar-toggle\" data-toggle=\"collapse\" data-target=\"#myNavbar\">";
  echo "<span class=\"icon-bar\"></span>";
  echo "<span class=\"icon-bar\"></span>";
        echo "<span class=\"icon-bar\"></span>";
      echo "</button>";
      echo "<a class=\"navbar-brand\" href=\"./homepage.php\">Tipster</a>";
    echo "</div>";
    echo "<div class=\"collapse navbar-collapse\" id=\"myNavbar\">";

      echo "<ul class=\"nav navbar-nav navbar-right\">";
      echo "<li class=\"dropdown\">";
  echo "<a class=\"dropdown-toggle\" data-toggle=\"dropdown\" href=\"#\">Account <span class=\"caret\"></span></a>";
  echo "<ul class=\"dropdown-menu\">";
    echo "<li><a href=\"./MyAccount.php\">My Account</a></li>";
    echo "<li><a href =\"./EditDelivery.php\">Edit a delivery</a></li>";
    echo "<li><a href=\"./Averages.php\">Averages</a></li>";
    echo "<li> <a href = \"./BestDayEver.php\">Best Day</a></li>";
    echo "<li><a href = \"./WorstDayEver.php\">Worst Day</a></li>";
    echo "<li><a href=\"./logout.php\">Logout</a></li>";
  echo "</ul>";
  echo "</li>";
  echo "<li> <a href = \"./about.php\">About</a></li>";
        echo "<li><a href=\"./Halp.php\"><span class=\"glyphicons glyphicons-person-stick-old\"></span> HALP!/FAQ</a></li>";
        echo "<li><a href = \"./NoTipList.php\">No Tip List</a></li>";
        echo "<li>
         <a href = \"./10dollarclub.php\">$10 Club</a></li>";
        echo "<li><a href = \"./WhatsNew.php\">What's New?</a></li>";
      echo "</ul>";
    echo "</div>";
  echo "</div>";
echo "</nav>";

?>
