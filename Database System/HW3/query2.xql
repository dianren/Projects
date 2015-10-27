xquery version "1.0";

(: Generated with EditiX XML Editor (http://www.editix.com) at Tue Nov 25 21:59:42 PST 2014 :)


let $div_id :=

for $x in distinct-values(doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/WorksFor/divId)
where count(doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/WorksFor[divId =$x]) 
= count(doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Employee/empId)
return $x

let $name :=	
for $z in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Division
where $z/divId = $div_id
return <divName>{data($z/divName)}</divName>

return <query2>{$name}</query2>
