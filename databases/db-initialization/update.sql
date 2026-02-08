USE ShippingLineDB;
GO

/* SHIPS (5 rows) - verify whether references in other tables changed their values */
UPDATE ships
SET imo_number = '9600002'
WHERE imo_number = '9500002'

UPDATE ships
SET imo_number = '9600003'
WHERE imo_number = '9500003'

UPDATE ships
SET imo_number = '9600004'
WHERE imo_number = '9500004'

UPDATE ships
SET imo_number = '9600005'
WHERE imo_number = '9500005'

UPDATE ships
SET imo_number = '9600006'
WHERE imo_number = '9500006'


/* CLIENTS (5 rows) */
UPDATE clients
SET contract_valid_to = '2028-12-31'
WHERE client_code = 1;  

UPDATE clients
SET contract_valid_to = '2026-12-31'
WHERE client_code = 2;  

UPDATE clients
SET contract_valid_to = '2029-03-01'
WHERE client_code = 3;  

UPDATE clients
SET contract_valid_to = '2029-04-14'
WHERE client_code = 5;  

UPDATE clients
SET contract_valid_to = '2029-05-01'
WHERE client_code = 10; 


/* ORDERS (5 rows) */
UPDATE orders
SET status = 'COMPLETED'
WHERE id = 3;   

UPDATE orders
SET status = 'COMPLETED'
WHERE id = 4;   

UPDATE orders
SET status = 'IN PROGRESS'
WHERE id = 6;  

UPDATE orders
SET status = 'IN PROGRESS'
WHERE id = 8;   

UPDATE orders
SET order_placement_date = '2024-02-01 10:00:00'
WHERE id = 10;




/* CRUISES (5 rows) */
UPDATE cruises
SET status = 'FINISHED'
WHERE id = 5;

UPDATE cruises
SET status = 'IN PROGRESS',
    atd    = '2024-06-01 12:05:00'
WHERE id = 6;

UPDATE cruises
SET status = 'IN PROGRESS',
    atd = '2024-06-20 05:10:00'
WHERE id = 7;

UPDATE cruises
SET status = 'CANCELED'
WHERE id = 8;

UPDATE cruises
SET etd = '2024-08-02 06:00:00',
    eta = '2024-08-11 11:00:00'
WHERE id = 9;



/* CREW MEMBERS (5 rows) */
UPDATE crew_members
SET rank = 'Master'
WHERE id = 1;   

UPDATE crew_members
SET rank = 'Chief Officer'
WHERE id = 2;   

UPDATE crew_members
SET contract_termination = '2030-03-31'
WHERE id = 3;   

UPDATE crew_members
SET contract_termination = '2029-12-31'
WHERE id = 4;  

UPDATE crew_members
SET rank = 'Second Officer'
WHERE id = 10;  

/* PORT CALLS (5) rows) */
UPDATE port_calls
SET ata = '2024-01-10 19:30:00'
WHERE cruise_id = 1 AND seq_no = 1;

UPDATE port_calls
SET ata = '2024-01-12 20:45:00'
WHERE cruise_id = 1 AND seq_no = 2;

UPDATE port_calls
SET status = 'FINISHED'
WHERE cruise_id = 5 AND seq_no = 1;

UPDATE port_calls
SET status = 'IN PROGRESS',
    atd    = '2024-05-22 08:10:00',
    ata    = '2024-05-22 19:50:00'
WHERE cruise_id = 5 AND seq_no = 2;

UPDATE port_calls
SET status = 'IN PROGRESS'
WHERE cruise_id = 6 AND seq_no = 1;


/* MAINTENANCE EVENTS (5 rows) */
UPDATE maintenance_events
SET [end] = '2023-03-04'
WHERE id = 1; 

UPDATE maintenance_events
SET status = 'CANCELED'
WHERE id = 5;   

UPDATE maintenance_events
SET status = 'IN PROGRESS'
WHERE id = 10;  

UPDATE maintenance_events
SET status = 'IN PROGRESS'
WHERE id = 18;  

UPDATE maintenance_events
SET status = 'CANCELED'
WHERE id = 20;  


/* INCIDENTS (5 rows) */
UPDATE incidents
SET severity  = 'MAJOR',
    delay_min = 90
WHERE id = 1;   

UPDATE incidents
SET delay_min = 180
WHERE id = 3;   

UPDATE incidents
SET severity  = 'CRITICAL',
    delay_min = 420
WHERE id = 5;   

UPDATE incidents
SET severity  = 'MINOR',
    delay_min = 240
WHERE id = 9;   

UPDATE incidents
SET severity  = 'MAJOR',
    delay_min = 300
WHERE id = 17;  


/* CREW_ASSIGNMENT (5 rows) */
UPDATE crew_assignment
SET cruise_id = 2
WHERE crew_id = 2 AND cruise_id = 1;  

UPDATE crew_assignment
SET cruise_id = 4
WHERE crew_id = 5 AND cruise_id = 3;  

UPDATE crew_assignment
SET cruise_id = 1
WHERE crew_id = 7 AND cruise_id = 4;   

UPDATE crew_assignment
SET cruise_id = 5
WHERE crew_id = 11 AND cruise_id = 6;  

UPDATE crew_assignment
SET cruise_id = 8
WHERE crew_id = 19 AND cruise_id = 10;


/* CARGO (5 rows) */
UPDATE cargo
SET status = 'DELIVERED',
    transported_weight_t = 882.000
WHERE id = 4;   

UPDATE cargo
SET status = 'DELIVERED',
    transported_weight_t = 498.000
WHERE id = 6;   

UPDATE cargo
SET status = 'DELIVERED',
    transported_weight_t = 648.000
WHERE id = 11;  

UPDATE cargo
SET status = 'IN DELIVERY',
    transported_weight_t = 480.000
WHERE id = 14;  

UPDATE cargo
SET status = 'CANCELED',
    transported_weight_t = 20.000
WHERE id = 20;  




