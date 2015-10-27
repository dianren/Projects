xquery version "1.0";

(: Generated with EditiX XML Editor (http://www.editix.com) at Wed Nov 26 01:07:51 PST 2014 :)


let $m_id :=
for $x in distinct-values(doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Division/managerEmpId)
return $x

for $y in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Employee
where not($y/empId = $m_id)
return <query4>{<empName>{data($y/empName)}</empName>, '&#xa;' ,<empPhone>{data($y/empPhone)}</empPhone>, '&#xa;',  <empOffice>{data($y/empOffice)}</empOffice>}</query4>


