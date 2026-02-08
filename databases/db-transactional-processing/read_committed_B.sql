-- Session B
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

DECLARE @requested_weight_t DECIMAL(18,3) = 300.00

PRINT CONCAT('B sees remaining = ', @available_capacity_t);

IF(@requested_weight_t <= @available_capacity_t)
BEGIN
    INSERT INTO cargo (order_id, cruise_id, load_seqno, discharge_seqno,
                       planned_weight_t, transported_weight_t, status)
    VALUES (1, 1, 1, 3, @requested_weight_t, NULL, 'NOT STARTED');

    PRINT 'B inserted 300t';
END
ELSE
BEGIN
    ROLLBACK;
    THROW 50011, 'B: not enough capacity', 1;
END

COMMIT
GO
