CREATE TABLE memcheck (
    id SERIAL PRIMARY KEY,
    session_id INTEGER NOT NULL,
    user_id INTEGER NOT NULL,
    last_modified TIMESTAMP NOT NULL,
    memcheck INTEGER NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users (id)
    FOREIGN KEY (session_id) REFERENCES sessions (session_id)
);

