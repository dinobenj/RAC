CREATE TABLE sessions (
    id SERIAL PRIMARY KEY,
    user_id INTEGER NOT NULL,
    last_modified TIMESTAMP NOT NULL,
    memcheck INTEGER NOT NULL,
    dll_id INTEGER NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users (id)
    FOREIGN KEY (dll_id) REFERENCES dlls (id)
);
--Will add more columns to this table later as more features are added