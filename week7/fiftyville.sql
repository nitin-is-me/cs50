-- schema
-- sqlite> .schema
CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE bakery_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);

-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Filter the crime scene report to find exact report, although there are two
SELECT
    *
FROM
    crime_scene_reports
WHERE
    YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND street = 'Humphrey Street';

-- filter the interviews of the same day, seems like many mention bakery, and one person mentions he withdrew some money from bank and called
-- someone for less than a minute. It's also mentioned he left bakery within 10 minutes of theft
SELECT
    *
FROM
    interviews
WHERE
    YEAR = 2025
    AND MONTH = 7
    AND DAY = 28;

-- check bakery security logs from 10:15 to 10:25
SELECT
    *
FROM
    bakery_security_logs
WHERE
    YEAR = 2025
    AND MONTH = 7
    AND DAY = 28
    AND HOUR = 10
    AND MINUTE BETWEEN 15 AND 25;

-- check phone calls less than a minute for the same day
SELECT
    *
FROM
    phone_calls
WHERE
    duration <= 60
    AND YEAR = 2025
    AND MONTH = 7
    AND DAY = 28;

-- people who exited the bakery from 10:15 to 10:25
SELECT
    *
FROM
    people
WHERE
    license_plate IN (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            YEAR = 2025
            AND MONTH = 7
            AND DAY = 28
            AND HOUR = 10
            AND MINUTE BETWEEN 15 AND 25
    );

-- check names of all people who withdrew from Leggett Street on same day
SELECT
    name
FROM
    people
WHERE
    id IN (
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE
            account_number IN (
                SELECT
                    account_number
                FROM
                    atm_transactions
                WHERE
                    MONTH = 7
                    AND YEAR = 2025
                    AND DAY = 28
                    AND atm_location = 'Leggett Street'
                    AND transaction_type = 'withdraw'
            )
    );

-- check people who exited the bakery between 10:15 and 10:25 AND also withdrew from legget street on same day. We found Iman, Luca, Diana and Bruce
SELECT
    *
FROM
    people
WHERE
    license_plate IN (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            YEAR = 2025
            AND MONTH = 7
            AND DAY = 28
            AND HOUR = 10
            AND MINUTE BETWEEN 15 AND 25
    )
    AND id IN (
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE
            account_number IN (
                SELECT
                    account_number
                FROM
                    atm_transactions
                WHERE
                    MONTH = 7
                    AND YEAR = 2025
                    AND DAY = 28
                    AND atm_location = 'Leggett Street'
                    AND transaction_type = 'withdraw'
            )
    );

-- Among them check whose call duration is under a minute on same day. Search narrows down to Diana and Bruce.
SELECT
    *
FROM
    people
WHERE
    license_plate IN (
        SELECT
            license_plate
        FROM
            bakery_security_logs
        WHERE
            YEAR = 2025
            AND MONTH = 7
            AND DAY = 28
            AND HOUR = 10
            AND MINUTE BETWEEN 15 AND 25
    )
    AND id IN (
        SELECT
            person_id
        FROM
            bank_accounts
        WHERE
            account_number IN (
                SELECT
                    account_number
                FROM
                    atm_transactions
                WHERE
                    MONTH = 7
                    AND YEAR = 2025
                    AND DAY = 28
                    AND atm_location = 'Leggett Street'
                    AND transaction_type = 'withdraw'
            )
    )
    AND phone_number IN (
        SELECT
            caller
        FROM
            phone_calls
        WHERE
            duration <= 60
            AND YEAR = 2025
            AND MONTH = 7
            AND DAY = 28
    );

-- now check all the flights on next day because the evidence said he flew next day from fiftyville
SELECT
    *
FROM
    flights
    JOIN airports ON airports.id = flights.origin_airport_id
WHERE
    flights.year = 2025
    AND flights.month = 7
    AND flights.day = 29
    AND airports.city = 'Fiftyville';

-- check all the flights Diana and Bruce have taken
SELECT
    *
FROM
    passengers
WHERE
    passport_number IN (
        SELECT
            passport_number
        FROM
            people
        WHERE
            license_plate IN (
                SELECT
                    license_plate
                FROM
                    bakery_security_logs
                WHERE
                    YEAR = 2025
                    AND MONTH = 7
                    AND DAY = 28
                    AND HOUR = 10
                    AND MINUTE BETWEEN 15 AND 25
            )
            AND id IN (
                SELECT
                    person_id
                FROM
                    bank_accounts
                WHERE
                    account_number IN (
                        SELECT
                            account_number
                        FROM
                            atm_transactions
                        WHERE
                            MONTH = 7
                            AND YEAR = 2025
                            AND DAY = 28
                            AND atm_location = 'Leggett Street'
                            AND transaction_type = 'withdraw'
                    )
            )
            AND phone_number IN (
                SELECT
                    caller
                FROM
                    phone_calls
                WHERE
                    duration <= 60
                    AND YEAR = 2025
                    AND MONTH = 7
                    AND DAY = 28
            )
    );

-- flights in which diana and bruce have sit on 29th July (thief left from earliest flight)
SELECT
    *
FROM
    flights
WHERE
    id IN (
        SELECT
            flight_id
        FROM
            passengers
        WHERE
            passport_number IN (
                SELECT
                    passport_number
                FROM
                    people
                WHERE
                    license_plate IN (
                        SELECT
                            license_plate
                        FROM
                            bakery_security_logs
                        WHERE
                            YEAR = 2025
                            AND MONTH = 7
                            AND DAY = 28
                            AND HOUR = 10
                            AND MINUTE BETWEEN 15 AND 25
                    )
                    AND id IN (
                        SELECT
                            person_id
                        FROM
                            bank_accounts
                        WHERE
                            account_number IN (
                                SELECT
                                    account_number
                                FROM
                                    atm_transactions
                                WHERE
                                    MONTH = 7
                                    AND YEAR = 2025
                                    AND DAY = 28
                                    AND atm_location = 'Leggett Street'
                                    AND transaction_type = 'withdraw'
                            )
                    )
                    AND phone_number IN (
                        SELECT
                            caller
                        FROM
                            phone_calls
                        WHERE
                            duration <= 60
                            AND YEAR = 2025
                            AND MONTH = 7
                            AND DAY = 28
                    )
            )
    )
    AND DAY = 29
    AND MONTH = 7
    AND YEAR = 2025;

-- find who left the earliest on 29th (It's Bruce), and to where (New York City)
SELECT
    people.name,
    passengers.flight_id,
    flights.day,
    flights.hour,
    flights.minute,
    airports.city
FROM
    people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.destination_airport_id = airports.id
WHERE
    people.id IN (
        SELECT
            id
        FROM
            people
        WHERE
            license_plate IN (
                SELECT
                    license_plate
                FROM
                    bakery_security_logs
                WHERE
                    YEAR = 2025
                    AND MONTH = 7
                    AND DAY = 28
                    AND HOUR = 10
                    AND MINUTE BETWEEN 15 AND 25
            )
            AND id IN (
                SELECT
                    person_id
                FROM
                    bank_accounts
                WHERE
                    account_number IN (
                        SELECT
                            account_number
                        FROM
                            atm_transactions
                        WHERE
                            MONTH = 7
                            AND YEAR = 2025
                            AND DAY = 28
                            AND atm_location = 'Leggett Street'
                            AND transaction_type = 'withdraw'
                    )
            )
            AND phone_number IN (
                SELECT
                    caller
                FROM
                    phone_calls
                WHERE
                    duration <= 60
                    AND YEAR = 2025
                    AND MONTH = 7
                    AND DAY = 28
            )
    )
    AND flights.year = 2025
    AND flights.month = 7
    AND flights.day = 29;

--- Now that we know Bruce is the thief, we can use his number to see who received is call to find the accomplice (it's Robin)
SELECT
    people.name
FROM
    people
    JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE
    phone_calls.year = 2025
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND duration <= 60
    AND phone_calls.caller = '(367) 555-5533';
