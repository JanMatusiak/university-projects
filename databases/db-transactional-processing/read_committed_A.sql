-- Session A
USE ShippingLineDB 
GO

SET TRANSACTION ISOLATION LEVEL READ COMMITTED
BEGIN TRANSACTION 

DECLARE @current_total_planned_weight_t DECIMAL(18,3) = 
(SELECT SUM(planned_weight_t) FROM cargo 
WHERE order_id = 1)

DECLARE @cargo_capacity_t DECIMAL(18, 3) =
(SELECT cargo_capacity_t FROM ships
WHERE imo_number = '9500001') 

DECLARE @available_capacity_t DECIMAL(18,3) = @cargo_capacity_t - @current_total_planned_weight_t 

DECLARE @requested_weight_t DECIMAL(18,3) = 400.00

PRINT CONCAT('A sees remaining = ', @available_capacity_t);
WAITFOR DELAY '00:00:10';

IF(@requested_weight_t <= @available_capacity_t)
BEGIN
    INSERT INTO cargo (order_id, cruise_id, load_seqno, discharge_seqno,
                       planned_weight_t, transported_weight_t, status)
    VALUES (1, 1, 1, 3, @requested_weight_t, NULL, 'NOT STARTED');

    PRINT 'A inserted 400t';
END
ELSE
BEGIN
    ROLLBACK;
    THROW 50011, 'A: not enough capacity', 1;
END

COMMIT 
GO

