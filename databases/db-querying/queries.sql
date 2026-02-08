USE ShippingLineDB;
GO

-- a helper view that displays the number of incidents per cruise
CREATE VIEW incidents_per_cruise AS 
SELECT
    cruise_id, 
    COUNT(*) AS incident_count 
FROM incidents 
GROUP BY cruise_id;

-- 1) VIEW + ORDER BY 
-- Purpose: Rank cruises by number of incidents (highest incident_count first)
-- Business need: Identify the most problematic cruises for investigation, reporting, and corrective actions
SELECT * 
FROM incidents_per_cruise 
ORDER BY incident_count DESC;

-- 2) JOIN + ORDER BY 
-- Purpose: Show cruises together with ship names and planned times, ordered by departure date.
-- Business need: Provide a scheduling overview and make it easy to review the most recent and next cruises.
SELECT c.id AS cruise_id, s.name, c.etd, c.eta 
FROM cruises AS c
JOIN ships s ON s.imo_number = c.ship_number 
ORDER BY c.etd DESC; 

-- 3) AGGREGATE + GROUP BY 
-- Purpose: Count how many cruises exist in each status (e.g., PLANNED / IN PROGRESS / FINISHED).
-- Business need: Track workload for planning resources and reporting progress.
SELECT status, COUNT(*) AS cruise_count
FROM cruises 
GROUP BY status;

-- 4) JOIN + GROUP BY
-- Purpose: For each ship, show crew members who worked on it, together with a cruise_id they participated in.
-- Business need: Trace who served on which vessel and on which specific voyage (staffing history / audits / planning).
SELECT s.imo_number, s.name AS ship_name, cr.id AS crew_id, cr.name, cr.surname, cr.rank, c.id AS cruise_id
FROM ships s
JOIN cruises c ON c.ship_number = s.imo_number
JOIN crew_assignment ca ON ca.cruise_id = c.id
JOIN crew_members cr ON cr.id = ca.crew_id
GROUP BY s.imo_number, s.name, cr.id, cr.name, cr.surname, cr.rank, c.id;

-- 5) SUBQUERY + AGGREGATE
-- Purpose: For each client, compute the total transported cargo weight across all their orders.
-- Business need: Measure customer weight to support key account management and revenue forecasting
SELECT cl.name AS client_name,
  COALESCE((
    SELECT SUM(ca.transported_weight_t)
    FROM orders o
    JOIN cargo ca ON ca.order_id = o.id
    WHERE o.client_code = cl.client_code
  ), 0) AS total_weight
FROM clients cl;

-- 6) JOIN + ORDER BY
-- Purpose: List all cruise port calls with port name and ETA, ordered chronologically per cruise.
-- Business need: Provide a route timeline for operational monitoring, reporting and analysis
SELECT c.id, p.name AS port_name, pc.eta
FROM cruises c
JOIN port_calls pc ON pc.cruise_id = c.id
JOIN ports p ON p.un_locode = pc.port_code
ORDER BY c.id, pc.eta;

-- 7) SUBQUERY + ORDER BY
-- Purpose: Find crew members who are not assigned to any cruise.
-- Business need: Detect underutilized staff (or incomplete data) for scheduling, cost control, and HR planning
INSERT INTO crew_members (name, surname, email, country_id, date_of_birth, contract_termination, rank) VALUES ('Jan', 'Matusiak', 'jan.matusiak.2006@gmail.com', 1, '2006-09-20', '2026-06-30', 'First Captain');
SELECT cm.id, cm.name, cm.surname, cm.rank
FROM crew_members cm
WHERE NOT EXISTS (
    SELECT 1
    FROM crew_assignment ca
    WHERE ca.crew_id = cm.id
)
ORDER BY cm.surname, cm.name;

-- 8) SUBQUERY + JOIN
-- Purpose: For each cruise, show the last port it called at 
-- Business need: Quick overview for reporting and operations wrap-up.
SELECT
    c.id AS cruise_id,
    p.name AS last_port_name,
    pc.eta AS last_eta
FROM cruises c
JOIN port_calls pc ON pc.cruise_id = c.id
JOIN ports p ON p.un_locode = pc.port_code
WHERE pc.seq_no = (
    SELECT MAX(pc2.seq_no)
    FROM port_calls pc2
    WHERE pc2.cruise_id = c.id
);

-- 9) SUBQUERY + JOIN
-- Purpose: List orders (with client) that have at least one cargo item not delivered yet
-- Business need: Identify “at-risk" or ongoing orders to prioritize follow-ups
SELECT
    o.id AS order_id,
    cl.name AS client_name,
    o.order_placement_date
FROM orders o
JOIN clients cl ON cl.client_code = o.client_code
WHERE EXISTS (
    SELECT 1
    FROM cargo ca
    WHERE ca.order_id = o.id
      AND ca.status IN ('IN DELIVERY', 'NOT STARTED')
);

-- 10) SUBQUERY + JOIN 
-- Purpose: For each client, show their most recent order 
-- Business need: Track customer activity to support relationship management and sales prioritization.
SELECT c.name, o.id AS order_id, o.order_placement_date 
FROM clients AS c 
JOIN orders o ON o.client_code = c.client_code 
WHERE o.order_placement_date = (
    SELECT MAX(o2.order_placement_date)
    FROM orders AS o2 
    WHERE o2.client_code = c.client_code 
);





