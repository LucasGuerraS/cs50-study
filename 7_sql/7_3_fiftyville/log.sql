-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Get starting evidence on Chamberlin Street
SELECT description,day FROM crime_scene_reports WHERE street = "Chamberlin Street" AND month = 7;
/*
+----------------------------------------------------------------+-----+
|                          description                           | day |
+----------------------------------------------------------------+-----+
| Vandalism took place at 18:46. Two people witnessed the event. | 1   |
| Bank robbery took place at 15:10. No known witnesses.          | 3   |
+----------------------------------------------------------------+-----+
*/
-- Get Interview from the 28th
SELECT transcript,day FROM interviews WHERE month = 7 AND day = 28;
/*
+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+-----+
|                                                                                                                                                     transcript                                                                                                                                                      | day |
+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+-----+
| “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”                                                                                                                               | 28  |
| “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      | 28  |
| “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.                                                                                                                   | 28  |
| Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          | 28  |
| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 | 28  |
| As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. | 28  |
| Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.                                                                        | 28  |
+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+-----+
*/
 -- Get Fiftyville airport ID
 SELECT id FROM airports WHERE city LIKE "Fiftyville";
 /*
+----+
| id |
+----+
| 8  |
+----+
 */
 -- Get flights on the 29th going out of Fiftyville and their IDs
 SELECT destination_airport_id, id, hour, minute,day,month,year FROM flights WHERE origin_airport_id = 8 AND day = 29 AND month = 7 ORDER BY hour ASC, minute ASC;
/*
+------------------------+----+------+--------+-----+-------+------+
| destination_airport_id | id | hour | minute | day | month | year |
+------------------------+----+------+--------+-----+-------+------+
| 4                      | 36 | 8    | 20     | 29  | 7     | 2023 |
| 1                      | 43 | 9    | 30     | 29  | 7     | 2023 |
| 11                     | 23 | 12   | 15     | 29  | 7     | 2023 |
| 9                      | 53 | 15   | 20     | 29  | 7     | 2023 |
| 6                      | 18 | 16   | 0      | 29  | 7     | 2023 |
+------------------------+----+------+--------+-----+-------+------+
*/
-- Discover which airport has the id of 4
SELECT city FROM airports WHERE id = 4;
/*
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
*/
-- Discover who was on the bakery and also had a phone call with less than a minute and also withdrew money
SELECT DISTINCT p.name, p.id
FROM people p
JOIN bakery_security_logs bsl ON p.license_plate = bsl.license_plate JOIN phone_calls pc ON p.phone_number = pc.caller
JOIN bank_accounts ba ON p.id = ba.person_id JOIN atm_transactions at ON ba.account_number = at.account_number
WHERE bsl.month = 7 AND bsl.day = 28 AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60 AND at.month = 7 AND at.day = 28 AND at.transaction_type = "withdraw";
/*
+--------+--------+
|  name  |   id   |
+--------+--------+
| Taylor | 449774 |
| Diana  | 514354 |
| Bruce  | 686048 |
+--------+--------+
*/
-- See who was on the flight to NYC
SELECT DISTINCT p.name, p.id FROM people p JOIN passengers ps ON p.passport_number = ps.passport_number WHERE ps.flight_id = 36;
/*
+--------+--------+
|  name  |   id   |
+--------+--------+
| Kenny  | 395717 |
| Sofia  | 398010 |
| Taylor | 449774 |
| Luca   | 467400 |
| Kelsey | 560886 |
| Edward | 651714 |
| Bruce  | 686048 |
| Doris  | 953679 |
+--------+--------+
*/
-- See who Taylor called on the 28th
SELECT p.name,  p.id FROM phone_calls pc JOIN people p ON pc.receiver = p.phone_number WHERE pc.receiver = '(676) 555-6554';
/*
+-------+--------+
| name  |   id   |
+-------+--------+
| James | 250277 |
| James | 250277 |
| James | 250277 |
+-------+--------+
*/
-- See who Bruce called
SELECT name,id FROM people WHERE phone_number = '(375) 555-8161';
/*
+-------+--------+
| name  |   id   |
+-------+--------+
| Robin | 864400 |
+-------+--------+
*/
