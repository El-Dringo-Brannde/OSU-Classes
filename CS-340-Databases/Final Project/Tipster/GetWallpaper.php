<?php
 require_once 'Mobile_Detect.php';
  $detect = new Mobile_Detect;
 if ($detect ->isMobile()){
   echo "<style>";
   echo "body{";
      echo "background-image: url(\"http://i.imgur.com/B8Fn7NP.jpg\");";
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
