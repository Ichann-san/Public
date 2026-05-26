-- Active: 1763821327986@@127.0.0.1@5432@mbdp12
-- ==============================================================
-- TUGAS KELAS - TRANSACTION ISOLATION LEVEL TESTING
-- PostgreSQL Script
-- ==============================================================
-- HOW TO USE THIS SCRIPT:
--   Some tests require TWO separate psql terminal windows.
--   Follow the [TERMINAL 1] and [TERMINAL 2] labels carefully.
--   Run commands IN ORDER, pausing at each ">>> PAUSE <<<" marker.
--
-- OPEN TERMINAL:
--   COMMAND: psql -U postgres -d postgres
--   (or replace 'postgres' with your database name)
-- ==============================================================


-- ==============================================================
-- SECTION 1: DDL - Create Table
-- ==============================================================
-- Run this in TERMINAL 1

DROP TABLE IF EXISTS account;

CREATE TABLE account (
    id          SERIAL PRIMARY KEY,
    name        VARCHAR(50),
    balance     INT,
    last_update TIMESTAMP DEFAULT NOW()
);


-- ==============================================================
-- SECTION 2: DML - Insert Initial Data
-- ==============================================================
-- Run this in TERMINAL 1

INSERT INTO account (name, balance) VALUES
    ('JASMINE', 1500000),
    ('ARIEL',    500000),
    ('BELLE',    300000);

-- Verify data was inserted correctly:
SELECT * FROM account;
-- Expected result:
--  id |  name   | balance |         last_update
-- ----+---------+---------+----------------------------
--   1 | JASMINE | 1500000 | 2026-05-18 19:36:30.739455
--   2 | ARIEL   |  500000 | 2026-05-18 19:36:30.739455
--   3 | BELLE   |  300000 | 2026-05-18 19:36:30.739455


-- ==============================================================
-- HELPER: Reset data to original state (run whenever needed)
-- ==============================================================
-- COMMAND (run between tests to reset):
--   UPDATE account SET balance = 1500000, last_update = NOW() WHERE id = 1;
--   UPDATE account SET balance = 500000,  last_update = NOW() WHERE id = 2;
--   UPDATE account SET balance = 300000,  last_update = NOW() WHERE id = 3;


-- ==============================================================
-- TASK 1A: NON-REPEATABLE READ TEST
-- ==============================================================
-- A non-repeatable read occurs when:
--   Transaction T1 reads a row,
--   Transaction T2 updates and commits that row,
--   T1 reads the same row again and gets a DIFFERENT value.
-- ==============================================================

-- --------------------------------------------------------------
-- TEST 1A-1: Non-Repeatable Read at READ COMMITTED
-- RESULT: ✓ CAN HAPPEN (failure bisa terjadi)
-- --------------------------------------------------------------
-- You need TWO psql terminal windows open.

-- [TERMINAL 1] Step 1: Start transaction, first read
BEGIN;
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
SELECT id, name, balance FROM account WHERE id = 1;
-- Expected: balance = 1500000
-- >>> PAUSE: Go to TERMINAL 2 and run TEST 1A-1 TERMINAL 2 block <<<

-- [TERMINAL 2] Step 2: Update and commit
BEGIN;
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
UPDATE account SET balance = balance - 200000, last_update = NOW() WHERE id = 1;
COMMIT;
-- >>> DONE in TERMINAL 2. Go back to TERMINAL 1 <<<

-- [TERMINAL 1] Step 3: Second read in same transaction
SELECT id, name, balance FROM account WHERE id = 1;
-- Expected: balance = 1300000  <-- DIFFERENT from first read!
-- NON-REPEATABLE READ OCCURRED at READ COMMITTED
COMMIT;

-- Reset data before next test:
UPDATE account SET balance = 1500000, last_update = NOW() WHERE id = 1;
UPDATE account SET balance = 500000,  last_update = NOW() WHERE id = 2;
UPDATE account SET balance = 300000,  last_update = NOW() WHERE id = 3;


-- --------------------------------------------------------------
-- TEST 1A-2: Non-Repeatable Read at REPEATABLE READ
-- RESULT: ✗ CANNOT HAPPEN (failure tidak bisa terjadi)
-- --------------------------------------------------------------

-- [TERMINAL 1] Step 1: Start transaction, first read
BEGIN;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SELECT id, name, balance FROM account WHERE id = 1;
-- Expected: balance = 1500000
-- >>> PAUSE: Go to TERMINAL 2 and run TEST 1A-2 TERMINAL 2 block <<<

-- [TERMINAL 2] Step 2: Update and commit
BEGIN;
UPDATE account SET balance = balance - 200000, last_update = NOW() WHERE id = 1;
COMMIT;
-- >>> DONE in TERMINAL 2. Go back to TERMINAL 1 <<<

-- [TERMINAL 1] Step 3: Second read in same transaction
SELECT id, name, balance FROM account WHERE id = 1;
-- Expected: balance = 1500000  <-- SAME as first read! (snapshot protected)
-- NON-REPEATABLE READ DID NOT OCCUR at REPEATABLE READ
COMMIT;

-- Reset:
UPDATE account SET balance = 1500000, last_update = NOW() WHERE id = 1;
UPDATE account SET balance = 500000,  last_update = NOW() WHERE id = 2;
UPDATE account SET balance = 300000,  last_update = NOW() WHERE id = 3;


-- --------------------------------------------------------------
-- TEST 1A-3: Non-Repeatable Read at SERIALIZABLE
-- RESULT: ✗ CANNOT HAPPEN (failure tidak bisa terjadi)
-- --------------------------------------------------------------

-- [TERMINAL 1] Step 1: Start transaction, first read
BEGIN;
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SELECT id, name, balance FROM account WHERE id = 1;
-- Expected: balance = 1500000
-- >>> PAUSE: Go to TERMINAL 2 and run TEST 1A-3 TERMINAL 2 block <<<

-- [TERMINAL 2] Step 2: Update and commit
BEGIN;
UPDATE account SET balance = balance - 200000, last_update = NOW() WHERE id = 1;
COMMIT;
-- >>> DONE in TERMINAL 2. Go back to TERMINAL 1 <<<

-- [TERMINAL 1] Step 3: Second read in same transaction
SELECT id, name, balance FROM account WHERE id = 1;
-- Expected: balance = 1500000  <-- SAME as first read! (snapshot protected)
-- NON-REPEATABLE READ DID NOT OCCUR at SERIALIZABLE
COMMIT;

-- Reset:
UPDATE account SET balance = 1500000, last_update = NOW() WHERE id = 1;
UPDATE account SET balance = 500000,  last_update = NOW() WHERE id = 2;
UPDATE account SET balance = 300000,  last_update = NOW() WHERE id = 3;


-- ==============================================================
-- TASK 1B: SERIALIZATION ANOMALY TEST
-- ==============================================================
-- A serialization anomaly occurs when:
--   Two concurrent transactions each read a shared value,
--   and each writes based on what it read,
--   producing a result that could NOT happen if run sequentially.
--
-- Scenario: 
--   T1 reads total balance, then updates JASMINE's balance if total > 2000000
--   T2 reads total balance, then updates ARIEL's balance if total > 2000000
--   If run sequentially: only one update would happen (after first update, 
--   total would drop and the second might not qualify)
-- ==============================================================

-- --------------------------------------------------------------
-- TEST 1B-1: Serialization Anomaly at READ COMMITTED
-- RESULT: ✓ CAN HAPPEN (failure bisa terjadi)
-- --------------------------------------------------------------

-- [TERMINAL 1] Step 1: Read total balance
BEGIN;
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
SELECT SUM(balance) AS total FROM account;
-- Expected: total = 2300000 (> 2000000, so T1 will proceed to update)
-- >>> PAUSE: Go to TERMINAL 2 and run TEST 1B-1 TERMINAL 2 block <<<

-- [TERMINAL 2] Step 2: Also read total, update ARIEL, and commit
BEGIN;
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
SELECT SUM(balance) AS total FROM account;
-- Expected: total = 2300000 (> 2000000, so T2 also decides to update)
UPDATE account SET balance = balance + 100000, last_update = NOW() WHERE id = 2; -- ARIEL
COMMIT;
-- >>> DONE in TERMINAL 2. Go back to TERMINAL 1 <<<

-- [TERMINAL 1] Step 3: Update JASMINE and commit
UPDATE account SET balance = balance + 100000, last_update = NOW() WHERE id = 1; -- JASMINE
COMMIT;
-- Both transactions committed! Both added bonus despite total having changed.
-- SERIALIZATION ANOMALY OCCURRED at READ COMMITTED

SELECT * FROM account;
-- Both JASMINE and ARIEL got +100000 bonus based on stale total reads

-- Reset:
UPDATE account SET balance = 1500000, last_update = NOW() WHERE id = 1;
UPDATE account SET balance = 500000,  last_update = NOW() WHERE id = 2;
UPDATE account SET balance = 300000,  last_update = NOW() WHERE id = 3;


-- --------------------------------------------------------------
-- TEST 1B-2: Serialization Anomaly at REPEATABLE READ
-- RESULT: ✓ CAN HAPPEN in PostgreSQL (failure bisa terjadi)
-- Note: REPEATABLE READ protects against non-repeatable reads,
--       but NOT against all serialization anomalies.
-- --------------------------------------------------------------

-- [TERMINAL 1] Step 1: Read total balance
BEGIN;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SELECT SUM(balance) AS total FROM account;
-- Expected: total = 2300000
-- >>> PAUSE: Go to TERMINAL 2 and run TEST 1B-2 TERMINAL 2 block <<<

-- [TERMINAL 2] Step 2: Read, update ARIEL, commit
BEGIN;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SELECT SUM(balance) AS total FROM account;
UPDATE account SET balance = balance + 100000, last_update = NOW() WHERE id = 2; -- ARIEL
COMMIT;
-- >>> DONE in TERMINAL 2. Go back to TERMINAL 1 <<<

-- [TERMINAL 1] Step 3: Update JASMINE and commit
UPDATE account SET balance = balance + 100000, last_update = NOW() WHERE id = 1; -- JASMINE
COMMIT;
-- Both transactions committed successfully!
-- SERIALIZATION ANOMALY OCCURRED at REPEATABLE READ

SELECT * FROM account;

-- Reset:
UPDATE account SET balance = 1500000, last_update = NOW() WHERE id = 1;
UPDATE account SET balance = 500000,  last_update = NOW() WHERE id = 2;
UPDATE account SET balance = 300000,  last_update = NOW() WHERE id = 3;


-- --------------------------------------------------------------
-- TEST 1B-3: Serialization Anomaly at SERIALIZABLE
-- RESULT: ✗ CANNOT HAPPEN (failure tidak bisa terjadi)
-- PostgreSQL will detect the conflict and abort one transaction.
-- --------------------------------------------------------------

-- [TERMINAL 1] Step 1: Read total balance
BEGIN;
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SELECT SUM(balance) AS total FROM account;
-- Expected: total = 2300000
-- >>> PAUSE: Go to TERMINAL 2 and run TEST 1B-3 TERMINAL 2 block <<<

-- [TERMINAL 2] Step 2: Read, update ARIEL, commit
BEGIN;
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SELECT SUM(balance) AS total FROM account;
UPDATE account SET balance = balance + 100000, last_update = NOW() WHERE id = 2; -- ARIEL
COMMIT;
-- T2 commits successfully.
-- >>> DONE in TERMINAL 2. Go back to TERMINAL 1 <<<

-- [TERMINAL 1] Step 3: Attempt update JASMINE and commit
UPDATE account SET balance = balance + 100000, last_update = NOW() WHERE id = 1; -- JASMINE
COMMIT;
-- EXPECTED ERROR:
--   ERROR:  could not serialize access due to read/write dependencies among transactions
--   DETAIL:  Reason code: Canceled on identification as a pivot, during commit attempt.
--   HINT:   The transaction might succeed if retried.
--
-- PostgreSQL ABORTED T1 to prevent the anomaly!
-- SERIALIZATION ANOMALY DID NOT OCCUR at SERIALIZABLE

SELECT * FROM account;
-- Only ARIEL (T2) got the bonus. T1 was rolled back.

-- Reset:
UPDATE account SET balance = 1500000, last_update = NOW() WHERE id = 1;
UPDATE account SET balance = 500000,  last_update = NOW() WHERE id = 2;
UPDATE account SET balance = 300000,  last_update = NOW() WHERE id = 3;


-- ==============================================================
-- TASK 2: ISOLATION LEVEL MAPPING TABLE
-- ==============================================================
--
-- Mark:
--   X  = failure TIDAK BISA terjadi (cannot happen)
--   V  = failure BISA terjadi (can happen)
--
-- +---------------------------+----------------+-----------------+--------------+
-- | Failure / Anomaly         | Read Committed | Repeatable Read | Serializable |
-- +---------------------------+----------------+-----------------+--------------+
-- | Dirty Read                |       X        |        X        |      X       |
-- | Non-Repeatable Read       |       V        |        X        |      X       |
-- | Phantom Read              |       V        |        X        |      X       |
-- | Serialization Anomaly     |       V        |        V        |      X       |
-- +---------------------------+----------------+-----------------+--------------+
--
-- CATATAN / NOTES:
-- * PostgreSQL tidak memiliki isolation level READ UNCOMMITTED.
--   Jika di-set ke READ UNCOMMITTED, PostgreSQL otomatis menggunakan
--   READ COMMITTED, sehingga Dirty Read tidak pernah terjadi di PostgreSQL.
--
-- * Pada PostgreSQL, REPEATABLE READ juga mencegah Phantom Read
--   (berbeda dari standar SQL yang mengizinkan phantom read di level ini).
--
-- * Hanya SERIALIZABLE yang mencegah Serialization Anomaly.
--   Ini dicapai dengan Serializable Snapshot Isolation (SSI) di PostgreSQL.
-- ==============================================================
