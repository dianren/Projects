DROP TABLE HW2BUILDINGS;
DROP TABLE HW2STUDENTS;
DROP TABLE HW2TRAMSTOPS;

DELETE FROM USER_SDO_GEOM_METADATA 
   WHERE TABLE_NAME = 'HW2BUILDINGS' AND COLUMN_NAME = 'BU_SHAPE';
DELETE FROM USER_SDO_GEOM_METADATA 
   WHERE TABLE_NAME = 'HW2STUDENTS' AND COLUMN_NAME = 'STU_SHAPE';
DELETE FROM USER_SDO_GEOM_METADATA 
   WHERE TABLE_NAME = 'HW2TRAMSTOPS' AND COLUMN_NAME = 'TRAMS_SHAPE';
   
