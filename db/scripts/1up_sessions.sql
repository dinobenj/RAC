CREATE TABLE IF NOT EXISTS sessions (
    id SERIAL PRIMARY KEY,
    user_id INTEGER NOT NULL,
    last_modified TIMESTAMP NOT NULL,
    constraint "fk-session_user_id "FOREIGN KEY (user_id) REFERENCES users (id)
);
--Will add more columns to this table later as more features are added