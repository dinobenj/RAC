CREATE TABLE IF NOT EXISTS memcheck (
    id SERIAL PRIMARY KEY,
    session_id INTEGER NOT NULL,
    user_id INTEGER NOT NULL,
    last_modified TIMESTAMP NOT NULL,
    memcheck INTEGER NOT NULL,
    constraint "fk-id_user_id" foreign key (user_id) REFERENCES users (id),
    constraint "fk-session_id" foreign key (session_id) REFERENCES sessions (id)
);

