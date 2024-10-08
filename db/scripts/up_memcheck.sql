CREATE TABLE memcheck (
    session_id SERIAL PRIMARY KEY,
    user_id INTEGER NOT NULL,
    last_modified TIMESTAMP NOT NULL,
    memcheck INTEGER NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users (id)
);

