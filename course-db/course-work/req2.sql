DROP FUNCTION IF EXISTS supplier_of_car(VARCHAR(17));

CREATE OR REPLACE FUNCTION supplier_of_car(VIN VARCHAR(17))
RETURNS INT
AS
$$
DECLARE id INT;
BEGIN

    SELECT s.id
        FROM last_orders_of_cars as o
        LEFT JOIN suppliers AS s ON s.id = o.supplier_id
        WHERE o.car_VIN = VIN
	INTO id;

    return id;
END
$$ language plpgsql;
