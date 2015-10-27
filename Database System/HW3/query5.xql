xquery version "1.0";

(: Generated with EditiX XML Editor (http://www.editix.com) at Wed Nov 26 00:51:02 PST 2014 :)

<query5><average>{sum(for $x in distinct-values(doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/WorksFor/empId)
return count(doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/WorksFor[empId =$x])) 
div count(doc("/Users/dianren/Desktop/CS585/hw/hw3/myhw/company.xml")/company/Employee/empId)}</average></query5>
