DROP FUNCTION IF EXISTS cars_of_client(INT);
DROP FUNCTION IF EXISTS cars_of_client_by_range(INT, DATE, DATE);
DROP FUNCTION IF EXISTS cars_of_client_at_moment(INT, DATE);


CREATE OR REPLACE FUNCTION cars_of_client(id INT)
RETURNS table(VIN VARCHAR(17), model VARCHAR(256))
LANGUAGE plpgsql
AS $$
BEGIN
    return query
        SELECT DISTINCT c.VIN, c.model
        FROM cars AS c
        WHERE c.VIN IN (SELECT o.car_VIN
                        FROM  orders_of_client(id) AS O);
END
$$;

CREATE OR REPLACE FUNCTION cars_of_client_by_range(id INT,
                                        r_begin DATE, r_end DATE)
RETURNS table(VIN VARCHAR(17), model VARCHAR(256))
LANGUAGE plpgsql
AS $$
BEGIN
    return query
        SELECT DISTINCT c.VIN, c.model
        FROM cars AS c
        WHERE c.VIN IN (SELECT o.car_VIN
                        FROM orders_of_client(id) AS o
                        WHERE o.issue_date BETWEEN r_begin AND r_end);
END
$$;


CREATE OR REPLACE FUNCTION cars_of_client_at_moment(id INT, moment DATE)
RETURNS table(VIN VARCHAR(17), model VARCHAR(256))
LANGUAGE plpgsql
AS $$
BEGIN
    return query
        SELECT DISTINCT c.VIN, c.model
        FROM cars AS c
        WHERE c.VIN IN (SELECT o.car_VIN
                        FROM orders_of_client(id) AS o
                        WHERE moment BETWEEN o.issue_date AND o.return_date);
END
$$;
