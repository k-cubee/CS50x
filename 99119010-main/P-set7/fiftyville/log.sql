-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checks the crime_scene_reports
SELECT description, day, month, year, street
  FROM crime_scene_reports;

-- Gets the interview which matches the date of the crime_scene_report
SELECT name, transcript
  FROM interviews
 WHERE day = 28
   AND month = 7
   AND year = 2021;

-- Filtered down the interview into three by checking for the mention of the bakery
-- The thief might be spotted in the security footage before 10:25
-- The thief withdrew money from ATM on Legget Street
-- The thief wants to get to Fiftyville and wants the accomplice to buy the tickets

-- Checks for bakery_security_logs
SELECT activity, license_plate, minute
  FROM bakery_security_logs
 WHERE hour = 10
   AND year = 2021
   AND month = 7
   AND day = 28
 ORDER BY minute;

SELECT activity, license_plate, minute
  FROM bakery_security_logs
 WHERE hour = 9
   AND year = 2021
   AND month = 7
   AND day = 28
 ORDER BY minute;

-- Checks for atm logs and also
-- Gets the name of everyone with the atm_logs
-- This might be useful for ticket purchase
SELECT people.name, atm_transactions.account_number, atm_transactions.amount, atm_transactions.transaction_type
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
  JOIN atm_transactions
    ON atm_transactions.account_number = bank_accounts.account_number
 WHERE atm_transactions.year = 2021
   AND atm_transactions.month = 7
   AND atm_transactions.day = 28
   AND atm_location = "Leggett Street";

-- Checks for name of the caller and receiver
SELECT people.name AS caller, phone_calls.duration
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.caller
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND duration < 60;

SELECT people.name AS receiver, phone_calls.duration
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.receiver
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND duration < 60;

-- Gets car owners at the crime scene
SELECT people.name, bakery_security_logs.activity, bakery_security_logs.minute
  FROM people
  JOIN bakery_security_logs
    ON bakery_security_logs.license_plate = people.license_plate
 WHERE bakery_security_logs.hour = 10
   AND bakery_security_logs.year = 2021
   AND bakery_security_logs.month = 7
   AND bakery_security_logs.day = 28
 ORDER BY bakery_security_logs.minute;

-- Intersects all queries
SELECT people.name
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
  JOIN atm_transactions
    ON atm_transactions.account_number = bank_accounts.account_number
 WHERE atm_transactions.year = 2021
   AND atm_transactions.month = 7
   AND atm_transactions.day = 28
   AND atm_location = "Leggett Street"
       INTERSECT
SELECT people.name
  FROM people
  JOIN bakery_security_logs
    ON bakery_security_logs.license_plate = people.license_plate
 WHERE bakery_security_logs.hour = 10
   AND bakery_security_logs.year = 2021
   AND bakery_security_logs.month = 7
   AND bakery_security_logs.day = 28
       INTERSECT
SELECT people.name
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.caller
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND duration < 60;

-- Taylor cannot be the thief as he left after more than 10 minutes
-- This leaves with Bruce and Diana
-- Bruce was talking to Robin and Diana was talking to Philip
SELECT flights.hour, flights.minute, airports.full_name
  FROM airports
  JOIN flights
    ON airports.id = flights.destination_airport_id
 WHERE airports.city = "Fiftyville"
   AND flights.year = 2021
   AND flights.month = 7
   AND flights.day = 29
 ORDER BY hour, minute;

-- Gets flights leaving to Fiftyville
SELECT flights.hour, flights.minute, flights.destination_airport_id, flights.id
  FROM flights
  JOIN airports
    ON airports.id = flights.origin_airport_id
 WHERE airports.city = "Fiftyville"
   AND flights.year = 2021
   AND flights.month = 7
   AND flights.day = 29
 ORDER BY flights.hour, flights.minute;

-- Gets the name of the airport that has the flight leaving to Fiftyville
SELECT airports.city, flights.destination_airport_id, flights.id
  FROM airports
  JOIN flights
    ON airports.id = flights.destination_airport_id
 WHERE airports.id IN
       (SELECT flights.destination_airport_id
          FROM flights
          JOIN airports
            ON airports.id = flights.origin_airport_id
         WHERE airports.city = "Fiftyville"
           AND flights.year = 2021
           AND flights.month = 7
           AND flights.day = 29)
   AND flights.year = 2021
   AND flights.month = 7
   AND flights.day = 29
 ORDER BY flights.hour, flights.minute;

-- So New York City is the name of the airport with the earliest flight
-- And the flight id is 36
SELECT people.name
  FROM passengers
  JOIN people
    ON people.passport_number = passengers.passport_number
  JOIN flights
    ON passengers.flight_id = flights.id
 WHERE flights.id = 36;

-- Bruce and Taylor are the only suspects left on the plane
-- And since Taylor should be innocent, Bruce is the thief
-- And Robin is his accomplice.