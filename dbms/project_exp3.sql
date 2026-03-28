CREATE TABLE "User" (
    user_id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

CREATE TABLE Movie (
    movie_id INT PRIMARY KEY,
    movie_name VARCHAR(150) NOT NULL,
    language VARCHAR(50),
    duration INT
);

CREATE TABLE Theatre (
    theatre_id INT PRIMARY KEY,
    name VARCHAR(150) NOT NULL
);

CREATE TABLE Screen (
    screen_id INT PRIMARY KEY,
    theatre_id INT,
    capacity INT,
    FOREIGN KEY (theatre_id) REFERENCES Theatre(theatre_id)
);

CREATE TABLE "Show" (
    show_id INT PRIMARY KEY,
    movie_id INT,
    theatre_id INT,
    screen_id INT,
    status VARCHAR(20),
    start_time TIMESTAMP,
    end_time TIMESTAMP,
    FOREIGN KEY (movie_id) REFERENCES Movie(movie_id),
    FOREIGN KEY (theatre_id) REFERENCES Theatre(theatre_id),
    FOREIGN KEY (screen_id) REFERENCES Screen(screen_id)
);

CREATE TABLE Seat (
    seat_id INT PRIMARY KEY,
    screen_id INT,
    row_no INT,
    column_no INT,
    type VARCHAR(20),
    FOREIGN KEY (screen_id) REFERENCES Screen(screen_id)
);

CREATE TABLE Ticket (
    tkt_id INT PRIMARY KEY,
    user_id INT,
    show_id INT,
    seat_id INT,
    amount NUMERIC(10,2),
    payment_method VARCHAR(50),
    FOREIGN KEY (user_id) REFERENCES "User"(user_id),
    FOREIGN KEY (show_id) REFERENCES "Show"(show_id),
    FOREIGN KEY (seat_id) REFERENCES Seat(seat_id)
);

SELECT table_name
FROM information_schema.tables
WHERE table_type = 'BASE TABLE'
  AND table_schema NOT IN ('pg_catalog', 'information_schema');