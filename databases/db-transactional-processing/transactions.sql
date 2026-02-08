-- Use cases requiring transactions:

-- 1) Place an order and assign cargo bookings for a cruise
-- When an order is placed by a client, cargos for the order are added as well. They are then assigned to cruises that are responsible for their delivery.
-- This requires transactional processing, as we do not want an order to be recorded while cargo that constitutes a part of it is not - or we do not want to overbook the maximum allowed capacity of the ship.

-- 2) Update a final port call together with related statuses
-- When a cruise is finished, its status should be set to 'COMPLETED'; similarly with the final port call ('COMPLETED') and order statuses ('DELIVERED').
-- This requires transactional processing, as otherwise an undelivered order in a completed cruise may exist.

-- 3) Schedule maintenance and update related cruises
-- A ship may require a maintenance event; cruises due for this ship should be canceled.
-- This requires transactional processing, as otherwise a planned cruise may exist in the database even though the assigned ship is unavailable.

-- Isolation level: use case 1)
-- This use case requires isolation level, as each ship has a maximum capacity field; we cannot therefore assign to it a quantity of cargo that exceeds this value. 
-- This may be the case if two people assign cargo to a particular ship at the same time. Both calculate the remaining allowed capacity and both add the remaining value.
-- As a result, total planned cargo exceeds the allowed value.
-- Recommended level of isolation: SERIALIZABLE
-- Such level will ensure safety. Even though it limits real concurrency, in case of our database, we can expect only one person to be responsible for inserting planned cargo to the database.

-- Use cases 2) and 3) will also use the SERIALIZABLE level of isolation so as to avid phantom inserts.
-- For use case 2), for instance, no cargo or order must be assigned to a completed cruise 
-- For use case 3), for instance, we do not want another cruise to be assigned to a ship that has been scheduled a maintenance event

-- To represent the issue, I will run two sets of scripts. The setup will consist of a ship, a planned cruise and cargo assigned to this cruise. Sum of planned_weight_t fields of all cargo 
-- referring this cruise will be less than ship's cargo_capacity_t. 
-- For the first set of scripts, two scripts will try to add cargo of the remaining capacity with a READ COMMITTED level of isolation. It will be shown that at the end both session, 
-- total cargo weight assigned to a ship will exceed the cargo_capacity_t of that ship.
-- For the second set of scripts, two similar script, operating with a SERIALIZABLE level of isolation, will try to do the same. It will be shown that the second session will rollback after
-- realizing the cargo_capacity_t would be exceeded. 

