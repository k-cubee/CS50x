SELECT title
  FROM movies
  JOIN ratings
    ON movies.id = ratings.movie_id
 WHERE id IN
       (SELECT stars.movie_id
          FROM stars
          JOIN ratings
            ON ratings.movie_id = stars.movie_id
          JOIN people
            ON stars.person_id = people.id
         WHERE people.name = "Chadwick Boseman")
 ORDER BY ratings.rating DESC
 LIMIT 5;