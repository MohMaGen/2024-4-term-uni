create or replace procedure object_stat(in target_name varchar, out min int, out avg int)
    language plpgsql
as
$$
begin
    select MIN(p.cost_rub), AVG(p.cost_rub) into min, avg
    from projects as p, authors as a
    where p.author_id = a.author_id and a.family_name = target_name;
end
$$;
