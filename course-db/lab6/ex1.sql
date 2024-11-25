create or replace function Period(in lower date, in upper date)
    returns table(
        project_id int,
        title varchar,
        start_date date,
        duration_years int,
        cost_rub float,
        author_id int,
        project_type_id int 
    )
    language plpgsql
as
$$
begin
    return query
        select * from projects as p
        where p.start_date between lower and upper;
end
$$;

select * from Period('2004-1-1', '2020-1-1');
