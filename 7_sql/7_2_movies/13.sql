SELECT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT id
        FROM movies
        WHERE id IN (
            SELECT movie_id
            FROM stars
            WHERE person_id = (
                SELECT id
                FROM people
                WHERE name = "Kevin Bacon"
                AND birth = 1958
            )
        )
    )
)
AND id != (
    SELECT id
    FROM people
    WHERE name = "Kevin Bacon"
    AND birth = 1958
);

/*
SELECT DISTINCT p.name
FROM people p
JOIN stars s1
ON p.id = s1.person_id
JOIN movies m
ON s1.movie_id = m.id
JOIN stars s2
ON m.id = s2.movie_id
JOIN people kb
ON s2.person_id = kb.id
WHERE kb.name = 'Kevin Bacon'
  AND kb.birth = 1958
  AND p.id != kb.id;
*/
