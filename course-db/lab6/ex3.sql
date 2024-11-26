create or replace function Row_count(in date_from date, in date_to date)
    returns int
    language plpgsql
as
$$
declare
    ret int;
begin
    select COUNT(*) into ret from Period(date_from, date_to);
    return ret;
end $$;

select * from Row_count('2004-1-1', '2020-1-1');
