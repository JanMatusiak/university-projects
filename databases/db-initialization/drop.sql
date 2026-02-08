USE ShippingLineDB;
GO

/* DELETE ALL TABLES */

IF OBJECT_ID('dbo.cargo', 'U') IS NOT NULL
    DROP TABLE dbo.cargo;
GO

IF OBJECT_ID('dbo.crew_assignment', 'U') IS NOT NULL
    DROP TABLE dbo.crew_assignment;
GO

IF OBJECT_ID('dbo.incidents', 'U') IS NOT NULL
    DROP TABLE dbo.incidents;
GO

IF OBJECT_ID('dbo.maintenance_events', 'U') IS NOT NULL
    DROP TABLE dbo.maintenance_events;
GO

IF OBJECT_ID('dbo.port_calls', 'U') IS NOT NULL
    DROP TABLE dbo.port_calls;
GO

IF OBJECT_ID('dbo.cruises_waterbody', 'U') IS NOT NULL
    DROP TABLE dbo.cruises_waterbody;
GO

IF OBJECT_ID('dbo.countries_waterbody', 'U') IS NOT NULL
    DROP TABLE dbo.countries_waterbody;
GO

IF OBJECT_ID('dbo.ports', 'U') IS NOT NULL
    DROP TABLE dbo.ports;
GO

IF OBJECT_ID('dbo.cruises', 'U') IS NOT NULL
    DROP TABLE dbo.cruises;
GO

IF OBJECT_ID('dbo.orders', 'U') IS NOT NULL
    DROP TABLE dbo.orders;
GO

IF OBJECT_ID('dbo.crew_members', 'U') IS NOT NULL
    DROP TABLE dbo.crew_members;
GO

IF OBJECT_ID('dbo.ships', 'U') IS NOT NULL
    DROP TABLE dbo.ships;
GO

IF OBJECT_ID('dbo.clients', 'U') IS NOT NULL
    DROP TABLE dbo.clients;
GO

IF OBJECT_ID('dbo.waterbodies', 'U') IS NOT NULL
    DROP TABLE dbo.waterbodies;
GO

IF OBJECT_ID('dbo.countries', 'U') IS NOT NULL
    DROP TABLE dbo.countries;
GO
