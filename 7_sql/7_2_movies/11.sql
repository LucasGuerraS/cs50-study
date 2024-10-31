SELECT title
FROM movies
JOIN ratings
ON movies.id = ratings.movie_id
WHERE id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Chadwick Boseman"))
ORDER BY rating DESC
LIMIT 5;

-- Fancier Way --
/*
SELECT title FROM movies
JOIN ratings
ON movies.id = ratings.movie_id
JOIN stars
ON movies.id = stars.movie_id
JOIN people
ON people.id = stars.person_id
WHERE name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;
*/
