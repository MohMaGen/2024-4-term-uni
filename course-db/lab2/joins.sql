select
    authors.family_name, projects.title
from
    authors, projects
where
    authors.author_id = projects.author_id and
    authors.family_name = 'Иванов';




select
    authors.family_name, projects.title, project_types.type_name
from
    authors, projects, project_types
where
    projects.author_id = authors.author_id and
    projects.project_type_id = project_types.project_type_id and
    project_types.type_name = 'Технология' and
    authors.family_name = 'Иванов';


-- All projects and their authors with 'Технология' type.
select
    authors.family_name, projects.title, project_types.type_name
from
    authors, projects, project_types
where
        projects.author_id = authors.author_id and
        projects.project_type_id = project_types.project_type_id and
        project_types.type_name = 'НИР' and
        projects.duration_years > 3 and
        authors.age <= 30;

select
    projects.title, projects.start_date, projects.duration_years, projects.cost_rub,
    authors.family_name, authors.age,
    project_types.type_name
from
    authors, projects, project_types
where
        projects.author_id = authors.author_id
    and
        projects.project_type_id = project_types.project_type_id;


select
    a.family_name, p.title, p.start_date
from
    authors as a, projects as p
where
        a.author_id = p.author_id
    and
        p.start_date BETWEEN '2005-01-01' and '2005-12-31';

select
    p.title, p.start_date, t.type_name
from projects as p
left join project_types as t
on p.project_type_id = t.project_type_id;

select
    p.title, p.start_date, t.type_name

from project_types as t
right join projects as p
on p.project_type_id = t.project_type_id;

select
    p.title, p.start_date, p.duration_years, p.cost_rub,
    a.family_name, a.age,
    t.type_name
from
    projects as p
full outer join authors as a on a.author_id = p.author_id
full outer join project_types as t on p.project_type_id = t.project_type_id


