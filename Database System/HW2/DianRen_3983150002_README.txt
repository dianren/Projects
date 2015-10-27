{\rtf1\ansi\ansicpg1252\cocoartf1265\cocoasubrtf210
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural

\f0\fs24 \cf0 Name:   Dian Ren\
ID: 3983150002\
\
\
URL: {\field{\*\fldinst{HYPERLINK "http://www.sqlfiddle.com/#!2/2543c9/16"}}{\fldrslt http://www.sqlfiddle.com/#!2/2543c9/16}}\
\
SQL:\
\
CREATE TABLE HW2POINTS(\
  PO_ID CHAR(15) PRIMARY KEY,\
  PO_LOCATION POINT NOT NULL);\
\
\
CREATE TABLE HW2POLYGONS(\
  PGON_ID CHAR(15) PRIMARY KEY,\
  PGON_LOCATION POLYGON NOT NULL);\
\
\
INSERT INTO HW2POINTS VALUES('p1', GeomFromText( ' POINT( 1  1) ' ));\
  \
INSERT INTO HW2POLYGONS VALUES('polygon1', PolygonFromText('polygon(( 0 0, 3 0, 0 3, 0 0))'));\
\
\
\
\
\
SET @point = 'Point(1 1)';\
SET @polygon = 'Polygon((0 0,0 3,3 0,0 0))';\
\
\
\
SELECT GeometryType(PolygonFromText(@polygon));\
\
SELECT WITHIN(GeomFromText(@point), PolygonFromText(@polygon));\
\
\
SELECT CONTAINS(PolygonFromText(@polygon), GeomFromText(@point));\
\
\
SELECT AsText(Envelope(PolygonFromText(@polygon)));\
\
select Astext(Centroid(PolygonFromText(@polygon)));}