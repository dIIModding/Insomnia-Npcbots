-- InsomniaCore DBC mirror tables (minimal)

DROP TABLE IF EXISTS `ins_dbc_map`;
CREATE TABLE `ins_dbc_map` (
  `ID` int NOT NULL,
  `Directory` varchar(255) NOT NULL,
  `MapName` varchar(255) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

DROP TABLE IF EXISTS `ins_dbc_spelldata`;
CREATE TABLE `ins_dbc_spelldata` (
  `ID` int NOT NULL,
  `SpellName` varchar(255) NOT NULL,
  `SchoolMask` int NOT NULL,
  `Category` int NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

DROP TABLE IF EXISTS `ins_dbc_itemdata`;
CREATE TABLE `ins_dbc_itemdata` (
  `ID` int NOT NULL,
  `Class` int NOT NULL,
  `SubClass` int NOT NULL,
  `InventoryType` int NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
CREATE TABLE `ins_dbc_itemdata` (
  `ID` int unsigned NOT NULL,
  `Class` int unsigned NOT NULL,
  `SubClass` int unsigned NOT NULL,
  `InventoryType` int unsigned NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
DROP TABLE IF EXISTS `ins_dbc_map`;
CREATE TABLE `ins_dbc_map` (
  `ID` int unsigned NOT NULL,
  `Directory` varchar(255) NOT NULL,
  `MapName` varchar(255) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

DROP TABLE IF EXISTS `ins_dbc_spelldata`;
CREATE TABLE `ins_dbc_spelldata` (
  `ID` int unsigned NOT NULL,
  `SpellName` varchar(255) NOT NULL,
  `SchoolMask` int unsigned NOT NULL,
  `Category` int unsigned NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

DROP TABLE IF EXISTS `ins_dbc_itemdata`;
CREATE TABLE `ins_dbc_itemdata` (
  `ID` int unsigned NOT NULL,
  `Class` int unsigned NOT NULL,
  `SubClass` int unsigned NOT NULL,
  `InventoryType` int unsigned NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
DROP TABLE IF EXISTS `ins_dbc_map`;
CREATE TABLE `ins_dbc_map` (
  `ID` int unsigned NOT NULL,
  `Directory` varchar(255) NOT NULL,
  `MapName` varchar(255) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

DROP TABLE IF EXISTS `ins_dbc_spelldata`;
CREATE TABLE `ins_dbc_spelldata` (
  `ID` int unsigned NOT NULL,
  `SpellName` varchar(255) NOT NULL,
  `SchoolMask` int unsigned NOT NULL,
  `Category` int unsigned NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

DROP TABLE IF EXISTS `ins_dbc_itemdata`;
CREATE TABLE `ins_dbc_itemdata` (
  `ID` int unsigned NOT NULL,
  `Class` int unsigned NOT NULL,
  `SubClass` int unsigned NOT NULL,
  `InventoryType` int unsigned NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;