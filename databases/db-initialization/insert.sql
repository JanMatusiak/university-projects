USE ShippingLineDB;
GO

/* COUNTRIES (10 rows) */
INSERT INTO countries (continent, name, area_m2, population) VALUES ('Europe',        'Poland',         312679000000.00,   38000000);
INSERT INTO countries (continent, name, area_m2, population) VALUES ('Europe',        'Germany',        357022000000.00,   83000000);
INSERT INTO countries (continent, name, area_m2, population) VALUES ('Europe',        'United Kingdom', 243610000000.00,   67000000);
INSERT INTO countries (continent, name, area_m2, population) VALUES ('Europe',        'Netherlands',    41543000000.00,    17500000);
INSERT INTO countries (continent, name, area_m2, population) VALUES ('Europe',        'Spain',          505990000000.00, 47000000);
INSERT INTO countries (continent, name, area_m2, population) VALUES ('Europe',        'Italy',          301340000000.00, 59000000); 
INSERT INTO countries (continent, name, area_m2, population) VALUES ('Europe',        'Greece',         131957000000.00, 10400000);
INSERT INTO countries (continent, name, area_m2, population) VALUES ('North America', 'United States',  9833517000000.00, 331000000);
INSERT INTO countries (continent, name, area_m2, population) VALUES ('Asia',          'China',          9596961000000.00,1400000000);
INSERT INTO countries (continent, name, area_m2, population) VALUES ('Asia',          'Singapore',      728000000.00,    5600000);

/* WATERBODIES (10 rows) */
INSERT INTO waterbodies (name, navarea, kind) VALUES ('Baltic Sea',        'I',   'SEA');
INSERT INTO waterbodies (name, navarea, kind) VALUES ('North Sea',         'I',   'SEA');
INSERT INTO waterbodies (name, navarea, kind) VALUES ('North Atlantic',     'IV',  'SEA');
INSERT INTO waterbodies (name, navarea, kind) VALUES ('Mediterranean Sea',   'III',  'SEA');
INSERT INTO waterbodies (name, navarea, kind) VALUES ('Red Sea',   'IX',  'SEA');
INSERT INTO waterbodies (name, navarea, kind) VALUES ('Arabian Sea',   'VIII',  'SEA');
INSERT INTO waterbodies (name, navarea, kind) VALUES ('Bay of Bengal',   'VIII',  'SEA');
INSERT INTO waterbodies (name, navarea, kind) VALUES ('Andaman Sea',   'XI',  'SEA');
INSERT INTO waterbodies (name, navarea, kind) VALUES ('South China Sea',   'XI',  'SEA');
INSERT INTO waterbodies (name, navarea, kind) VALUES ('East China Sea',   'XI',  'SEA');

/* COUNTRIES_WATERBODY (20 rows) */
INSERT INTO countries_waterbody (countries_id, waterbody_id) VALUES (1, 1);  -- Poland - Baltic
INSERT INTO countries_waterbody VALUES (2, 2);                                -- Germany - North
INSERT INTO countries_waterbody VALUES (2, 1);                                -- Germany - Baltic
INSERT INTO countries_waterbody VALUES (3, 3);                                -- UK - Atlantic
INSERT INTO countries_waterbody VALUES (3, 2);                                -- UK - North
INSERT INTO countries_waterbody VALUES (4, 2);                                -- Netherlands - North Sea
INSERT INTO countries_waterbody VALUES (5, 3);                                -- Spain - North Atlantic
INSERT INTO countries_waterbody VALUES (5, 4);                                -- Spain - Mediterranean
INSERT INTO countries_waterbody VALUES (6, 4);                                -- Italy - Mediterranean
INSERT INTO countries_waterbody VALUES (7, 4);                                -- Greece - Mediterranean
INSERT INTO countries_waterbody VALUES (8, 3);                                -- US - Atlantic
INSERT INTO countries_waterbody VALUES (9, 9);                                -- China - South China
INSERT INTO countries_waterbody VALUES (9, 10);                                -- China - East China
INSERT INTO countries_waterbody VALUES (10, 9);                                -- Singapore - South China

/* SHIPS (20 rows) */
INSERT INTO ships (imo_number, name, flag_country, producer, cargo_capacity_t, crew_capacity, ownership_status) VALUES
('9500001', 'Baltic Star',         'Poland',        'Meyer Werft',              65000.000, 22, 'OWNED');
INSERT INTO ships VALUES ('9500002', 'Northern Light',      'Norway',        'Hudong-Zhonghua',          75000.000, 25, 'RENTED');
INSERT INTO ships VALUES ('9500003', 'Atlantic Breeze',     'Germany',       'Meyer Werft',              80000.000, 24, 'OWNED');
INSERT INTO ships VALUES ('9500004', 'Mediterranean Queen', 'Italy',         'Fincantieri',              70000.000, 26, 'OWNED');
INSERT INTO ships VALUES ('9500005', 'Pacific Trader',      'China',         'CSIC',                     90000.000, 28, 'RENTED');
INSERT INTO ships VALUES ('9500006', 'Ocean Voyager',       'United States', 'General Dynamics NASSCO',  85000.000, 30, 'OWNED');
INSERT INTO ships VALUES ('9500007', 'Southern Cross',      'Australia',     'Hyundai Heavy Industries', 78000.000, 23, 'RENTED');
INSERT INTO ships VALUES ('9500008', 'Sea Horizon',         'Singapore',     'Samsung Heavy Industries', 72000.000, 21, 'OWNED');
INSERT INTO ships VALUES ('9500009', 'Cape Pioneer',        'South Africa',  'Daewoo Shipbuilding',      82000.000, 27, 'RENTED');
INSERT INTO ships VALUES ('9500010', 'Global Carrier',      'United Kingdom','Mitsubishi Heavy',         95000.000, 32, 'OWNED');
INSERT INTO ships VALUES ('9500011', 'Polar Spirit',        'Norway',        'Meyer Werft',              76000.000, 24, 'RENTED');
INSERT INTO ships VALUES ('9500012', 'Ocean Explorer',      'Germany',       'Meyer Werft',              88000.000, 26, 'OWNED');
INSERT INTO ships VALUES ('9500013', 'Atlantic Trader',     'United Kingdom','Fincantieri',              83000.000, 25, 'OWNED');
INSERT INTO ships VALUES ('9500014', 'Pacific Horizon',     'United States', 'General Dynamics NASSCO',  91000.000, 29, 'RENTED');
INSERT INTO ships VALUES ('9500015', 'Eastern Star',        'China',         'CSIC',                     87000.000, 27, 'OWNED');
INSERT INTO ships VALUES ('9500016', 'Equator Runner',      'Brazil',        'Hyundai Heavy Industries', 79000.000, 23, 'RENTED');
INSERT INTO ships VALUES ('9500017', 'Cape Voyager',        'South Africa',  'Daewoo Shipbuilding',      81000.000, 22, 'OWNED');
INSERT INTO ships VALUES ('9500018', 'Coral Reef',          'Australia',     'Hyundai Heavy Industries', 82000.000, 24, 'RENTED');
INSERT INTO ships VALUES ('9500019', 'Strait Navigator',    'Singapore',     'Samsung Heavy Industries', 70000.000, 20, 'OWNED');
INSERT INTO ships VALUES ('9500020', 'Baltic Carrier',      'Poland',        'Meyer Werft',              64000.000, 21, 'OWNED');


/* CLIENTS (20 rows) */
INSERT INTO clients (name, billing_address, contract_valid_from, contract_valid_to) VALUES
('Baltic Logistics Ltd.',        'ul. Portowa 1, 80-001 Gdańsk, Poland',           '2022-01-01', '2026-12-31');
INSERT INTO clients VALUES ('Nordic Shipping AS',           'Bryggegata 5, 0250 Oslo, Norway',                '2021-06-01', '2025-05-31');
INSERT INTO clients VALUES ('Rhine Trade GmbH',             'Hafenstrasse 10, 20457 Hamburg, Germany',        '2023-03-01', '2027-03-01');
INSERT INTO clients VALUES ('Mediterranean Importers SRL',  'Via Porto 21, 80100 Napoli, Italy',              '2020-09-01', '2025-08-31');
INSERT INTO clients VALUES ('Atlantic Partners Inc.',       '200 Harbor Dr, Newark, NJ, USA',                 '2022-04-15', '2028-04-14');
INSERT INTO clients VALUES ('Pacific Retail Co.',           'Minato 3-1, Tokyo, Japan',                       '2021-11-01', '2026-10-31');
INSERT INTO clients VALUES ('Iberia Foods SA',              'Calle Mar 4, 11001 Cádiz, Spain',                '2023-01-01', '2027-12-31');
INSERT INTO clients VALUES ('South Seas Export Pte Ltd.',   '10 Harbourfront Walk, Singapore',                '2022-07-01', '2027-06-30');
INSERT INTO clients VALUES ('Cape Commodities Pty Ltd.',    'Breakwater Blvd, Cape Town, South Africa',       '2020-02-01', '2025-02-01');
INSERT INTO clients VALUES ('Down Under Mining Ltd.',       '1 Wharf Rd, Newcastle NSW, Australia',           '2023-05-01', '2028-05-01');
INSERT INTO clients VALUES ('Nordic Metals GmbH',           'Hafenallee 3, 20457 Hamburg, Germany',           '2021-03-01', '2025-03-01');
INSERT INTO clients VALUES ('Euro Grain BV',                'Maasboulevard 10, 3011 Rotterdam, Netherlands',  '2022-02-01', '2027-02-01');
INSERT INTO clients VALUES ('Pacific Manufacturing Co.',    '500 Bay St, San Francisco, CA, USA',             '2020-01-01', '2025-12-31');
INSERT INTO clients VALUES ('Shanghai Trade Corp',          'Pudong Avenue 88, Shanghai, China',              '2023-05-01', '2028-04-30');
INSERT INTO clients VALUES ('Lion City Foods Pte Ltd.',     'Port Road 2, Singapore',                          '2022-09-01', '2027-08-31');
INSERT INTO clients VALUES ('Rio Minerals SA',              'Av. Atlantica 100, Rio de Janeiro, Brazil',      '2021-10-01', '2026-09-30');
INSERT INTO clients VALUES ('Cape Steel Ltd.',              'Harbour Rd 4, Cape Town, South Africa',          '2019-06-01', '2024-06-01');
INSERT INTO clients VALUES ('Southern Energy Pty Ltd.',     'Dockside Ave 12, Sydney NSW, Australia',         '2023-01-01', '2028-01-01');
INSERT INTO clients VALUES ('Baltic Timber Sp. z o.o.',     'Nabrzeże 7, 80-001 Gdańsk, Poland',              '2022-03-01', '2027-03-01');
INSERT INTO clients VALUES ('TransAtlantic Lines Ltd.',     'Harbour St 9, London, United Kingdom',           '2021-11-01', '2026-10-31');

/* ORDERS (20 rows) */
INSERT INTO orders (client_code, status, order_placement_date) VALUES (1,  'COMPLETED',   '2024-01-05 10:15:00');
INSERT INTO orders VALUES (2,  'COMPLETED',   '2024-02-02 09:30:00');
INSERT INTO orders VALUES (3,  'IN PROGRESS', '2024-03-12 11:45:00');
INSERT INTO orders VALUES (4,  'IN PROGRESS', '2024-04-08 14:20:00');
INSERT INTO orders VALUES (5,  'COMPLETED',   '2024-01-20 08:05:00');
INSERT INTO orders VALUES (6,  'NOT STARTED', '2024-05-01 16:10:00');
INSERT INTO orders VALUES (7,  'IN PROGRESS', '2024-02-18 09:55:00');
INSERT INTO orders VALUES (8,  'NOT STARTED', '2024-06-03 12:40:00');
INSERT INTO orders VALUES (9,  'COMPLETED',   '2024-03-05 07:25:00');
INSERT INTO orders VALUES (10, 'CANCELED',    '2024-01-30 15:00:00');
INSERT INTO orders VALUES (11, 'COMPLETED',   '2024-02-10 09:10:00');
INSERT INTO orders VALUES (12, 'IN PROGRESS', '2024-02-15 16:20:00');
INSERT INTO orders VALUES (13, 'COMPLETED',   '2024-03-01 11:00:00');
INSERT INTO orders VALUES (14, 'IN PROGRESS', '2024-03-22 13:45:00');
INSERT INTO orders VALUES (15, 'NOT STARTED', '2024-04-05 08:30:00');
INSERT INTO orders VALUES (16, 'IN PROGRESS', '2024-04-18 10:15:00');
INSERT INTO orders VALUES (17, 'COMPLETED',   '2024-05-02 14:50:00');
INSERT INTO orders VALUES (18, 'NOT STARTED', '2024-05-20 09:05:00');
INSERT INTO orders VALUES (19, 'IN PROGRESS', '2024-06-10 15:25:00');
INSERT INTO orders VALUES (20, 'CANCELED',    '2024-06-18 12:10:00');

/* CRUISES (20 rows) */
INSERT INTO cruises (ship_number, etd, eta, atd, ata, status) VALUES 
('9500001', '2024-01-10 08:00:00', '2024-01-15 06:00:00', '2024-01-10 08:15:00', '2024-01-15 06:30:00', 'FINISHED');
INSERT INTO cruises VALUES ('9500002', '2024-02-01 09:00:00', '2024-02-05 18:00:00', '2024-02-01 09:05:00', '2024-02-05 18:20:00', 'FINISHED');
INSERT INTO cruises VALUES ('9500003', '2024-03-10 06:00:00', '2024-03-18 12:00:00', '2024-03-10 06:10:00', '2024-03-18 12:45:00', 'FINISHED');
INSERT INTO cruises VALUES ('9500004', '2024-04-02 07:00:00', '2024-04-10 09:00:00', '2024-04-02 07:20:00', '2024-04-10 09:25:00', 'FINISHED');
INSERT INTO cruises VALUES ('9500005', '2024-05-15 10:00:00', '2024-05-25 15:00:00', '2024-05-15 10:05:00', '2024-05-25 15:40:00', 'IN PROGRESS');
INSERT INTO cruises VALUES ('9500006', '2024-06-01 12:00:00', '2024-06-12 18:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500007', '2024-06-20 05:00:00', '2024-07-01 08:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500008', '2024-07-05 09:00:00', '2024-07-15 21:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500009', '2024-08-01 06:00:00', '2024-08-10 11:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500010', '2024-09-10 10:00:00', '2024-09-20 16:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500011', '2024-10-01 08:00:00', '2024-10-10 18:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500012', '2024-10-15 09:00:00', '2024-10-25 20:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500013', '2024-11-01 06:00:00', '2024-11-12 14:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500014', '2024-11-20 07:00:00', '2024-11-30 19:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500015', '2024-12-05 10:00:00', '2024-12-15 21:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500016', '2025-01-10 08:00:00', '2025-01-20 18:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500017', '2025-01-25 09:00:00', '2025-02-05 20:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500018', '2025-02-10 07:00:00', '2025-02-20 19:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500019', '2025-03-01 06:00:00', '2025-03-11 16:00:00', NULL, NULL, 'PLANNED');
INSERT INTO cruises VALUES ('9500019', '2025-03-20 10:00:00', '2025-03-30 22:00:00', NULL, NULL, 'PLANNED');

/* CREW MEMBERS (20 rows) */
INSERT INTO crew_members (name, surname, email, country_id, date_of_birth, contract_termination, rank) VALUES 
('Jan',     'Kowalski', 'jan.kowalski@example.com',      1, '1985-03-12', '2027-12-31', 'Captain');
INSERT INTO crew_members VALUES ('Anna',    'Nowak',    'anna.nowak@example.com',        1, '1990-07-25', '2026-06-30', 'First Officer');
INSERT INTO crew_members VALUES ('Hans',    'Mueller',  'hans.mueller@example.com',      2, '1982-11-05', '2028-03-31', 'Chief Engineer');
INSERT INTO crew_members VALUES ('Claudia', 'Schmidt',  'claudia.schmidt@example.com',   2, '1988-02-18', '2026-12-31', 'Second Officer');
INSERT INTO crew_members VALUES ('John',    'Smith',    'john.smith@example.com',        3, '1979-09-09', '2025-09-09', 'Bosun');
INSERT INTO crew_members VALUES ('Emily',   'Brown',    'emily.brown@example.com',       3, '1992-01-30', '2027-01-30', 'Deckhand');
INSERT INTO crew_members VALUES ('Pieter',  'Jensen', 'pieter.devries@example.com',    4, '1986-04-14', '2028-04-14', 'Chief Officer');
INSERT INTO crew_members VALUES ('Sara',    'Janssen',  'sara.janssen@example.com',      4, '1993-08-20', '2029-08-20', 'Electrician');
INSERT INTO crew_members VALUES ('Michael', 'Johnson',  'michael.johnson@example.com',   5, '1987-05-02', '2026-05-02', 'Able Seaman');
INSERT INTO crew_members VALUES ('Lisa',    'Taylor',   'lisa.taylor@example.com',       5, '1995-12-11', '2030-12-11', 'Third Officer');
INSERT INTO crew_members VALUES ('Li',      'Wei',      'li.wei@example.com',            6, '1984-04-10', '2028-04-10', 'Second Engineer');
INSERT INTO crew_members VALUES ('Wang',    'Fang',     'wang.fang@example.com',         6, '1989-09-19', '2029-09-19', 'Motorman');
INSERT INTO crew_members VALUES ('Amir',    'Rahman',   'amir.rahman@example.com',       7, '1983-01-22', '2027-01-22', 'Chief Cook');
INSERT INTO crew_members VALUES ('Nur',     'Aisyah',   'nur.aisyah@example.com',        7, '1991-06-03', '2028-06-03', 'Steward');
INSERT INTO crew_members VALUES ('Joao',    'Silva',    'joao.silva@example.com',        8, '1980-02-15', '2026-02-15', 'Deck Cadet');
INSERT INTO crew_members VALUES ('Maria',   'Santos',   'maria.santos@example.com',      8, '1994-07-28', '2029-07-28', 'Radio Officer');
INSERT INTO crew_members VALUES ('Thabo',   'Dlamini',  'thabo.dlamini@example.com',     9, '1985-10-05', '2027-10-05', 'Boatswain');
INSERT INTO crew_members VALUES ('Naledi',  'Khumalo',  'naledi.khumalo@example.com',    9, '1993-03-14', '2028-03-14', 'Second Mate');
INSERT INTO crew_members VALUES ('Jack',    'Wilson',   'jack.wilson@example.com',      10, '1981-11-30', '2026-11-30', 'Chief Mate');
INSERT INTO crew_members VALUES ('Olivia',  'Martin',   'olivia.martin@example.com',    10, '1996-09-07', '2030-09-07', 'Fourth Officer');


/* PORTS (20 rows) */
INSERT INTO ports (un_locode, waterbody_id, country_id, name) VALUES ('PL GDN', 1,  1,  'Gdansk');          -- Poland / Baltic Sea
INSERT INTO ports VALUES ('PL SZZ', 1,  1,  'Szczecin');        -- Poland / Baltic Sea
INSERT INTO ports VALUES ('DE HAM', 2,  2,  'Hamburg');         -- Germany / North Sea
INSERT INTO ports VALUES ('DE BRE', 2,  2,  'Bremen');          -- Germany / North Sea
INSERT INTO ports VALUES ('GB LON', 2,  3,  'London');          -- UK / North Sea approach
INSERT INTO ports VALUES ('GB LIV', 3,  3,  'Liverpool');       -- UK / North Atlantic
INSERT INTO ports VALUES ('NL RTM', 2,  4,  'Rotterdam');       -- Netherlands / North Sea
INSERT INTO ports VALUES ('NL AMS', 2,  4,  'Amsterdam');       -- Netherlands / North Sea
INSERT INTO ports VALUES ('ES BCN', 4,  5,  'Barcelona');       -- Spain / Mediterranean
INSERT INTO ports VALUES ('ES CAD', 3,  5,  'Cadiz');           -- Spain / Atlantic coast
INSERT INTO ports VALUES ('IT NAP', 4,  6,  'Naples');          -- Italy / Mediterranean
INSERT INTO ports VALUES ('IT TRS', 4,  6,  'Trieste');         -- Italy / Mediterranean (Adriatic)
INSERT INTO ports VALUES ('GR PIR', 4,  7,  'Piraeus');         -- Greece / Mediterranean
INSERT INTO ports VALUES ('GR SKG', 4,  7,  'Thessaloniki');    -- Greece / Mediterranean
INSERT INTO ports VALUES ('US NYC', 3,  8,  'New York');        -- USA / North Atlantic
INSERT INTO ports VALUES ('US MIA', 3,  8,  'Miami');           -- USA / North Atlantic (Caribbean approach)
INSERT INTO ports VALUES ('CN SHA',10,  9,  'Shanghai');        -- China / East China Sea
INSERT INTO ports VALUES ('CN HKG', 9,  9,  'Hong Kong');       -- China / South China Sea
INSERT INTO ports VALUES ('SG SIN', 9, 10,  'Singapore');       -- Singapore / South China Sea
INSERT INTO ports VALUES ('SG JUR', 9, 10,  'Jurong');          -- Singapore / South China Sea


/* PORT CALLS (20 rows) */
INSERT INTO port_calls (cruise_id, seq_no, port_code, etd, eta, atd, ata, status) VALUES
(1, 1, 'PL GDN', '2024-01-10 08:00:00', '2024-01-10 20:00:00', '2024-01-10 08:15:00', '2024-01-10 19:45:00', 'FINISHED');
INSERT INTO port_calls VALUES (1, 2, 'US NYC', '2024-01-12 09:00:00', '2024-01-12 21:00:00', '2024-01-12 09:10:00', '2024-01-12 20:55:00', 'FINISHED');
INSERT INTO port_calls VALUES (2, 1, 'DE HAM', '2024-02-01 09:00:00', '2024-02-01 20:00:00', '2024-02-01 09:05:00', '2024-02-01 19:50:00', 'FINISHED');
INSERT INTO port_calls VALUES (2, 2, 'GR PIR', '2024-02-03 08:00:00', '2024-02-03 19:00:00', '2024-02-03 08:10:00', '2024-02-03 18:55:00', 'FINISHED'); 
INSERT INTO port_calls VALUES (3, 1, 'NL RTM', '2024-03-10 06:00:00', '2024-03-10 18:00:00', '2024-03-10 06:20:00', '2024-03-10 17:50:00', 'FINISHED');
INSERT INTO port_calls VALUES (3, 2, 'CN SHA', '2024-03-15 07:00:00', '2024-03-15 19:00:00', '2024-03-15 07:10:00', '2024-03-15 18:45:00', 'FINISHED'); 
INSERT INTO port_calls VALUES (4, 1, 'ES BCN', '2024-04-02 07:00:00', '2024-04-02 19:00:00', '2024-04-02 07:20:00', '2024-04-02 18:55:00', 'FINISHED');
INSERT INTO port_calls VALUES (4, 2, 'GB LIV', '2024-04-07 09:00:00', '2024-04-07 21:00:00', '2024-04-07 09:10:00', '2024-04-07 20:40:00', 'FINISHED'); 
INSERT INTO port_calls VALUES (5, 1, 'IT NAP', '2024-05-15 10:00:00', '2024-05-15 22:00:00', '2024-05-15 10:15:00', '2024-05-15 21:40:00', 'IN PROGRESS');
INSERT INTO port_calls VALUES (5, 2, 'US NYC', '2024-05-22 08:00:00', '2024-05-22 20:00:00', NULL,  NULL, 'PLANNED');
INSERT INTO port_calls VALUES (6, 1, 'NL AMS', '2024-06-01 12:00:00', '2024-06-01 22:00:00', NULL, NULL, 'PLANNED');
INSERT INTO port_calls VALUES (6, 2, 'US NYC', '2024-06-03 08:00:00', '2024-06-03 18:00:00', NULL, NULL, 'PLANNED');
INSERT INTO port_calls VALUES (7, 1, 'ES CAD', '2024-06-20 05:00:00', '2024-06-20 15:00:00', NULL, NULL, 'PLANNED');
INSERT INTO port_calls VALUES (7, 2, 'US MIA', '2024-06-22 06:00:00', '2024-06-22 18:00:00', NULL, NULL, 'PLANNED');
INSERT INTO port_calls VALUES (8, 1, 'IT TRS', '2024-07-05 09:00:00', '2024-07-05 21:00:00', NULL, NULL, 'PLANNED');
INSERT INTO port_calls VALUES (8, 2, 'GR PIR', '2024-07-08 10:00:00', '2024-07-08 20:00:00', NULL, NULL, 'PLANNED');
INSERT INTO port_calls VALUES (9, 1, 'GR PIR', '2024-08-01 06:00:00', '2024-08-01 18:00:00', NULL, NULL, 'PLANNED');
INSERT INTO port_calls VALUES (9, 2, 'SG SIN', '2024-08-04 07:00:00', '2024-08-04 19:00:00', NULL, NULL, 'PLANNED');
INSERT INTO port_calls VALUES (10, 1, 'SG SIN', '2024-09-10 10:00:00', '2024-09-10 22:00:00', NULL, NULL, 'PLANNED');
INSERT INTO port_calls VALUES (10, 2, 'CN HKG', '2024-09-15 08:00:00', '2024-09-15 20:00:00', NULL, NULL, 'PLANNED');



/* MAINTENANCE EVENTS (20 rows) */
INSERT INTO maintenance_events (ship_number, cause, start, [end], status) VALUES ('9500001', 'Annual hull inspection', '2023-03-01', '2023-03-03', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500002', 'Engine overhaul',                 '2023-04-10', '2023-04-20', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500003', 'Navigation system upgrade',       '2023-05-05', '2023-05-10', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500004', 'Dry dock painting',               '2023-06-15', '2023-06-25', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500005', 'Propeller inspection',            '2023-07-01', '2023-07-05', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500006', 'Safety equipment replacement',    '2023-08-10', '2023-08-15', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500007', 'Ballast water system cleaning',   '2023-09-01', '2023-09-04', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500008', 'Radar calibration',               '2023-10-05', '2023-10-07', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500009', 'Fuel system inspection',          '2023-11-12', '2023-11-16', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500010', 'Planned dry dock',                '2024-01-05', NULL,         'PLANNED');
INSERT INTO maintenance_events VALUES ('9500011', 'Generator inspection',            '2024-02-01', '2024-02-03', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500012', 'Hull cleaning',                   '2024-02-10', '2024-02-12', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500013', 'Lifeboat drill',                  '2024-03-05', '2024-03-05', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500014', 'Bridge equipment upgrade',        '2024-03-15', '2024-03-20', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500015', 'Propeller balancing',             '2024-04-01', '2024-04-04', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500016', 'Ballast tank inspection',         '2024-04-20', '2024-04-23', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500017', 'Fuel tank cleaning',              '2024-05-02', '2024-05-07', 'FINISHED');
INSERT INTO maintenance_events VALUES ('9500018', 'Planned class survey',            '2024-06-01', NULL,         'PLANNED');
INSERT INTO maintenance_events VALUES ('9500019', 'Emergency generator test',        '2024-06-10', NULL,         'PLANNED');
INSERT INTO maintenance_events VALUES ('9500020', 'Dry dock scheduled',              '2024-07-01', NULL,         'PLANNED');


/* INCIDENTS (20 rows) */
INSERT INTO incidents (cruise_id, cause, start, [end], delay_min, severity) VALUES 
(1, 'Heavy fog near departure port',  '2024-01-10 07:30:00', '2024-01-10 08:30:00',  60, 'MINOR');
INSERT INTO incidents VALUES (1, 'Cargo loading delay',            '2024-01-12 08:00:00', '2024-01-12 10:00:00', 120, 'MINOR');
INSERT INTO incidents VALUES (2, 'Engine temperature alarm',       '2024-02-02 13:00:00', '2024-02-02 15:30:00', 150, 'MAJOR');
INSERT INTO incidents VALUES (2, 'Berth congestion at London',     '2024-02-03 17:00:00', '2024-02-03 19:00:00', 120, 'MINOR');
INSERT INTO incidents VALUES (3, 'Storm in North Atlantic',        '2024-03-12 00:00:00', '2024-03-13 06:00:00', 360, 'MAJOR');
INSERT INTO incidents VALUES (3, 'Minor technical inspection',     '2024-03-15 08:00:00', '2024-03-15 09:30:00',  90, 'MINOR');
INSERT INTO incidents VALUES (4, 'Cargo shift in hold',            '2024-04-06 03:00:00', '2024-04-06 05:00:00', 120, 'MAJOR');
INSERT INTO incidents VALUES (4, 'Medical evacuation by helicopter','2024-04-07 10:00:00','2024-04-07 12:30:00', 150, 'CRITICAL');
INSERT INTO incidents VALUES (5, 'Strong headwinds',               '2024-05-18 06:00:00', '2024-05-18 12:00:00', 360, 'MAJOR');
INSERT INTO incidents VALUES (5, 'Berthing delay in Sydney',       '2024-05-22 18:00:00', '2024-05-22 20:00:00', 120, 'MINOR');
INSERT INTO incidents VALUES (6, 'Delayed pilot boarding',         '2024-06-01 11:00:00', '2024-06-01 12:30:00',  90, 'MINOR');
INSERT INTO incidents VALUES (6, 'Minor engine vibration',         '2024-06-03 10:00:00', '2024-06-03 12:00:00', 120, 'MINOR');
INSERT INTO incidents VALUES (7, 'Fog on departure',               '2024-06-20 04:00:00', '2024-06-20 06:00:00', 120, 'MINOR');
INSERT INTO incidents VALUES (7, 'Cargo documentation issue',      '2024-06-22 05:00:00', '2024-06-22 07:30:00', 150, 'MAJOR');
INSERT INTO incidents VALUES (8, 'Heavy swell in Pacific',         '2024-07-07 00:00:00', '2024-07-07 06:00:00', 360, 'MAJOR');
INSERT INTO incidents VALUES (8, 'Minor medical case',             '2024-07-08 11:00:00', '2024-07-08 12:00:00',  60, 'MINOR');
INSERT INTO incidents VALUES (9, 'Strike at destination port',     '2024-08-04 06:00:00', '2024-08-04 12:00:00', 360, 'CRITICAL');
INSERT INTO incidents VALUES (9, 'Navigation buoy unlit',          '2024-08-01 23:00:00', '2024-08-02 01:00:00', 120, 'MINOR');
INSERT INTO incidents VALUES (10,'Tugboat unavailability',         '2024-09-10 09:00:00', '2024-09-10 11:00:00', 120, 'MAJOR');
INSERT INTO incidents VALUES (10,'Strong crosswinds at berth',     '2024-09-15 07:00:00', '2024-09-15 09:30:00', 150, 'MAJOR');


/* CRUISES_WATERBODY (20 rows) */
INSERT INTO cruises_waterbody (cruise_id, waterbody_id) VALUES (1, 1);  -- Baltic Sea
INSERT INTO cruises_waterbody VALUES (1, 2);                            -- North Sea
INSERT INTO cruises_waterbody VALUES (1, 3);                            -- North Atlantic
INSERT INTO cruises_waterbody VALUES (2, 2);                            -- North Sea
INSERT INTO cruises_waterbody VALUES (2, 3);                            -- North Atlantic
INSERT INTO cruises_waterbody VALUES (2, 4);                            -- Mediterranean Sea
INSERT INTO cruises_waterbody VALUES (3, 2);                            -- North Sea
INSERT INTO cruises_waterbody VALUES (3, 3);                            -- North Atlantic
INSERT INTO cruises_waterbody VALUES (3, 4);                            -- Mediterranean Sea
INSERT INTO cruises_waterbody VALUES (3, 5);                            -- Red Sea
INSERT INTO cruises_waterbody VALUES (3, 6);                            -- Arabian Sea
INSERT INTO cruises_waterbody VALUES (3, 7);                            -- Bay of Bengal
INSERT INTO cruises_waterbody VALUES (3, 8);                            -- Andaman Sea
INSERT INTO cruises_waterbody VALUES (3, 9);                            -- South China Sea
INSERT INTO cruises_waterbody VALUES (3,10);                            -- East China Sea
INSERT INTO cruises_waterbody VALUES (4, 4);                            -- Mediterranean Sea
INSERT INTO cruises_waterbody VALUES (4, 3);                            -- North Atlantic
INSERT INTO cruises_waterbody VALUES (5, 4);                            -- Mediterranean Sea
INSERT INTO cruises_waterbody VALUES (5, 3);                            -- North Atlantic
INSERT INTO cruises_waterbody VALUES (9, 9);                            -- South China Sea

/* CREW_ASSIGNMENT (20 rows) */
INSERT INTO crew_assignment (crew_id, cruise_id) VALUES (1,  1);
INSERT INTO crew_assignment VALUES (2,  1);
INSERT INTO crew_assignment VALUES (3,  2);
INSERT INTO crew_assignment VALUES (4,  2);
INSERT INTO crew_assignment VALUES (5,  3);
INSERT INTO crew_assignment VALUES (6,  3);
INSERT INTO crew_assignment VALUES (7,  4);
INSERT INTO crew_assignment VALUES (8,  4);
INSERT INTO crew_assignment VALUES (9,  5);
INSERT INTO crew_assignment VALUES (10, 5);
INSERT INTO crew_assignment VALUES (11, 6);
INSERT INTO crew_assignment VALUES (12, 6);
INSERT INTO crew_assignment VALUES (13, 7);
INSERT INTO crew_assignment VALUES (14, 7);
INSERT INTO crew_assignment VALUES (15, 8);
INSERT INTO crew_assignment VALUES (16, 8);
INSERT INTO crew_assignment VALUES (17, 9);
INSERT INTO crew_assignment VALUES (18, 9);
INSERT INTO crew_assignment VALUES (19,10);
INSERT INTO crew_assignment VALUES (20,10);


/* CARGO (20 rows) */
INSERT INTO cargo (order_id, cruise_id, load_seqno, discharge_seqno, planned_weight_t, transported_weight_t, status)
VALUES (1,  1, 1, 2, 1200.000, 1180.000, 'DELIVERED');
INSERT INTO cargo VALUES (2,  1, 1, 2,  800.000,  790.000, 'DELIVERED');
INSERT INTO cargo VALUES (3,  2, 1, 2,  600.000,  590.000, 'DELIVERED');
INSERT INTO cargo VALUES (4,  2, 1, 2,  900.000,  880.000, 'IN DELIVERY');
INSERT INTO cargo VALUES (5,  3, 1, 2, 1000.000,  990.000, 'DELIVERED');
INSERT INTO cargo VALUES (6,  3, 1, 2,  500.000,  495.000, 'IN DELIVERY');
INSERT INTO cargo VALUES (7,  4, 1, 2,  700.000,  690.000, 'DELIVERED');
INSERT INTO cargo VALUES (8,  4, 1, 2,  300.000,  295.000, 'IN DELIVERY');
INSERT INTO cargo VALUES (9,  5, 1, 2,  450.000,  440.000, 'DELIVERED');
INSERT INTO cargo VALUES (10, 5, 1, 2,  350.000,  345.000, 'CANCELED');
INSERT INTO cargo VALUES (11, 6, 1, 2,  600.000,  580.000, 'IN DELIVERY');
INSERT INTO cargo VALUES (12, 6, 1, 2,  750.000,  740.000, 'NOT STARTED');
INSERT INTO cargo VALUES (13, 7, 1, 2,  900.000,  890.000, 'IN DELIVERY');
INSERT INTO cargo VALUES (14, 7, 1, 2,  500.000,  480.000, 'NOT STARTED');
INSERT INTO cargo VALUES (15, 8, 1, 2,  650.000,  640.000, 'DELIVERED');
INSERT INTO cargo VALUES (16, 8, 1, 2,  400.000,  390.000, 'IN DELIVERY');
INSERT INTO cargo VALUES (17, 9, 1, 2,  550.000,  540.000, 'DELIVERED');
INSERT INTO cargo VALUES (18, 9, 1, 2,  300.000,  295.000, 'IN DELIVERY');
INSERT INTO cargo VALUES (19,10, 1, 2,  700.000,  690.000, 'IN DELIVERY');
INSERT INTO cargo VALUES (20,10, 1, 2,  250.000,  245.000, 'CANCELED');
