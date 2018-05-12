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
  <style> body{color: white;}</style>
</head>
<body>
  <h1>12/1/2016</h1>
  Largely I would say the website is functional enough to be presented, still lacking some more advanced features though
  <h1>12/5/2016</h1>
  I added two things to the database, DeliveryCount and TipSum for each shift a user works, haven't added any SQL to update it but its there
  <h1>12/6/2016</h1>
  <ul>
    <li>
      I also added a What's New section of the site to tell anyone what I have added lately, kinda like a lazy blog
    </li>
    <li>
      Added the $10 club, shows customers who tip more than $10
    </li>
    <li>
      Added a graph to track the hourly tip average you make per day in the Averages page for the user
    </li>
    <li>
      Added an error message for the signup page to tell you that the username that you chose is already taken, should have done that a LONG time ago.
    </li>
    <li>
      Added the ability to edit a delivery, but not the date or time, just all other delivery data
    </li>
  <h1>12/7/2016</h1>
    <li>
      Hull breach! I wiped out the shift table somehow, I think I fixed it though..
    </li>
    <li>
      Added Best and worst day, gives you stats on each respective day
    </li>
    <li>
      Added the My account page, lets you see overall data like Total Tips made, and Deliveries Taken
    </li>
    <li>
       Added the ability to change the password 
    </li>
  </ul>

</body>
</html>
