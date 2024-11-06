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

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: authors; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.authors (
    author_id integer NOT NULL,
    family_name character varying(50) NOT NULL,
    age integer NOT NULL
);


ALTER TABLE public.authors OWNER TO postgres;

--
-- Name: authors_author_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.authors_author_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.authors_author_id_seq OWNER TO postgres;

--
-- Name: authors_author_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.authors_author_id_seq OWNED BY public.authors.author_id;


--
-- Name: authors_values; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW public.authors_values AS
 SELECT family_name,
    age
   FROM public.authors a;


ALTER VIEW public.authors_values OWNER TO postgres;

--
-- Name: project_types; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.project_types (
    project_type_id integer NOT NULL,
    type_name character varying(50) NOT NULL
);


ALTER TABLE public.project_types OWNER TO postgres;

--
-- Name: projects; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.projects (
    project_id integer NOT NULL,
    title character varying(50) NOT NULL,
    start_date date NOT NULL,
    duration_years integer NOT NULL,
    cost_rub double precision NOT NULL,
    author_id integer,
    project_type_id integer
);


ALTER TABLE public.projects OWNER TO postgres;

--
-- Name: ilog_query; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW public.ilog_query AS
 SELECT p.start_date AS "Дата начала проекта",
    p.title AS "Название проекта",
    a.family_name AS "Фамилия",
    a.age AS "Возраст",
    t.type_name AS "Тип проекта",
    p.duration_years AS "Длительность прокта, лет.",
    p.cost_rub AS "Стоимость, тыс.руб.",
    p.author_id
   FROM ((public.projects p
     LEFT JOIN public.project_types t ON ((p.project_type_id = t.project_type_id)))
     LEFT JOIN public.authors a ON ((a.author_id = p.author_id)));


ALTER VIEW public.ilog_query OWNER TO postgres;

--
-- Name: itog_query; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW public.itog_query AS
 SELECT project_id,
    author_id,
    project_type_id,
    start_date AS "Дата начала проекта",
    title AS "Название проекта",
    duration_years AS "Длительность прокта, лет.",
    cost_rub AS "Стоимость, тыс.руб."
   FROM public.projects p;


ALTER VIEW public.itog_query OWNER TO postgres;

--
-- Name: project_types_project_type_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.project_types_project_type_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.project_types_project_type_id_seq OWNER TO postgres;

--
-- Name: project_types_project_type_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.project_types_project_type_id_seq OWNED BY public.project_types.project_type_id;


--
-- Name: projects_project_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.projects_project_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.projects_project_id_seq OWNER TO postgres;

--
-- Name: projects_project_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.projects_project_id_seq OWNED BY public.projects.project_id;


--
-- Name: view_by_years; Type: VIEW; Schema: public; Owner: postgres
--

CREATE VIEW public.view_by_years AS
 SELECT EXTRACT(year FROM start_date) AS year,
    avg(cost_rub) AS "avg cost",
    sum(cost_rub) AS "sum cost",
    avg(duration_years) AS "avg duration"
   FROM public.projects
  GROUP BY (EXTRACT(year FROM start_date))
  ORDER BY (EXTRACT(year FROM start_date));


ALTER VIEW public.view_by_years OWNER TO postgres;

--
-- Name: authors author_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.authors ALTER COLUMN author_id SET DEFAULT nextval('public.authors_author_id_seq'::regclass);


--
-- Name: project_types project_type_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.project_types ALTER COLUMN project_type_id SET DEFAULT nextval('public.project_types_project_type_id_seq'::regclass);


--
-- Name: projects project_id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.projects ALTER COLUMN project_id SET DEFAULT nextval('public.projects_project_id_seq'::regclass);


--
-- Data for Name: authors; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.authors (author_id, family_name, age) FROM stdin;
1	Иванов	30
2	Петрова	29
3	Сидорова	41
\.


--
-- Data for Name: project_types; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.project_types (project_type_id, type_name) FROM stdin;
1	Технология
2	НИР
3	ОКР
\.


--
-- Data for Name: projects; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.projects (project_id, title, start_date, duration_years, cost_rub, author_id, project_type_id) FROM stdin;
1	Проект1	2004-02-03	5	1200	1	1
2	Проект2	2005-01-15	4	800	2	2
3	Проект3	2005-02-02	3	950	3	1
4	Проект4	2005-03-02	5	1000	1	2
5	Проект5	2005-02-14	5	900	3	3
6	Проект6	2005-04-04	5	1100	2	1
9	Проект Ы	2026-02-03	5	1200	1	1
10	Проект А	2024-05-03	3	200	1	2
7	Проект Ы	2024-02-03	5	1200	1	1
8	Проект А	2024-05-03	3	200	2	1
\.


--
-- Name: authors_author_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.authors_author_id_seq', 3, true);


--
-- Name: project_types_project_type_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.project_types_project_type_id_seq', 3, true);


--
-- Name: projects_project_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.projects_project_id_seq', 10, true);


--
-- Name: authors authors_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.authors
    ADD CONSTRAINT authors_pkey PRIMARY KEY (author_id);


--
-- Name: project_types project_types_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.project_types
    ADD CONSTRAINT project_types_pkey PRIMARY KEY (project_type_id);


--
-- Name: projects projects_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.projects
    ADD CONSTRAINT projects_pkey PRIMARY KEY (project_id);


--
-- Name: projects fk_author; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.projects
    ADD CONSTRAINT fk_author FOREIGN KEY (author_id) REFERENCES public.authors(author_id);


--
-- Name: projects fk_project_type; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.projects
    ADD CONSTRAINT fk_project_type FOREIGN KEY (project_type_id) REFERENCES public.project_types(project_type_id);


--
-- PostgreSQL database dump complete
--

