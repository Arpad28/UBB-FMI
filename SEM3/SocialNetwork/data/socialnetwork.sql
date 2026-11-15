CREATE TABLE users (
                       id BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
                       first_name VARCHAR(100) NOT NULL,
                       last_name VARCHAR(100) NOT NULL
);

CREATE TABLE friendships (
                             id1 BIGINT NOT NULL,
                             id2 BIGINT NOT NULL,
                             friends_from TIMESTAMP NOT NULL,
                             CONSTRAINT pk_friendships PRIMARY KEY (id1, id2),
                             CONSTRAINT chk_id_order CHECK (id1 < id2),
                             CONSTRAINT fk_user1 FOREIGN KEY (id1) REFERENCES users(id) ON DELETE CASCADE,
                             CONSTRAINT fk_user2 FOREIGN KEY (id2) REFERENCES users(id) ON DELETE CASCADE
);