xquery version "1.0";


let $emp_id :=
for $x in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Employee
where $x/empName = "PSmith" or $x/empName = "Jack"
return $x/empId

let $div_id :=
for $y in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/WorksFor
where $y/percentTime>=50 and $y/empId = $emp_id 
return $y/divId

let $dept_id :=
for $z in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Division
where $z/divId = $div_id
return $z/housedDeptId

let$name :=
for $m in doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Department
where $m/deptId = $dept_id
return <deptName>{data($m/deptName)}</deptName>

return <query1>{$name}</query1>
