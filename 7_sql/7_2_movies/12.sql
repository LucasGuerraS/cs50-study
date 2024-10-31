SELECT title
FROM movies
WHERE id IN (
    SELECT movie_id
    FROM stars
    WHERE person_id = (SELECT id FROM people WHERE name = 'Johnny Depp')
)
AND id IN (
    SELECT movie_id
    FROM stars
    WHERE person_id = (SELECT id FROM people WHERE name = 'Helena Bonham Carter')
);

-- Fancier query doing a double join --
/*
SELECT *
FROM movies m
JOIN stars s1 ON m.id = s1.movie_id
JOIN people p1 ON s1.person_id = p1.id
JOIN stars s2 ON m.id = s2.movie_id
JOIN people p2 ON s2.person_id = p2.id
WHERE p1.name = 'Johnny Depp'
  AND p2.name = 'Helena Bonham Carter';
*/
