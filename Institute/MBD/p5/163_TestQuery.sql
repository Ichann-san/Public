-- Active: 1761461509284@@127.0.0.1@3306@quiz1

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
