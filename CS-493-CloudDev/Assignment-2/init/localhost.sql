-- phpMyAdmin SQL Dump
-- version 4.8.0.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: May 08, 2018 at 03:42 AM
-- Server version: 8.0.11
-- PHP Version: 7.1.7

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `Cloud`
--
CREATE DATABASE IF NOT EXISTS `Cloud` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;
USE `Cloud`;

-- --------------------------------------------------------

--
-- Table structure for table `Businesses`
--

CREATE TABLE `Businesses` (
  `name` varchar(44) COLLATE utf8_unicode_ci NOT NULL,
  `owner` varchar(44) COLLATE utf8_unicode_ci NOT NULL,
  `address` varchar(44) COLLATE utf8_unicode_ci NOT NULL,
  `city` varchar(44) COLLATE utf8_unicode_ci NOT NULL,
  `state` varchar(44) COLLATE utf8_unicode_ci NOT NULL,
  `zip` varchar(44) COLLATE utf8_unicode_ci NOT NULL,
  `phone` varchar(44) COLLATE utf8_unicode_ci NOT NULL,
  `email` varchar(44) COLLATE utf8_unicode_ci NOT NULL,
  `businessID` int(155) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Categories`
--

CREATE TABLE `Categories` (
  `categoryID` int(55) NOT NULL,
  `name` varchar(55) COLLATE utf8_unicode_ci NOT NULL,
  `owner` varchar(55) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Photos`
--

CREATE TABLE `Photos` (
  `photoID` int(100) NOT NULL,
  `owner` varchar(55) COLLATE utf8_unicode_ci NOT NULL,
  `business` varchar(55) COLLATE utf8_unicode_ci NOT NULL,
  `caption` varchar(55) COLLATE utf8_unicode_ci NOT NULL,
  `image` varchar(55) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `Reviews`
--

CREATE TABLE `Reviews` (
  `reviewID` int(55) NOT NULL,
  `owner` varchar(555) COLLATE utf8_unicode_ci NOT NULL,
  `business` varchar(555) COLLATE utf8_unicode_ci NOT NULL,
  `star` int(11) NOT NULL,
  `dollar` int(11) NOT NULL,
  `message` varchar(555) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `subCategories`
--

CREATE TABLE `subCategories` (
  `id` int(55) NOT NULL,
  `name` varchar(55) COLLATE utf8_unicode_ci NOT NULL,
  `owner` varchar(55) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


-- --------------------------------------------------------

--
-- Table structure for table `Users`
--

CREATE TABLE `Users` (
  `name` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `type` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `id` int(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Businesses`
--
ALTER TABLE `Businesses`
  ADD PRIMARY KEY (`businessID`),
  ADD UNIQUE KEY `name` (`name`),
  ADD KEY `owner` (`owner`) USING BTREE;

--
-- Indexes for table `Categories`
--
ALTER TABLE `Categories`
  ADD PRIMARY KEY (`categoryID`),
  ADD UNIQUE KEY `name` (`name`);

--
-- Indexes for table `Photos`
--
ALTER TABLE `Photos`
  ADD PRIMARY KEY (`photoID`),
  ADD KEY `photo owner` (`owner`),
  ADD KEY `business photo` (`business`);

--
-- Indexes for table `Reviews`
--
ALTER TABLE `Reviews`
  ADD PRIMARY KEY (`reviewID`),
  ADD KEY `business review` (`business`),
  ADD KEY `ReviewOwner` (`owner`);

--
-- Indexes for table `subCategories`
--
ALTER TABLE `subCategories`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `name` (`name`);

--
-- Indexes for table `Users`
--
ALTER TABLE `Users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `name` (`name`),
  ADD UNIQUE KEY `name_2` (`name`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Businesses`
--
ALTER TABLE `Businesses`
  MODIFY `businessID` int(155) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `Categories`
--
ALTER TABLE `Categories`
  MODIFY `categoryID` int(55) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `Photos`
--
ALTER TABLE `Photos`
  MODIFY `photoID` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `Reviews`
--
ALTER TABLE `Reviews`
  MODIFY `reviewID` int(55) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `subCategories`
--
ALTER TABLE `subCategories`
  MODIFY `id` int(55) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `Users`
--
ALTER TABLE `Users`
  MODIFY `id` int(50) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
