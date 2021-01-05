select distinct p.name from ratings as r,directors as s, people as p where s.movie_id = r.movie_id and s.person_id = p.id and r.rating >= 9.0;
