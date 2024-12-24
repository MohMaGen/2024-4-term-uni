--
-- PostgreSQL database dump
--

-- Dumped from database version 16.3
-- Dumped by pg_dump version 16.3

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: cars_of_client(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.cars_of_client(id integer) RETURNS TABLE(vin character varying, model character varying)
    LANGUAGE plpgsql
    AS $$
BEGIN
    return query
        SELECT c.VIN, c.model
        FROM cars AS c
        WHERE c.VIN IN (SELECT o.car_VIN
                        FROM  orders_of_client(id) AS O);
END
$$;


ALTER FUNCTION public.cars_of_client(id integer) OWNER TO postgres;

--
-- Name: cars_of_client_at_moment(integer, date); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.cars_of_client_at_moment(id integer, moment date) RETURNS TABLE(vin character varying, model character varying)
    LANGUAGE plpgsql
    AS $$
BEGIN
    return query
        SELECT c.VIN, c.model
        FROM cars AS c
        WHERE c.VIN IN (SELECT o.car_VIN
                        FROM orders_of_client(id) AS o
                        WHERE moment BETWEEN o.issue_date AND o.return_date);
END
$$;


ALTER FUNCTION public.cars_of_client_at_moment(id integer, moment date) OWNER TO postgres;

--
-- Name: cars_of_client_by_range(integer, date, date); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.cars_of_client_by_range(id integer, r_begin date, r_end date) RETURNS TABLE(vin character varying, model character varying)
    LANGUAGE plpgsql
    AS $$
BEGIN
    return query
        SELECT c.VIN, c.model
        FROM cars AS c
        WHERE c.VIN IN (SELECT o.car_VIN
                        FROM orders_of_client(id) AS o
                        WHERE o.issue_date BETWEEN r_begin AND r_end);
END
$$;


ALTER FUNCTION public.cars_of_client_by_range(id integer, r_begin date, r_end date) OWNER TO postgres;

--
-- Name: orders_of_client(integer); Type: FUNCTION; Schema: public; Owner: postgres
--

CREATE FUNCTION public.orders_of_client(_client_id integer) RETURNS TABLE(order_id integer, car_vin character varying, cost integer, issue_date date, return_date date, supplier_id integer, client_id integer)
    LANGUAGE plpgsql
    AS $$
BEGIN
    return query
        SELECT * FROM orders
        WHERE orders.client_id = _client_id;
END
$$;


ALTER FUNCTION public.orders_of_client(_client_id integer) OWNER TO postgres;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: cars; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.cars (
    vin character varying(17) NOT NULL,
    model character varying(256),
    milage_km integer
);


ALTER TABLE public.cars OWNER TO postgres;

--
-- Name: clients; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.clients (
    id integer NOT NULL,
    full_name character varying(256) NOT NULL,
    id_number character varying(10),
    id_issue_date date,
    id_institution character varying(7),
    address character varying(256),
    phone character varying(256)
);


ALTER TABLE public.clients OWNER TO postgres;

--
-- Name: clients_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.clients_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.clients_id_seq OWNER TO postgres;

--
-- Name: clients_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.clients_id_seq OWNED BY public.clients.id;


--
-- Name: orders; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.orders (
    id integer NOT NULL,
    car_vin character varying(17),
    cost integer NOT NULL,
    issue_date date NOT NULL,
    return_date date NOT NULL,
    supplier_id integer,
    client_id integer
);


ALTER TABLE public.orders OWNER TO postgres;

--
-- Name: orders_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.orders_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.orders_id_seq OWNER TO postgres;

--
-- Name: orders_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.orders_id_seq OWNED BY public.orders.id;


--
-- Name: suppliers; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.suppliers (
    id integer NOT NULL,
    name character varying(256) NOT NULL
);


ALTER TABLE public.suppliers OWNER TO postgres;

--
-- Name: suppliers_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.suppliers_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.suppliers_id_seq OWNER TO postgres;

--
-- Name: suppliers_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.suppliers_id_seq OWNED BY public.suppliers.id;


--
-- Name: clients id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.clients ALTER COLUMN id SET DEFAULT nextval('public.clients_id_seq'::regclass);


--
-- Name: orders id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders ALTER COLUMN id SET DEFAULT nextval('public.orders_id_seq'::regclass);


--
-- Name: suppliers id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.suppliers ALTER COLUMN id SET DEFAULT nextval('public.suppliers_id_seq'::regclass);


--
-- Data for Name: cars; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.cars (vin, model, milage_km) FROM stdin;
15AD1135931ADB325	Ford Focus RS	40000
15AD1135ABASDSAK5	Ford Focus RS	401232
23AD11235DAB1B145	Porshe 911	232124
2AS1293BADKAS1235	Porshe 911	220242
23AD1121ASBLAS4AB	Porshe 911	208402
15AD1135931ADAB49	KamAZ-6560	659493
12351135931ADAB49	KamAZ-6560	593912
\.


--
-- Data for Name: clients; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.clients (id, full_name, id_number, id_issue_date, id_institution, address, phone) FROM stdin;
1	Краснов Дмитрий Александрович	4379123456	2012-02-01	723-235	г. Москва, ул. Кривая д. 23	81321232354
2	Зеленов Влад Георгиевич	4379543456	2010-05-01	703-235	г. Москва, ул. Кривая д. 24	81323432354
3	Пятков Алексей Марков	4379543700	2008-05-01	703-235	г. Москва, ул. Ленина, д. 1	89033432354
4	Титова Влада Петрова	4379543700	2008-05-01	703-235	г. Москва, ул. Ленина, д. 1	89033432354
5	Каролёва Лена Георгиевна	4379543700	2008-05-01	703-235	г. Москва, ул. Ленина, д. 1	89033432354
\.


--
-- Data for Name: orders; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.orders (id, car_vin, cost, issue_date, return_date, supplier_id, client_id) FROM stdin;
1	15AD1135931ADB325	10000	2022-11-02	2022-12-05	1	1
2	23AD11235DAB1B145	50000	2022-05-02	2022-12-05	2	2
3	2AS1293BADKAS1235	50500	2023-01-02	2023-01-10	2	2
4	23AD11235DAB1B145	50100	2023-02-25	2023-03-02	2	2
5	15AD1135931ADAB49	101000	2021-02-25	2021-03-02	3	3
6	15AD1135931ADAB49	105000	2022-02-25	2022-03-02	3	1
7	12351135931ADAB49	105100	2023-02-25	2022-03-02	3	5
8	12351135931ADAB49	105100	2023-01-02	2023-01-10	3	4
9	15AD1135931ADAB49	105000	2020-06-21	2020-06-25	2	5
\.


--
-- Data for Name: suppliers; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.suppliers (id, name) FROM stdin;
1	ООО Машины
2	ООО КАРСФОРЭВРИВАН
3	ООО Большие машины
\.


--
-- Name: clients_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.clients_id_seq', 5, true);


--
-- Name: orders_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.orders_id_seq', 9, true);


--
-- Name: suppliers_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.suppliers_id_seq', 3, true);


--
-- Name: cars cars_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.cars
    ADD CONSTRAINT cars_pkey PRIMARY KEY (vin);


--
-- Name: clients clients_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.clients
    ADD CONSTRAINT clients_pkey PRIMARY KEY (id);


--
-- Name: orders orders_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_pkey PRIMARY KEY (id);


--
-- Name: suppliers suppliers_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.suppliers
    ADD CONSTRAINT suppliers_pkey PRIMARY KEY (id);


--
-- Name: orders orders_car_vin_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_car_vin_fkey FOREIGN KEY (car_vin) REFERENCES public.cars(vin);


--
-- Name: orders orders_client_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_client_id_fkey FOREIGN KEY (client_id) REFERENCES public.clients(id);


--
-- Name: orders orders_supplier_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_supplier_id_fkey FOREIGN KEY (supplier_id) REFERENCES public.suppliers(id);


--
-- PostgreSQL database dump complete
--

