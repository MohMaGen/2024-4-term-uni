SELECT
    title,
    start_date,
    row_number() OVER date_grades
FROM projects
WINDOW date_grades AS (order by start_date)
