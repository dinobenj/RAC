CREATE TABLE dll (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL
    allowed_dll text[] NOT NULL
    all_dll text[] NOT NULL
    restricted_dll text[] NOT NULL
    session_id INTEGER NOT NULL,
    FOREIGN KEY (session_id) REFERENCES sessions (id)

);