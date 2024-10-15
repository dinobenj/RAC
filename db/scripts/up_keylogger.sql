CREATE TABLE IF NOT EXISTS keylogger (
    id SERIAL PRIMARY KEY,
    session_id INTEGER NOT NULL,
    user_id INTEGER NOT NULL,
    last_modified TIMESTAMP NOT NULL,
    keylogger json NOT NULL,
    constraint "fk-logger_user_id" FOREIGN KEY (user_id) REFERENCES users (id),
    constraint "fk-logger_session_id" FOREIGN KEY (session_id) REFERENCES sessions (id)
);