<?xml version="1.0" encoding="UTF-8"?>


<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<html>
			<body style="font-family:Aria">
				<h1 style="font-size:24pt;background-color:Yellow;font-weight:bold;color:red">Employee</h1>
				<p>
					Employee <b>&lt;name&gt;</b> 
					works from <b>&lt;office&gt;</b> office. 
					<b>&lt;name&gt;</b> works for <b>&lt;no. of divs&gt;</b> division(s),
					which are <b>&lt;divisionName1, divisionName2, ... , and divisionNameN&gt;</b>. <b>&lt;name&gt;</b> manages <b>&lt;no. of divs managed&gt;</b> division(s), 
					which are <b>&lt;managedDivisionName1, managedDivisionName2, ... , and managedDivisionNameN&gt;</b>. 
					<b>&lt;name&gt;</b> works for the most time with the <b>&lt;divisionName&gt;</b> division.
				</p>
				<p>
				<div style="font-size:12pt">
				<xsl:for-each select="/company/Employee">
					Employee <b><xsl:value-of select="empName"/></b> 
					works from <b><xsl:value-of select="empOffice"/></b>. 
					<b><xsl:value-of select="empName"/></b> works for 
					<b>
					<xsl:variable name="arr" select ="empId"/>
					<xsl:value-of select="count(/company/WorksFor[empId=$arr])"/>
					</b>
					division(s), which are 
					<b>
					<xsl:variable name="arr1" select ="empId"/>
					<xsl:for-each select="/company/WorksFor[empId=$arr1]/divId">
						<xsl:choose>
  							<xsl:when test="(last()-1)=position()">
								<xsl:variable name="arr2" select ="."/>
								<xsl:value-of select="/company/Division[divId=$arr2]/divName"/>
								<xsl:text> and </xsl:text>
							</xsl:when>
							<xsl:when test="last()=position()">
								<xsl:variable name="arr2" select ="."/>
								<xsl:value-of select="/company/Division[divId=$arr2]/divName"/>
								<xsl:text>. </xsl:text>
							</xsl:when>	
							<xsl:otherwise>
								<xsl:variable name="arr2" select ="."/>
								<xsl:value-of select="/company/Division[divId=$arr2]/divName"/>
								<xsl:text>, </xsl:text>
							</xsl:otherwise>
						</xsl:choose>
					</xsl:for-each>
					
					</b>
					<b><xsl:value-of select="empName"/></b> manages
					<b>
					<xsl:variable name="arr3" select ="empId"/>
					<xsl:value-of select="count(/company/Division[managerEmpId=$arr3])"/>
					</b>
					division(s), which are
					<b>
					<xsl:variable name="arr4" select ="empId"/>
					<xsl:for-each select="/company/Division[managerEmpId=$arr4]/divName">
						<xsl:choose>
  							<xsl:when test="(last()-1)=position()">
								<xsl:value-of select="."/>
								<xsl:text> and </xsl:text>
							</xsl:when>
							<xsl:when test="last()=position()">
								<xsl:value-of select="."/>
								<xsl:text>. </xsl:text>
								
							</xsl:when>
							<xsl:otherwise>
								<xsl:value-of select="."/>
								<xsl:text>, </xsl:text>
							</xsl:otherwise>
						</xsl:choose>
					</xsl:for-each>
					</b>
					<b><xsl:value-of select="empName"/></b> works for the most time with the
					<b>
					<xsl:variable name="arr5" select ="empId"/>
					<xsl:for-each select="/company/WorksFor[empId=$arr5]">
						<xsl:sort select="percentTime" order="descending"/>
						<xsl:if test="position()=1">
							<xsl:variable name="arr6" select ="divId"/>
							<xsl:value-of select="/company/Division[divId=$arr6]/divName"/>
						</xsl:if>
					</xsl:for-each>
					</b>.
					<br/>
				</xsl:for-each>
				</div>
				</p>
				
				

				<h1 style="font-size:24pt;background-color:LightGreen;font-weight:bold;color:red">Department</h1>
				<p>
					Department <b>&lt;department name&gt;</b> 
					houses <b>&lt;no. of divisions&gt;</b>
					division(s): <b>&lt;housedDivisionName1, housedDivisionName2, ..., and housedDivisionNameN.&gt;</b>
				</p>
				<p>
				<div style="font-size:12pt">
				<xsl:for-each select="/company/Department">
					Department <b><xsl:value-of select="deptName"/></b> houses
					<b>
					<xsl:variable name="brr" select ="deptId"/>
					<xsl:value-of select="count(/company/Division[housedDeptId=$brr])"/>
					</b>
					division(s):
					<b>
					<xsl:variable name="brr1" select ="deptId"/>
					<xsl:for-each select="/company/Division[housedDeptId=$brr1]/divName">
						<xsl:choose>
  							<xsl:when test="(last()-1)=position()">
								<xsl:value-of select="."/>
								<xsl:text> and </xsl:text>
							</xsl:when>
							<xsl:when test="last()=position()">
								<xsl:value-of select="."/>
								<xsl:text>.</xsl:text>
								
							</xsl:when>
							<xsl:otherwise>
								<xsl:value-of select="."/>
								<xsl:text>, </xsl:text>
							</xsl:otherwise>
						</xsl:choose>
					</xsl:for-each>	
					</b>
					<br/>
				</xsl:for-each>
				</div>
				</p>
			</body>
		</html>
	</xsl:template>	
</xsl:stylesheet>

