-- phpMyAdmin SQL Dump
-- version 4.6.5.1
-- https://www.phpmyadmin.net/
--
-- Host: mysql.eecs.oregonstate.edu
-- Generation Time: Dec 07, 2016 at 02:20 PM
-- Server version: 5.5.37-MariaDB-wsrep
-- PHP Version: 7.0.13

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cs340_dringb`
--

DELIMITER $$
--
-- Procedures
--
CREATE DEFINER=`cs340_dringb`@`%` PROCEDURE `Change_pass` (IN `New_Pass` VARCHAR(50), IN `Username` VARCHAR(50))  NO SQL
Update `ProjectUsers` set `ProjectUsers`.`Password` = New_Pass where `ProjectUsers`.`Username` = Username$$

CREATE DEFINER=`cs340_dringb`@`%` PROCEDURE `Change_Store` (IN `Cur_User` VARCHAR(50), IN `New_Store` VARCHAR(50))  NO SQL
Update ProjectUsers Set ProjectUsers.`Store Location` = New_Store where ProjectUsers.Username = Cur_User$$

CREATE DEFINER=`cs340_dringb`@`%` PROCEDURE `UpdateAllCollegeStats` ()  Begin 

Declare done int default 0; 
declare current_cName varchar(20); 
declare cNamecur cursor for select cName from Collegestats;
declare continue handler for not found set done = 1; 

open cNamecur; 

repeat 
	fetch cNamecur into current_cName;
    
    Update Collegestats
    set appCount = (SELECT count(*) from Apply where cName = current_cName)
    where cName = current_cName; 
    
    Update Collegestats
    set minGPA = (select min(gpa) from Apply, Student where Apply.cName = current_cName and Apply.sID = Student.sID)
    where cName = current_cName;
    
    Update Collegestats
    Set maxGPA = (select max(gpa) from Apply,Student where Apply.cName = current_cName and Apply.sID = Student.sID)
    where cName = current_cName; 
    
    UNTIL done 
    End repeat; 
    close cNamecur; 
END$$

CREATE DEFINER=`cs340_dringb`@`%` PROCEDURE `updateCollegeStats` (IN `param1` VARCHAR(20))  BEGIN
UPDATE Collegestats
SET appCount = (select count(*) from Apply where cName = param1)
WHERE cName = param1;

UPDATE Collegestats
SET minGPA = (SELECT min(gpa) from Apply, Student WHERE Apply.cName = param1 and Apply.sID = Student.sID)
WHERE cName = param1;

UPDATE Collegestats
SET maxGPA = (select max(gpa) from Apply, Student where Apply.cName = param1 and Apply.sID = Student.sID)
WHERE cName = param1;
END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `Averages`
--

CREATE TABLE `Averages` (
  `HourAvg` float DEFAULT NULL,
  `DayAvg` float DEFAULT NULL,
  `User` varchar(50) NOT NULL,
  `Date` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Averages`
--

INSERT INTO `Averages` (`HourAvg`, `DayAvg`, `User`, `Date`) VALUES
(10.81, 5.25, 'admin', '10/29/2016'),
(12.53, 5.18, 'admin', '11/12/2016'),
(12.19, 4.875, 'admin', '11/13/2016'),
(14.62, 6.28, 'admin', '11/19/2016'),
(12.8103, 4.88333, 'admin', '12/02/2016'),
(10.9059, 5.38095, 'admin', '12/03/2016'),
(60, 2, 'Shlink Lincoln', '12/02/2016');

-- --------------------------------------------------------

--
-- Table structure for table `Delivery`
--

CREATE TABLE `Delivery` (
  `DeliveryID` int(11) NOT NULL,
  `Date` varchar(10) NOT NULL,
  `Time` varchar(10) NOT NULL,
  `Username` varchar(50) NOT NULL,
  `OrderTotal` float NOT NULL,
  `Tip$` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Delivery`
--

INSERT INTO `Delivery` (`DeliveryID`, `Date`, `Time`, `Username`, `OrderTotal`, `Tip$`) VALUES
(28, '10/29/2016', '13:28:41', 'admin', 21, 5),
(29, '10/29/2016', '13:29:15 ', 'admin', 30.25, 10),
(30, '10/29/2016', '13:29:56 ', 'admin', 48.25, 10),
(31, '10/29/2016', '13:30:39 ', 'admin', 17.5, 0),
(32, '10/29/2016', '13:31:05 ', 'admin', 41.25, 6.75),
(33, '10/29/2016', '15:33:45 ', 'admin', 182.5, 18),
(34, '10/29/2016', '15:34:16 ', 'admin', 26, 5),
(35, '10/29/2016', '20:10:04 ', 'admin', 21, 2.5),
(36, '10/29/2016', '20:10:56 ', 'admin', 31.5, 4.5),
(37, '10/29/2016', '20:11:54 ', 'admin', 23.5, 2.5),
(38, '10/29/2016', '20:12:36 ', 'admin', 32, 4),
(39, '10/29/2016', '21:51:05 ', 'admin', 24.25, 5),
(40, '10/29/2016', '21:51:31 ', 'admin', 43.5, 5),
(41, '10/29/2016', '21:51:55 ', 'admin', 27.75, 5),
(42, '10/29/2016', '21:52:27 ', 'admin', 23.5, 5),
(43, '10/29/2016', '21:53:15 ', 'admin', 23, 2),
(44, '10/29/2016', '21:53:39 ', 'admin', 21, 0),
(45, '10/29/2016', '22:11:37 ', 'admin', 33.5, 4),
(46, '11/12/2016', '13:13:54', 'admin', 26.25, 5),
(47, '11/12/2016', '13:13:54', 'admin', 26.25, 5),
(48, '11/12/2016', '13:14:59', 'admin', 26.25, 5),
(49, '11/12/2016', '16:12:08', 'admin', 32, 2),
(50, '11/12/2016', '16:12:08', 'admin', 32, 2),
(51, '11/12/2016', '16:12:08', 'admin', 32, 2),
(52, '11/12/2016', '16:18:58', 'admin', 79, 5),
(53, '11/12/2016', '16:19:51', 'admin', 26.25, 5),
(54, '11/12/2016', '16:20:29', 'admin', 22.5, 5),
(55, '11/12/2016', '16:20:57', 'admin', 39.5, 4),
(56, '11/12/2016', '16:21:52', 'admin', 36, 5),
(57, '11/12/2016', '16:22:36', 'admin', 331.4, 20),
(58, '11/12/2016', '16:24:30', 'admin', 93.8, 10),
(59, '11/12/2016', '16:25:59', 'admin', 37.75, 4),
(60, '11/12/2016', '16:28:36', 'admin', 29, 5),
(61, '11/12/2016', '17:39:04', 'admin', 30, 5),
(62, '11/12/2016', '18:09:21', 'admin', 19.5, 2.5),
(63, '11/12/2016', '18:17:34', 'admin', 20.5, 3),
(64, '11/12/2016', '18:55:12', 'admin', 41.25, 3.75),
(65, '11/12/2016', '19:06:12', 'admin', 20.5, 3),
(66, '11/12/2016', '19:39:22', 'admin', 17, 2),
(67, '11/12/2016', '21:08:34', 'admin', 42.5, 2.5),
(68, '11/12/2016', '22:44:01', 'admin', 20.75, 2.25),
(69, '11/12/2016', '22:59:23', 'admin', 44.75, 15.25),
(70, '11/13/2016', '17:01:21', 'admin', 24.25, 5),
(71, '11/13/2016', '17:22:32', 'admin', 36.5, 4),
(72, '11/13/2016', '17:31:06', 'admin', 19, 3),
(73, '11/13/2016', '18:28:43', 'admin', 31.5, 3),
(74, '11/13/2016', '19:13:39', 'admin', 44.5, 7.5),
(75, '11/13/2016', '19:23:56', 'admin', 32.25, 6.75),
(141, '11/19/2016', '10:42:34', 'admin', 487.32, 50),
(142, '11/19/2016', '12:06:04', 'admin', 269, 5),
(143, '11/19/2016', '12:27:58', 'admin', 27, 6),
(144, '11/19/2016', '12:50:20', 'admin', 22.75, 2.25),
(145, '11/19/2016', '12:56:27', 'admin', 29.75, 5),
(146, '11/19/2016', '13:30:13', 'admin', 74, 6),
(147, '11/19/2016', '13:40:04', 'admin', 22.5, 3),
(148, '11/19/2016', '15:17:17', 'admin', 80.5, 5),
(149, '11/19/2016', '15:20:46', 'admin', 44, 5),
(150, '11/19/2016', '16:17:52', 'admin', 35.75, 5),
(151, '11/19/2016', '16:31:02', 'admin', 20.5, 4),
(152, '11/19/2016', '16:31:19', 'admin', 26, 3),
(153, '11/19/2016', '18:07:34', 'admin', 22, 8),
(154, '11/19/2016', '18:41:48', 'admin', 54.75, 3),
(155, '11/19/2016', '18:48:31', 'admin', 37, 3),
(156, '11/19/2016', '19:26:51', 'admin', 23.5, 6),
(157, '11/19/2016', '19:36:24', 'admin', 24.25, 0),
(158, '11/19/2016', '20:24:26', 'admin', 31, 3),
(159, '11/19/2016', '20:36:56', 'admin', 21, 0),
(160, '11/19/2016', '21:17:46', 'admin', 40, 0),
(161, '11/19/2016', '21:23:21', 'admin', 30.25, 6),
(162, '11/19/2016', '21:23:31', 'admin', 36, 10),
(166, '11/29/2016', '19:25:12', 'admin', 23, 5),
(167, '11/29/2016', '21:35:25', 'admin', 25, 15),
(175, '12/02/2016', '12:59:41', '', 222, 2),
(176, '12/02/2016', '16:48:56', 'admin', 27, 7),
(177, '12/02/2016', '17:17:41', 'admin', 33.25, 6),
(178, '12/02/2016', '17:47:54', 'admin', 43, 0),
(179, '12/02/2016', '17:48:00', 'admin', 43, 3),
(180, '12/02/2016', '18:04:07', 'admin', 37.5, 10),
(181, '12/02/2016', '18:26:07', 'admin', 18, 4),
(182, '12/02/2016', '18:33:36', 'admin', 41.25, 10),
(183, '12/02/2016', '19:00:11', 'admin', 30.5, 2),
(184, '12/02/2016', '19:12:43', 'admin', 32, 5),
(185, '12/02/2016', '19:25:24', 'admin', 23.5, 4),
(186, '12/02/2016', '19:59:06', 'admin', 29, 3),
(187, '12/02/2016', '20:05:36', 'admin', 27.75, 3.25),
(188, '12/02/2016', '20:19:30', 'Shlink Lincoln', 28.5, 2),
(189, '12/02/2016', '20:43:03', 'Shlink Lincoln', 20.5, 4.5),
(190, '12/02/2016', '20:59:06', 'admin', 20.5, 10),
(191, '12/02/2016', '20:44:04', 'Shlink Lincoln', 20.5, 5.5),
(192, '12/02/2016', '21:29:07', 'Shlink Lincoln', 40.5, 5),
(193, '12/02/2016', '22:04:22', 'Shlink Lincoln', 28.5, 3.5),
(194, '12/02/2016', '22:06:26', 'admin', 26.5, 2),
(195, '12/02/2016', '22:16:33', 'admin', 43.5, 4),
(196, '12/03/2016', '12:34:25', 'admin', 130.25, 8),
(197, '12/03/2016', '13:43:15', 'admin', 23.5, 3),
(198, '12/03/2016', '13:54:43', 'admin', 30, 5),
(199, '12/03/2016', '14:16:02', 'admin', 33.25, 5),
(200, '12/03/2016', '14:27:24', 'admin', 113.75, 10),
(201, '12/03/2016', '14:49:02', 'admin', 24.25, 5.75),
(202, '12/03/2016', '15:11:51', 'admin', 21.5, 6),
(203, '12/03/2016', '15:24:26', 'admin', 37.75, 6.25),
(204, '12/03/2016', '16:22:58', 'admin', 27, 20),
(205, '12/03/2016', '16:48:06', 'admin', 31, 2),
(206, '12/03/2016', '17:28:09', 'admin', 24.25, 5),
(207, '12/03/2016', '17:28:44', 'admin', 35.5, 2),
(208, '12/03/2016', '18:04:57', 'admin', 20.5, 2),
(209, '12/03/2016', '18:18:13', 'admin', 17.5, 3.5),
(210, '12/03/2016', '18:41:57', 'admin', 42, 3),
(211, '12/03/2016', '18:49:07', 'admin', 24.25, 3),
(212, '12/03/2016', '19:15:53', 'admin', 22, 2),
(213, '12/03/2016', '19:26:13', 'admin', 20.5, 9.5),
(214, '12/03/2016', '20:44:19', 'admin', 34.5, 6),
(215, '12/03/2016', '20:52:57', 'admin', 24.25, 5),
(216, '12/03/2016', '21:40:03', 'admin', 21, 1);

-- --------------------------------------------------------

--
-- Table structure for table `Location`
--

CREATE TABLE `Location` (
  `DeliveryID` int(10) NOT NULL,
  `Address` int(20) NOT NULL,
  `Street` varchar(30) NOT NULL,
  `APT` varchar(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Location`
--

INSERT INTO `Location` (`DeliveryID`, `Address`, `Street`, `APT`) VALUES
(28, 2985, 'nw Moda way', '314'),
(29, 890, 'nw 176th ave', NULL),
(30, 5565, 'nw Roanoke ln', NULL),
(31, 5102, 'nw crady ln', NULL),
(32, 2895, 'nw 156th pl', NULL),
(33, 5335, 'nw Roanoke ln', NULL),
(34, 18582, 'nw Holly st ', '206'),
(35, 16380, 'SW estuary dr', '202'),
(36, 762, 'SW 206th pl', NULL),
(37, 322, 'nw 215th terr', NULL),
(38, 730, 'nw autumncreek wy', NULL),
(39, 13910, 'SW Walker rd', NULL),
(40, 16275, 'SW mason ln', NULL),
(41, 15390, 'nw oakhills dr', NULL),
(42, 12572, 'nw amethyst CT ', NULL),
(43, 14686, 'nw Cornell Rd ', '84'),
(44, 5822, 'nw redfox dr ', NULL),
(45, 13115, 'SW evergreen st ', NULL),
(51, 16155, 'NW Cornell Rd', NULL),
(52, 1600, 'NW 167 pl', '320'),
(53, 296, 'NW 182nd ave', NULL),
(54, 18582, 'nw Holly st', '206'),
(55, 12280, 'NW Barnes Rd', NULL),
(56, 20860, 'NW painted mountain dr', NULL),
(57, 21700, 'NW wagon way', NULL),
(58, 16340, 'NW Bethany CT ', NULL),
(59, 1940, 'NW Miller Rd', 'D114'),
(60, 110, 'SW 137th Ave', '3'),
(61, 9691, 'NW Nottage Dr', NULL),
(62, 245, 'NW 117th Loop', NULL),
(63, 12740, 'SW Morrison St', NULL),
(64, 16697, 'NW Paddington Dr', NULL),
(65, 1725, 'NW Caitlin Terrace', NULL),
(66, 12433, 'NW 123rd Ave', '109'),
(67, 810, 'nw Island Terrace', 'a-8'),
(68, 12891, 'NW Dogwood St', NULL),
(69, 304, 'NW 207th Ave', NULL),
(70, 10163, 'NW jack ln', NULL),
(71, 20820, 'NW Wallula Ct', NULL),
(72, 16951, 'Northwest Milcliff Street', NULL),
(73, 20461, 'SW Keylock Ln', NULL),
(74, 18830, 'NW Rock Creek Cir', '261'),
(75, 2181, 'Upton Terrace', NULL),
(141, 14400, 'nw Greenbrier pkwy', NULL),
(142, 13775, 'SW Walker Rd', NULL),
(143, 2278, 'Nw 118th Ave ', NULL),
(144, 12642, 'NW Barnes Rd', '5'),
(145, 1450, 'NW Caitlin Terrace', NULL),
(146, 5565, 'NW Roanoke Ln', NULL),
(147, 5643, 'NW 179th Ave', NULL),
(148, 221, 'SW 204th Terrace', NULL),
(149, 20642, 'N W Painted Mountain Dr', NULL),
(150, 1940, 'NW Miller Rd', 'D114'),
(151, 120, 'SW 131st Ave', NULL),
(152, 2465, 'NW Schmidt Way', '313'),
(153, 2080, 'NW Thorncroft Dr', '1122'),
(154, 4331, 'NW Diamondback Dr', NULL),
(155, 4770, 'NW 186th Ave', NULL),
(156, 615, 'SW 171st Ave', NULL),
(157, 18370, 'NW Cornell Rd ', 'E'),
(158, 3525, 'NW 179th Pl', NULL),
(159, 3055, 'NW Ashford Cir', NULL),
(160, 910, 'NW Island Terrace', 'B3'),
(161, 1163, 'SW 160th Ave', NULL),
(162, 812, 'NW Fieldcrest Way', 'Q312'),
(166, 1836, 'NW Grant Cir', NULL),
(167, 1836, 'NW Grant Cir', NULL),
(175, 1836, 'NW Grant Cir', NULL),
(176, 8210, 'NW Ridgetop Ct', NULL),
(177, 14760, 'NW Central ct', NULL),
(178, 24, 'Venetian Dr', NULL),
(179, 2730, 'NW Palazza Way ', NULL),
(180, 15525, 'NW Gateway Ct', '135'),
(181, 16505, 'SW Estuary Dr', NULL),
(182, 170, 'SW Salix Terrace', NULL),
(183, 12688, 'NW Naomi Ln', NULL),
(184, 469, 'NW Skyline Blvd', NULL),
(185, 11046, 'NW Ridge Rd', NULL),
(186, 16116, 'NW Paisley Dr', NULL),
(187, 2252, 'NW 161st Pl', NULL),
(188, 20647, 'NW Trailwalk Dr', 'H201'),
(189, 668, 'NW Royden Terr', NULL),
(190, 11223, 'NW Saltzman Rd', NULL),
(191, 4711, 'SE Paladin Ln', NULL),
(192, 21670, 'SW Imperial Ct', NULL),
(193, 3115, 'NW Nyssa Ct', NULL),
(194, 17335, 'Sw Jay St', '205'),
(195, 2335, 'SW Briggs Rd', '9'),
(196, 5565, 'NW Roanoke Ln', NULL),
(197, 16380, 'SW Estuary Dr', '202'),
(198, 2820, 'SW 119th Ave', NULL),
(199, 2413, 'NW 153rd Ave', NULL),
(200, 5570, 'NW Toketee Dr', NULL),
(201, 13050, 'SW Brightwood St', NULL),
(202, 14575, 'NW 145th Pl', NULL),
(203, 18804, 'NW Park Ridge Way', NULL),
(204, 15302, 'NW Nightshade Dr', NULL),
(205, 17184, 'SW Artesian Ln', NULL),
(206, 16185, 'nw schendel ave', 'E'),
(207, 810, 'NW Island Terrace', 'A8'),
(208, 9990, 'SW Morrison St', NULL),
(209, 1740, 'NW 143rd Ave', NULL),
(210, 2061, 'NW 127th Pl', NULL),
(211, 14800, 'NW Cornell Rd', '3g'),
(212, 3785, 'NW 120th Terrace', NULL),
(213, 255, 'NW 116th Ave', '405'),
(214, 4155, 'SW 177th Ave', NULL),
(215, 15256, 'SW Millikan Way', '312'),
(216, 17630, 'NW Cornell Rd', '15');

-- --------------------------------------------------------

--
-- Table structure for table `ProjectUsers`
--

CREATE TABLE `ProjectUsers` (
  `Username` varchar(50) NOT NULL,
  `Password` varchar(50) NOT NULL,
  `Store Location` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ProjectUsers`
--

INSERT INTO `ProjectUsers` (`Username`, `Password`, `Store Location`) VALUES
('admin', 'dringo', 'Beaverton'),
('Brandon', 'Beandip', 'Beaverton'),
('Dringo1', 'password', 'Tigard'),
('Kelli', 'Abby', 'Tigard'),
('Shlink Lincoln', 'naked1', 'Beaverton'),
('Test', 'test', 'Beaverton');

-- --------------------------------------------------------

--
-- Stand-in structure for view `RunningAvg`
-- (See below for the actual view)
--
CREATE TABLE `RunningAvg` (
`avg(``Tip$``)` double
);

-- --------------------------------------------------------

--
-- Table structure for table `Shift`
--

CREATE TABLE `Shift` (
  `Date` varchar(10) NOT NULL,
  `Username` varchar(50) NOT NULL,
  `Hours` float NOT NULL,
  `TipSum` float NOT NULL,
  `DeliveryCount` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `Shift`
--

INSERT INTO `Shift` (`Date`, `Username`, `Hours`, `TipSum`, `DeliveryCount`) VALUES
('10/29/2016', 'admin', 9.55, 94.25, 18),
('11/12/2016', 'admin', 9.75, 123.25, 24),
('11/13/2016', 'admin', 2.37, 29.25, 6),
('11/19/2016', 'admin', 10.37, 138.25, 22),
('12/02/2016', 'admin', 5.46, 73.25, 15),
('12/03/2016', 'admin', 9.11, 113, 21);

-- --------------------------------------------------------

--
-- Structure for view `RunningAvg`
--
DROP TABLE IF EXISTS `RunningAvg`;

CREATE ALGORITHM=UNDEFINED DEFINER=`cs340_dringb`@`%` SQL SECURITY DEFINER VIEW `RunningAvg`  AS  select avg(`Delivery`.`Tip$`) AS `avg(``Tip$``)` from `Delivery` ;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Averages`
--
ALTER TABLE `Averages`
  ADD PRIMARY KEY (`User`,`Date`),
  ADD KEY `Date` (`Date`);

--
-- Indexes for table `Delivery`
--
ALTER TABLE `Delivery`
  ADD PRIMARY KEY (`DeliveryID`),
  ADD KEY `Delivery_ibfk_2` (`Username`),
  ADD KEY `Delivery_ibfk_1` (`Date`);

--
-- Indexes for table `Location`
--
ALTER TABLE `Location`
  ADD PRIMARY KEY (`DeliveryID`);

--
-- Indexes for table `ProjectUsers`
--
ALTER TABLE `ProjectUsers`
  ADD PRIMARY KEY (`Username`);

--
-- Indexes for table `Shift`
--
ALTER TABLE `Shift`
  ADD PRIMARY KEY (`Date`,`Username`),
  ADD KEY `Shift_ibfk_1` (`Username`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Delivery`
--
ALTER TABLE `Delivery`
  MODIFY `DeliveryID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=221;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `Averages`
--
ALTER TABLE `Averages`
  ADD CONSTRAINT `Averages_ibfk_3` FOREIGN KEY (`User`) REFERENCES `ProjectUsers` (`Username`),
  ADD CONSTRAINT `Averages_ibfk_4` FOREIGN KEY (`User`) REFERENCES `ProjectUsers` (`Username`);

--
-- Constraints for table `Location`
--
ALTER TABLE `Location`
  ADD CONSTRAINT `fk_DelivID` FOREIGN KEY (`DeliveryID`) REFERENCES `Delivery` (`DeliveryID`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `Shift`
--
ALTER TABLE `Shift`
  ADD CONSTRAINT `Shift_ibfk_1` FOREIGN KEY (`Username`) REFERENCES `ProjectUsers` (`Username`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
