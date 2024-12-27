DROP TABLE IF EXISTS Orders CASCADE;
DROP TABLE IF EXISTS Clients CASCADE;
DROP TABLE IF EXISTS Cars CASCADE;
DROP TABLE IF EXISTS Suppliers CASCADE;

CREATE TABLE Clients (
    id SERIAL PRIMARY KEY,
    full_name VARCHAR(256) NOT NULL,

    id_number VARCHAR(10),
    id_issue_date DATE,
    id_institution VARCHAR(7),

    address VARCHAR(256),
    phone VARCHAR(256)
);

CREATE TABLE Cars (
    VIN VARCHAR(17) PRIMARY KEY,
    model VARCHAR(256),
    milage_km INT
);

CREATE TABLE Suppliers (
    id SERIAL PRIMARY KEY,
    name VARCHAR(256) NOT NULL
);

CREATE TABLE Orders (
    id SERIAL PRIMARY KEY,
    car_VIN VARCHAR(17) REFERENCES Cars(VIN),
	cost INT NOT NULL,
    issue_date DATE NOT NULL,
    return_date DATE NOT NULL,
    supplier_id INT REFERENCES Suppliers (id),
    client_id INT REFERENCES Clients (id)
);

