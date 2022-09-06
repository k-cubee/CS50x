SELECT DISTINCT(people.name)
  FROM people
  JOIN stars
    ON people.id = stars.person_id
 WHERE stars.movie_id IN
       (SELECT movies.id
          FROM movies
         WHERE movies.id IN
               (SELECT stars.movie_id
                  FROM stars
                 WHERE stars.person_id IN
                       (SELECT people.id
                          FROM people
                         WHERE people.name = "Kevin Bacon")))
   AND NOT people.name = "Kevin Bacon";