SELECT COUNT(movie_id)
FROM ratings
WHERE rating = 10.0
GROUP BY rating;