-- Active: 1761461509284@@127.0.0.1@3306@quiz1
-- Delete tables if any
DROP TABLE IF EXISTS enrollments;
DROP TABLE IF EXISTS payments;
DROP TABLE IF EXISTS courses;
DROP TABLE IF EXISTS students;

CREATE TABLE students (
    student_id CHAR(5) PRIMARY KEY,
    student_name VARCHAR(100) NOT NULL,
    gender VARCHAR(10) NOT NULL,
    birth_date DATE NOT NULL,
    major VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE
);

CREATE TABLE courses (
    course_id CHAR(4) PRIMARY KEY,
    course_name VARCHAR(100) NOT NULL,
    credits INT NOT NULL CHECK (credits > 0),
    semester INT NOT NULL CHECK (semester BETWEEN 1 AND 8),
    lecturer_name VARCHAR(100) NOT NULL
);

CREATE TABLE enrollments (
    enrollment_id CHAR(8) PRIMARY KEY,
    student_id CHAR(5) NOT NULL,
    course_id CHAR(4) NOT NULL,
    enrollment_date DATE NOT NULL,
    final_grade VARCHAR(2),
    status VARCHAR(20) NOT NULL,
    CONSTRAINT fk_enrollment_student
        FOREIGN KEY (student_id) REFERENCES students(student_id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    CONSTRAINT fk_enrollment_course
        FOREIGN KEY (course_id) REFERENCES courses(course_id)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    CONSTRAINT uq_student_course UNIQUE (student_id, course_id)
);

CREATE TABLE payments (
    payment_id CHAR(6) PRIMARY KEY,
    student_id CHAR(5) NOT NULL,
    payment_date DATE NOT NULL,
    amount NUMERIC(12,0) NOT NULL CHECK (amount > 0),
    payment_method VARCHAR(30) NOT NULL,
    payment_status VARCHAR(20) NOT NULL,
    CONSTRAINT fk_payment_student
        FOREIGN KEY (student_id) REFERENCES students(student_id)
        ON UPDATE CASCADE
        ON DELETE CASCADE
);

INSERT INTO students (student_id, student_name, gender, birth_date, major, email) VALUES
('50001', 'Andi Saputra', 'Male', '2003-01-15', 'Informatics', 'andi.saputra@kampus.ac.id'),
('60001', 'Bunga Lestari', 'Female', '2002-07-21', 'Information Systems', 'bunga.lestari@kampus.ac.id'),
('50002', 'Citra Dewi', 'Female', '2003-03-10', 'Informatics', 'citra.dewi@kampus.ac.id'),
('70001', 'Dimas Prakoso', 'Male', '2001-11-05', 'Data Science', 'dimas.prakoso@kampus.ac.id'),
('60002', 'Eka Putri', 'Female', '2002-09-18', 'Information Systems', 'eka.putri@kampus.ac.id'),
('80001', 'Fajar Nugroho', 'Male', '2003-05-27', 'Cyber Security', 'fajar.nugroho@kampus.ac.id'),
('70002', 'Gita Permata', 'Female', '2002-12-01', 'Data Science', 'gita.permata@kampus.ac.id'),
('50003', 'Hendra Wijaya', 'Male', '2001-08-14', 'Informatics', 'hendra.wijaya@kampus.ac.id');

INSERT INTO courses (course_id, course_name, credits, semester, lecturer_name) VALUES
('C001', 'Database Systems', 3, 3, 'Dr. Ratna Sari'),
('C002', 'Data Structures', 3, 2, 'Ir. Budi Santoso'),
('C003', 'Operating Systems', 3, 4, 'Dr. Wahyu Hidayat'),
('C004', 'Web Programming', 3, 4, 'Maya Kusuma, M.Kom'),
('C005', 'Machine Learning', 3, 6, 'Dr. Rudi Hartono'),
('C006', 'Computer Networks', 3, 4, 'Ir. Taufik Akbar'),
('C007', 'Business Process Management', 2, 5, 'Dr. Lina Marlina');

INSERT INTO payments (payment_id, student_id, payment_date, amount, payment_method, payment_status) VALUES
('P00001', '50001', '2026-01-10', 3500000, 'Bank Transfer', 'Paid'),
('P00002', '60001',  '2026-01-10', 4200000, 'Virtual Account', 'Paid'),
('P00003', '50002', '2026-01-13', 3500000, 'Bank Transfer', 'Paid'),
('P00004', '70001', '2026-01-12', 5000000, 'Credit Card', 'Pending'),
('P00005', '60002', '2026-01-11', 4200000, 'Cash', 'Paid'),
('P00006', '80001', '2026-01-12', 3900000, 'Virtual Account', 'Paid'),
('P00007', '70002', '2026-01-10', 5000000, 'Bank Transfer', 'Pending'),
('P00008', '50003', '2026-01-13', 3500000, 'Credit Card', 'Paid');

INSERT INTO enrollments (enrollment_id, student_id, course_id, enrollment_date, final_grade, status) VALUES
('E0000001', '50001', 'C001', '2026-02-01', 'A', 'Completed'),
('E0000002', '50001', 'C002', '2026-02-01', 'B', 'Completed'),
('E0000003', '50001', 'C004', '2026-02-02', 'A', 'Completed'),

('E0000004', '60001', 'C001', '2026-02-01', 'A', 'Completed'),
('E0000005', '60001', 'C003', '2026-02-02', 'B', 'Completed'),
('E0000006', '60001', 'C007', '2026-02-03', 'A', 'Completed'),

('E0000007', '50002', 'C002', '2026-02-01', 'B', 'Completed'),
('E0000008', '50002', 'C004', '2026-02-02', 'A', 'Completed'),
('E0000009', '50002', 'C005', '2026-02-03', 'A', 'Completed'),

('E0000010', '70001', 'C001', '2026-02-01', 'C', 'Completed'),
('E0000011', '70001', 'C005', '2026-02-03', 'B', 'Completed'),

('E0000012', '60002', 'C003', '2026-02-02', 'B', 'Completed'),
('E0000013', '60002', 'C006', '2026-02-03', 'A', 'Completed'),
('E0000014', '60002', 'C007', '2026-02-04', 'B', 'Completed'),

('E0000015', '80001', 'C002', '2026-02-01', 'A', 'Completed'),
('E0000016', '80001', 'C006', '2026-02-03', 'B', 'Completed'),

('E0000017', '70002', 'C004', '2026-02-02', 'A', 'Completed'),
('E0000018', '70002', 'C005', '2026-02-03', 'A', 'Completed'),

('E0000019', '50003', 'C001', '2026-02-01', 'B', 'Completed'),
('E0000020', '50003', 'C007', '2026-02-04', 'A', 'Completed');

-- 1
SELECT s.student_name, s.major, c.course_name, e.final_grade
FROM students s
JOIN enrollments e ON s.student_id = e.student_id
JOIN courses c ON e.course_id = c.course_id
WHERE c.lecturer_name LIKE 'Dr.%';

-- 2
SELECT DISTINCT s.student_id, s.student_name
FROM students s
JOIN enrollments e1 ON s.student_id = e1.student_id
JOIN enrollments e2 ON s.student_id = e2.student_id
WHERE e1.course_id <> e2.course_id AND e1.enrollment_date = e2.enrollment_date;

-- 3
SELECT c.lecturer_name, c.course_name, COUNT(e.student_id) AS student_count
FROM courses c
JOIN enrollments e ON c.course_id = e.course_id
GROUP BY c.lecturer_name, c.course_name;

-- 4
SELECT s.student_name
FROM students s
JOIN payments p ON s.student_id = p.student_id
WHERE p.amount > (
    SELECT AVG(p2.amount)
    FROM payments p2
    JOIN students s2 ON p2.student_id = s2.student_id
    WHERE s2.gender = 'Male'
);

-- 5
SELECT course_name
FROM courses
WHERE semester % 2 = 0;

-- 6
SELECT s.student_id, s.student_name
FROM students s
JOIN enrollments e ON s.student_id = e.student_id
GROUP BY s.student_id, s.student_name
HAVING COUNT(e.course_id) > (
    SELECT AVG(course_count)
    FROM (
        SELECT COUNT(course_id) AS course_count
        FROM enrollments
        GROUP BY student_id
    ) AS avg_table
);

-- 7
SELECT s.student_name, s.major, p.payment_date
FROM students s
JOIN payments p ON s.student_id = p.student_id
WHERE p.payment_date = (SELECT MIN(payment_date) FROM payments);

-- 8
SELECT s.student_name, s.major
FROM students s
JOIN enrollments e ON s.student_id = e.student_id
WHERE e.final_grade = 'A'
GROUP BY s.student_name, s.major
HAVING COUNT(*) > 1;

-- 9
SELECT major
FROM students
GROUP BY major
HAVING COUNT(*) > (
    SELECT MIN(major_count)
    FROM (
        SELECT COUNT(*) AS major_count
        FROM students
        GROUP BY major
    ) AS min_table
);

-- 10
SELECT
    ROUND(SUM(CASE WHEN payment_status = 'Pending' THEN amount ELSE 0 END) / SUM(amount), 3) AS pending_percentage,
    ROUND(SUM(CASE WHEN payment_status = 'Paid' THEN amount ELSE 0 END) / SUM(amount), 3) AS paid_percentage
FROM payments;
