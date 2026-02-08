USE ShippingLineDB 
GO  

SELECT id, planned_weight_t FROM cargo
WHERE order_id = 1
