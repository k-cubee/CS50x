SELECT DISTINCT(title)
  FROM movies
 WHERE id IN
       (SELECT stars.movie_id
          FROM stars
          JOIN people
            ON stars.person_id = people.id
         WHERE people.name = "Helena Bonham Carter"
     INTERSECT
        SELECT stars.movie_id
          FROM stars
          JOIN people
            ON stars.person_id = people.id
         WHERE people.name = "Johnny Depp");