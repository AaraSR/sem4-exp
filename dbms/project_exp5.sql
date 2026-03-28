SELECT movie_name, language, duration
FROM Movie;

SELECT movie_name
FROM Movie
WHERE language = 'Hindi';

SELECT movie_name, duration
FROM Movie
WHERE duration > 160;

SELECT user_id, name
FROM "User"
ORDER BY name;

SELECT COUNT(*) AS total_movies
FROM Movie;

SELECT MAX(duration) AS longest_movie
FROM Movie;

SELECT AVG(duration) AS average_duration
FROM Movie;

SELECT movie_id, COUNT(show_id) AS total_shows
FROM "Show"
GROUP BY movie_id;

SELECT movie_id, COUNT(show_id) AS show_count
FROM "Show"
GROUP BY movie_id
HAVING COUNT(show_id) > 1;

SELECT show_id,
       TO_CHAR(start_time,'DD-MM-YYYY') AS show_date
FROM "Show";
