CREATE TABLE IF NOT EXISTS dll (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    allowed_dll text[] NOT NULL,
    all_dll text[] NOT NULL,
    restricted_dll text[] NOT NULL,
    session_id INTEGER NOT NULL,
    constraint "fk-dll_session_id" FOREIGN KEY (session_id) REFERENCES sessions (id)
);