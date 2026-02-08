USE ShippingLineDB;
GO

/* 
   DELETE DATA FROM ALL TABLES - order chosen to avoid FK violations
*/

DELETE FROM cargo;
DELETE FROM crew_assignment;
DELETE FROM incidents;
DELETE FROM maintenance_events;
DELETE FROM port_calls;
DELETE FROM cruises_waterbody;
DELETE FROM countries_waterbody;

DELETE FROM ports;
DELETE FROM cruises;
DELETE FROM orders;
DELETE FROM crew_members;

DELETE FROM ships;
DELETE FROM clients;
DELETE FROM waterbodies;
DELETE FROM countries;
