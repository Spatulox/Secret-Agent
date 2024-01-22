CREATE DATABASE IF NOT EXISTS secret_agent;
use secret_agent;

CREATE TABLE IF NOT EXISTS FEATURES(
    id_feature INT,
    name_feature VARCHAR(50),
    activated BOOLEAN,
    PRIMARY KEY(id_feature)
);

CREATE TABLE IF NOT EXISTS BOOSTS(
    id_boost INT,
    name_boost VARCHAR(50),
    price_boost INT,
    boost_bought INT,
    PRIMARY KEY(id_boost)
);

CREATE TABLE IF NOT EXISTS INVENTORY(
    id_inventory INT,
    coins INT,
    games INT,
    win INT,
    level INT,
    xp_till_next_level INT,
    PRIMARY KEY(id_inventory)
);

CREATE TABLE IF NOT EXISTS owned(
    id_boost INT,
    id_inventory INT,
    PRIMARY KEY(id_boost, id_inventory),
    FOREIGN KEY(id_boost) REFERENCES BOOSTS(id_boost),
    FOREIGN KEY(id_inventory) REFERENCES INVENTORY(id_inventory)
);
