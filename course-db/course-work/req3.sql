DROP FUNCTION IF EXISTS cars_on_parking(moment Date);
DROP FUNCTION IF EXISTS ordered_cars(moment Date);
DROP FUNCTION IF EXISTS cars_state(moment Date);

CREATE OR REPLACE FUNCTION ordered_cars(moment Date)
RETURNS table(VIN VARCHAR(17), model VARCHAR(256), milage_km INT)
LANGUAGE plpgsql
AS $$
BEGIN
    return query
        SELECT c.VIN, c.model, c.milage_km
        FROM cars AS c
        RIGHT JOIN orders AS o ON o.car_VIN = c.VIN
        WHERE o.issue_date <= moment AND o.return_date >= moment;
END
$$;

CREATE OR REPLACE FUNCTION cars_on_parking(moment Date)
RETURNS table(VIN VARCHAR(17), model VARCHAR(256), milage_km INT)
LANGUAGE plpgsql
AS $$
BEGIN
    return query
        SELECT *
        FROM cars AS c
        EXCEPT
        SELECT * FROM ordered_cars(moment);
END
$$;


CREATE OR REPLACE FUNCTION cars_state(moment Date)
RETURNS table(VIN VARCHAR(17), model VARCHAR(256), state TEXT)
LANGUAGE plpgsql
AS $$
BEGIN
    return query
        SELECT cp.VIN, cp.model, 'В гараже'
        FROM cars_on_parking(moment) AS cp
        UNION
        SELECT oc.VIN, oc.model, 'На заказе'
        FROM ordered_cars(moment) AS oc;
END
$$;
