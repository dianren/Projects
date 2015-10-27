xquery version "1.0";

(: Generated with EditiX XML Editor (http://www.editix.com) at Tue Nov 25 22:51:07 PST 2014 :)

let $emp_id1 :=
for $x in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Employee
where $x/empName = "PSmith" 
return $x/empId

let $emp_id2 :=
for $z in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Employee
where $z/empName = "Wong" 
return $z/empId

let $de_id1 :=
for $f in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Division
where $f/managerEmpId = $emp_id1
return $f/housedDeptId

let $de_id2 :=
for $e in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Division
where $e/managerEmpId = $emp_id2
return $e/housedDeptId

let $de_id :=
for $n in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Division
where $n/housedDeptId = $de_id1 and $n/housedDeptId != $de_id2
return $n/housedDeptId

let $d_name :=
for $m in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Department
where $m/deptId = $de_id
return <deptName>{data($m/deptName)}</deptName>

return <query3>{$d_name}</query3>

