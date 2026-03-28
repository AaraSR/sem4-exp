INSERT INTO "User" VALUES
	(1,'Aditya Vakadia'),
	(2,'Om Suryavanshi'),
	(3,'Aaradhya Raut'),
	(4,'Chandler Bing'),
	(5,'Eleven Hopper');

INSERT INTO Movie VALUES
(101,'Sholay','Hindi',162),
(102,'Dilwale Dulhania Le Jayenge','Hindi',189),
(103,'3 Idiots','Hindi',170),
(104,'Lagaan','Hindi',224),
(105,'Dangal','Hindi',161);


INSERT INTO Movie VALUES
(201,'Titanic','English',195),
(202,'Avatar','English',162),
(203,'The Dark Knight','English',152),
(204,'Avengers Endgame','English',181),
(205,'Inception','English',148),
(206,'Interstellar','English',169),
(207,'Jurassic Park','English',127),
(208,'The Matrix','English',136),
(209,'Gladiator','English',155),
(210,'Forrest Gump','English',142);

INSERT INTO Theatre VALUES
(1,'Regal Cinema'),
(2,'PVR Juhu'),
(3,'INOX Nariman Point');


INSERT INTO Screen VALUES
(1,1,200),
(2,2,180),
(3,3,220);


INSERT INTO "Show" VALUES
(1,103,1,1,'Running','2026-04-01 10:00','2026-04-01 13:00'),
(2,205,2,2,'Running','2026-04-01 14:00','2026-04-01 17:00'),
(3,101,3,3,'Running','2026-04-01 18:00','2026-04-01 21:00');

SELECT * FROM Movie;

UPDATE Movie
SET duration = 175
WHERE movie_name = '3 Idiots';


SELECT * FROM "User";

UPDATE "User"
SET name = 'Mike Wheeler'
WHERE user_id = 3;

SELECT * FROM Movie;

DELETE FROM Movie
WHERE movie_name = 'Gladiator';

SELECT * FROM Movie;