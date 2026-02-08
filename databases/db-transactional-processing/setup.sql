USE ShippingLineDB;
GO

INSERT INTO countries (continent, name, area_m2, population) VALUES ('Europe',        'Poland',         312679000000.00,   38000000);
INSERT INTO countries (continent, name, area_m2, population) VALUES ('Europe',        'Germany',        357022000000.00,   83000000);
INSERT INTO countries (continent, name, area_m2, population) VALUES ('Europe',        'United Kingdom', 243610000000.00,   67000000);

INSERT INTO waterbodies (name, navarea, kind) VALUES ('Baltic Sea',        'I',   'SEA');
INSERT INTO waterbodies (name, navarea, kind) VALUES ('North Sea',         'I',   'SEA');

INSERT INTO countries_waterbody (countries_id, waterbody_id) VALUES (1, 1);  -- Poland - Baltic
INSERT INTO countries_waterbody VALUES (2, 2);                                -- Germany - North
INSERT INTO countries_waterbody VALUES (2, 1);                                -- Germany - Baltic
INSERT INTO countries_waterbody VALUES (3, 2);                                -- UK - North

INSERT INTO clients (name, billing_address, contract_valid_from, contract_valid_to) VALUES
('Baltic Logistics Ltd.', 'ul. Portowa 1, 80-001 Gdańsk, Poland', '2022-01-01', '2026-12-31');

INSERT INTO orders (client_code, status, order_placement_date) VALUES (1,  'NOT STARTED',   '2026-01-23 12:00:00');

INSERT INTO ships (imo_number, name, flag_country, producer, cargo_capacity_t, crew_capacity, ownership_status) VALUES
('9500001', 'Baltic Star', 'Poland', 'Meyer Werft', 3000.000, 22, 'OWNED');

INSERT INTO cruises (ship_number, etd, eta, atd, ata, status) VALUES 
('9500001', '2026-01-26 08:00:00', '2026-01-31 06:00:00', NULL, NULL, 'PLANNED');

INSERT INTO ports (un_locode, waterbody_id, country_id, name) VALUES ('PL GDN', 1,  1,  'Gdansk'); -- Poland / Baltic Sea
INSERT INTO ports VALUES ('DE HAM', 2,  2,  'Hamburg'); -- Germany / North Sea
INSERT INTO ports VALUES ('GB LON', 2,  3,  'London'); -- UK / North Sea approach

INSERT INTO port_calls (cruise_id, seq_no, port_code, etd, eta, atd, ata, status) VALUES
(1, 1, 'PL GDN', '2026-01-26 08:00:00', NULL, NULL, NULL, 'PLANNED');
INSERT INTO port_calls VALUES (1, 2, 'DE HAM', '2026-01-28 09:00:00', '2026-01-28 0:00:00', NULL, NULL, 'PLANNED');
INSERT INTO port_calls VALUES (1, 3, 'GB LON', NULL, '2026-01-31 0:00:00', NULL, NULL, 'PLANNED');

INSERT INTO cargo (order_id, cruise_id, load_seqno, discharge_seqno, planned_weight_t, transported_weight_t, status)
VALUES (1, 1, 1, 3, 1200.000, NULL, 'NOT STARTED');
INSERT INTO cargo VALUES (1, 1, 1, 3,  800.000,  NULL, 'NOT STARTED');
INSERT INTO cargo VALUES (1, 1, 1, 3,  600.000,  NULL, 'NOT STARTED');