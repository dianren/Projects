

SELECT BBB.ID, BBB.FIRST_NAME, BBB.LAST_NAME
FROM (SELECT USER_ID, SUM(DEPOSIT)AS TOTAL
FROM (SELECT *
FROM DIANRESERVATION
WHERE END_DATE LIKE '%13')
GROUP BY USER_ID
ORDER BY SUM(DEPOSIT)DESC)AAA JOIN DIANUSER BBB ON AAA.USER_ID = BBB.ID
WHERE ROWNUM <=3
;