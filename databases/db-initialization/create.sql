USE ShippingLineDB;
GO

CREATE TABLE ships (
    imo_number CHAR(7) PRIMARY KEY NOT NULL,
    name VARCHAR(128) NOT NULL,
    flag_country VARCHAR(64) NOT NULL,
    producer VARCHAR(128),
    cargo_capacity_t DECIMAL(12,3),
    crew_capacity INTEGER,
    ownership_status VARCHAR(6) NOT NULL,
    CHECK (imo_number LIKE '[0-9][0-9][0-9][0-9][0-9][0-9][0-9]'),
    CHECK (cargo_capacity_t >= 0), CHECK (crew_capacity >= 0), CHECK (ownership_status IN ('OWNED', 'RENTED'))
);

CREATE TABLE maintenance_events (
    id INTEGER IDENTITY(1,1) PRIMARY KEY,
    ship_number CHAR(7) REFERENCES ships ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
    cause VARCHAR(255) NOT NULL,
    start DATE,
    [end] DATE,
    status VARCHAR(11) NOT NULL,
    CHECK (start <= [end]), CHECK (status IN ('PLANNED', 'IN PROGRESS', 'FINISHED', 'CANCELED'))
);

CREATE TABLE cruises (
    id INTEGER IDENTITY(1,1) PRIMARY KEY,
    ship_number CHAR(7) REFERENCES ships ON UPDATE CASCADE NOT NULL,
    etd DATETIME2,
    eta DATETIME2,
    atd DATETIME2,
    ata DATETIME2,
    status VARCHAR(11) NOT NULL,
    CHECK (status IN ('PLANNED', 'IN PROGRESS', 'FINISHED', 'CANCELED'))
);

CREATE TABLE incidents (
    id INTEGER IDENTITY(1,1) PRIMARY KEY,
    cruise_id INTEGER REFERENCES cruises ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
    cause VARCHAR(255) NOT NULL,
    start DATETIME2,
    [end] DATETIME2,
    delay_min INTEGER,
    severity VARCHAR(8),
    CHECK ([end] >= start), CHECK (severity IN ('MINOR', 'MAJOR', 'CRITICAL'))
);

CREATE TABLE countries (
    id INTEGER IDENTITY(1,1) PRIMARY KEY,
    continent VARCHAR(32) NOT NULL,
    name VARCHAR(64) NOT NULL,
    area_m2 DECIMAL(18, 2),
    population INTEGER,
    CHECK (area_m2 > 0), CHECK (population > 0)
);

CREATE TABLE crew_members (
    id INTEGER IDENTITY(1,1) PRIMARY KEY,
    name VARCHAR(64) NOT NULL,
    surname VARCHAR(64) NOT NULL,
    email VARCHAR(320) NOT NULL,
    country_id INTEGER REFERENCES countries NOT NULL,
    date_of_birth DATE NOT NULL,
    contract_termination DATE NOT NULL,
    rank VARCHAR(64) NOT NULL,
    CHECK (date_of_birth < GETDATE()), CHECK (contract_termination >= date_of_birth), CHECK (email LIKE '%_@_%._%'), 
    CHECK (name NOT LIKE '%[^A-Za-z]%')
);

CREATE TABLE waterbodies (
    id INTEGER IDENTITY(1,1) PRIMARY KEY,
    name VARCHAR(128) NOT NULL,
    navarea VARCHAR(4),
    kind VARCHAR(5) NOT NULL,
    CHECK (kind IN ('SEA', 'LAKE', 'RIVER')) 
);

CREATE TABLE ports (
    un_locode CHAR(6) PRIMARY KEY,
    waterbody_id INTEGER REFERENCES waterbodies NOT NULL,
    country_id INTEGER REFERENCES countries NOT NULL,
    name VARCHAR(128) NOT NULL,
    CHECK (un_locode LIKE '[A-Za-z][A-Za-z] [A-Za-z][A-Za-z][A-Za-z]')
);

CREATE TABLE port_calls (
    cruise_id INTEGER REFERENCES cruises ON UPDATE CASCADE NOT NULL,
    seq_no INTEGER NOT NULL,
    port_code CHAR(6) REFERENCES ports ON UPDATE CASCADE NOT NULL,
    etd DATETIME2,
    eta DATETIME2,
    atd DATETIME2,
    ata DATETIME2,
    status VARCHAR(11) NOT NULL,
    CONSTRAINT PK_port_calls PRIMARY KEY (cruise_id, seq_no),
    CHECK (seq_no > 0), CHECK (etd > eta), CHECK (atd > ata), CHECK (status IN ('PLANNED', 'IN PROGRESS', 'FINISHED', 'CANCELED')) 
);  

CREATE TABLE clients (
    client_code INTEGER IDENTITY(1,1) PRIMARY KEY,
    name VARCHAR(128) NOT NULL,
    billing_address VARCHAR(128) NOT NULL,
    contract_valid_from DATE NOT NULL,
    contract_valid_to DATE NOT NULL, 
    CHECK (contract_valid_to >= contract_valid_from)
);

CREATE TABLE orders (
    id INTEGER IDENTITY(1,1) PRIMARY KEY,
    client_code INTEGER REFERENCES clients ON UPDATE CASCADE NOT NULL,
    status VARCHAR(11) NOT NULL,
    order_placement_date DATETIME2 NOT NULL,
    CHECK (status IN ('COMPLETED', 'IN PROGRESS', 'NOT STARTED', 'CANCELED')) 
);

CREATE TABLE cargo (
    id INTEGER IDENTITY(1,1) PRIMARY KEY,
    order_id INTEGER REFERENCES orders ON UPDATE CASCADE NOT NULL,
    cruise_id INTEGER NOT NULL,
    load_seqno INTEGER NOT NULL,
    discharge_seqno INTEGER,
    planned_weight_t DECIMAL(18, 3),
    transported_weight_t DECIMAL (18, 3),
    status VARCHAR(11) NOT NULL,
    CONSTRAINT FK_cargo_load FOREIGN KEY (cruise_id, load_seqno)
        REFERENCES port_calls (cruise_id, seq_no),
    CONSTRAINT FK_cargo_discharge FOREIGN KEY (cruise_id, discharge_seqno)
        REFERENCES port_calls (cruise_id, seq_no),
    CHECK (discharge_seqno > load_seqno), CHECK (planned_weight_t > 0), CHECK (transported_weight_t > 0), CHECK (status IN ('DELIVERED', 'IN DELIVERY', 'NOT STARTED', 'CANCELED'))
);

CREATE TABLE cruises_waterbody (
    cruise_id INTEGER REFERENCES cruises ON UPDATE CASCADE NOT NULL,
    waterbody_id INTEGER REFERENCES waterbodies NOT NULL,
    CONSTRAINT PK_cruises_waterbody PRIMARY KEY (cruise_id, waterbody_id)
);

CREATE TABLE countries_waterbody (
    countries_id INTEGER REFERENCES countries NOT NULL,
    waterbody_id INTEGER REFERENCES waterbodies NOT NULL,
    CONSTRAINT PK_countries_waterbody PRIMARY KEY (countries_id, waterbody_id)   
);

CREATE TABLE crew_assignment (
    crew_id INTEGER REFERENCES crew_members ON UPDATE CASCADE NOT NULL,
    cruise_id INTEGER REFERENCES cruises ON UPDATE CASCADE NOT NULL,
    CONSTRAINT PK_crew_assignment PRIMARY KEY (crew_id, cruise_id)
);

