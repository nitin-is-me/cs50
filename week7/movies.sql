-- schema
-- sqlite> .schema
CREATE TABLE directors (
    movie_id INTEGER NOT NULL,
    person_id INTEGER NOT NULL,
    FOREIGN KEY(movie_id) REFERENCES movies(id),
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE movies (
    id INTEGER,
    title TEXT NOT NULL,
    year NUMERIC,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT NOT NULL,
    birth NUMERIC,
    PRIMARY KEY(id)
);
CREATE TABLE ratings (
    movie_id INTEGER NOT NULL UNIQUE,
    rating REAL NOT NULL,
    votes INTEGER NOT NULL,
    FOREIGN KEY(movie_id) REFERENCES movies(id)
);
CREATE TABLE stars (
    movie_id INTEGER NOT NULL,
    person_id INTEGER NOT NULL,
    FOREIGN KEY(movie_id) REFERENCES movies(id),
    FOREIGN KEY(person_id) REFERENCES people(id)
);

-- 1. Titles of all movies from 2008
SELECT title FROM movies WHERE year = 2008;

-- 2. Birth year of Emma Stone
SELECT birth FROM people WHERE name = 'Emma Stone';

-- 3. Titles of all movies since 2018, in alphabetical order
SELECT title FROM movies WHERE year >= 2018 ORDER BY title ASC;

-- 4. Number of movies with a 10.0 rating
SELECT COUNT(*) FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE ratings.rating = 10.0;

-- 5. Titles and years of all Harry Potter movies, in chronological order (title beginning with "Harry Potter and the ...")
SELECT title, year FROM movies WHERE title LIKE 'Harry Potter and the%' ORDER BY year ASC;

-- 6. Average rating of movies in 2012
SELECT AVG(ratings.rating) FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE movies.year = 2012;

-- 7. All movies and ratings from 2010, in decreasing order by rating (alphabetical for those with same rating)
SELECT movies.title, ratings.rating FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE movies.year = 2010 ORDER BY rating DESC, title ASC;

-- 8. Names of people who starred in Toy Story
SELECT people.name FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE movies.title = 'Toy Story';

-- 9. Names of all people who starred in a movie released in 2004, ordered by birth year
SELECT DISTINCT people.id, people.name FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE movies.year = 2004 ORDER BY people.birth ASC;

-- 10. Names of all directors who have directed a movie that got a rating of at least 9.0
SELECT DISTINCT people.name FROM directors JOIN movies ON directors.movie_id = movies.id JOIN ratings ON movies.id = ratings.movie_id JOIN people ON directors.person_id = people.id WHERE ratings.rating >= 9.0;

-- 11. Titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated
SELECT DISTINCT movies.title FROM movies JOIN ratings ON movies.id = ratings.movie_id JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE people.name = 'Chadwick Boseman' ORDER BY ratings.rating DESC LIMIT 5;

-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
SELECT movies.title FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE people.name IN ('Jennifer Lawrence', 'Bradley Cooper') GROUP BY movies.id HAVING COUNT(DISTINCT people.name) = 2;

-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred
SELECT DISTINCT name FROM people WHERE id IN (
    SELECT person_id FROM stars WHERE movie_id IN (
        SELECT movie_id FROM stars WHERE person_id=(
            SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958
        )
    )
) AND id != (
    SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958
);
