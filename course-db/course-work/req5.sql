DROP FUNCTION IF EXISTS orders_of_client(INT);

CREATE OR REPLACE FUNCTION orders_of_client(_client_id INT)
RETURNS table(
    order_id INT,
    car_VIN VARCHAR(17),
	cost INT,
    issue_date DATE,
    return_date DATE,
    supplier_id INT,
    client_id INT
)
LANGUAGE plpgsql
AS $$
BEGIN
    return query
        SELECT * FROM orders
        WHERE orders.client_id = _client_id;
END
$$;
