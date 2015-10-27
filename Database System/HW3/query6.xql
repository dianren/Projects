xquery version "1.0";

(: Generated with EditiX XML Editor (http://www.editix.com) at Tue Nov 25 23:09:28 PST 2014 :)


let $emp_id :=
(for $x in distinct-values(doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/WorksFor/empId)
order by count(doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/WorksFor[empId =$x]) descending
return $x)[1]
	
for $y in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Employee
where $y/empId = $emp_id
return <query6>{<empName>{data($y/empName)}</empName>, '&#xa;' ,<empPhone>{data($y/empPhone)}</empPhone>, '&#xa;',  <empOffice>{data($y/empOffice)}</empOffice>}</query6>


