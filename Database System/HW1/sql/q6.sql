


SELECT AAA.VILLA_ID, AAA.NAME, AAA.OWNER, BBB.FIRST_NAME, BBB.LAST_NAME, AAA.AVGRATE
FROM (SELECT B.VILLA_ID, B.NAME, B.OWNER, A.AVGRATE
FROM (SELECT VILLA_ID, AVG(RATING)AS AVGRATE
FROM DIANREVIEW
GROUP BY VILLA_ID
ORDER BY AVG(RATING)DESC) A JOIN DIANVILLA B ON A.VILLA_ID = B.VILLA_ID
WHERE ROWNUM <= 3) AAA
JOIN DIANUSER BBB ON AAA.OWNER = BBB.ID
ORDER BY AAA.AVGRATE DESC
;