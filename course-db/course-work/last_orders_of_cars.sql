CREATE OR REPLACE VIEW last_orders_of_cars AS
SELECT *
FROM orders AS o
WHERE (o.car_VIN, o.return_date) IN
      (SELECT _o.car_VIN, MAX(_o.return_date)
       FROM orders as _o GROUP BY _o.car_VIN);
