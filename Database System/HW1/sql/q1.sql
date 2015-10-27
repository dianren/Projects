SELECT  DIANVFEA.VILLA_ID, DIANVFEA.FEATURES
FROM DIANVFEA JOIN
DIANVILLA ON DIANVFEA.VILLA_ID = dianvilla.villa_id
WHERE DIANVFEA.FEATURES = 'Fea2'
AND DIANVFEA.FEATURES != 'Fea6'
;