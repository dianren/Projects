package CS585HW2;

//import java.beans.Statement;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class HW2 {

  private static Connection conn = null;
  private final String connection;
  private final String username;
  private final String password; 
  private static java.sql.Statement stmt = null;

  HW2(String username,String password,String connection) {
      this.username = username;
      this.password = password;
      this.connection = connection;
  }
  
  void getDBConnection() {
      try {
          DriverManager.registerDriver(

new oracle.jdbc.OracleDriver());
      } catch (SQLException ex) {
          System.out.println("Please install Oracle Driver.");
          return;
      }
      try {
          conn = DriverManager.getConnection(connection, username, password);
      } catch (SQLException e) {
          System.out.println(e);
          return;
      }
      if (conn != null) {
          System.out.println("Connection Succeeded.");
          System.out.println();
      } else {
          System.out.println("Connection failed.");
          System.out.println();
      }
  }
  
/**
   * @param args the command line arguments
* @throws SQLException 
   */
  public static void main(String[] args) 
  {
      /////////////////  connected ////////////////////
  	
	    HW2 obj = new HW2("system", "3983150002Rd", "jdbc:oracle:thin:@localhost:1521:orcl");
      obj.getDBConnection();
      
      ///////////// begin to query ///////////////////////
      
      String query_type = args[0];
      //String object_type = args[1];
      ResultSet rs = null;
      if(query_type.equals("window"))
      {
      	window(args[1], rs, args[2], args[3], args[4], args[5]);
      }
      else if(query_type.equals("within"))
      {
      	within(rs, args[1], args[2]);
      }
      else if(query_type.equals("nearest-neighbor"))
      {
      	NN(args[1], rs, args[2], args[3]);
      }
      else if(query_type.equals("fixed"))
      {
      	fixed(args[1]);
      }
   }




  public static void window(String object_type, ResultSet rs, String x1, String y1, String x2, String y2)
  {
  	
  	try 
      {
       	
       	stmt = conn.createStatement();
       	
       	if(object_type.equals("building"))
			{
				//System.out.println("building");
				String sql;
				sql = "SELECT B.BU_ID FROM HW2BUILDINGS B "
					+ "WHERE SDO_FILTER(B.BU_SHAPE, "
					+ "SDO_GEOMETRY(2003, NULL, NULL, SDO_ELEM_INFO_ARRAY(1, 1003, 3), "
					+ "SDO_ORDINATE_ARRAY("+x1+", "+y1+", "+x2+", "+y2+"))) = 'TRUE' "
					+ "ORDER BY B.BU_ID";
				//System.out.println(sql);
				rs = stmt.executeQuery(sql);
				int count = 0;
				while (rs.next()) 
				{
					String id = rs.getString("BU_ID");
					System.out.println("building" + count +" : " + id);
					count++;
				}
			}
       	else if(object_type.equals("student"))
       	{
       		String sql;
				sql = "SELECT S.STU_ID FROM HW2STUDENTS S "
					+ "WHERE SDO_FILTER(S.STU_SHAPE, "
					+ "SDO_GEOMETRY(2003, NULL, NULL, SDO_ELEM_INFO_ARRAY(1, 1003, 3), "
					+ "SDO_ORDINATE_ARRAY("+x1+", "+y1+", "+x2+", "+y2+"))) = 'TRUE' "
					+ "ORDER BY S.STU_ID";
				//System.out.println(sql);
				rs = stmt.executeQuery(sql);
				int count = 0;
				while (rs.next()) 
				{
					String id = rs.getString("STU_ID");
					System.out.println("student" + count +" : " + id);
					count++;
				}
       	}
       	else if(object_type.equals("tramstops"))
       	{
       		String sql;
				sql = "SELECT T.TRAMS_ID FROM HW2TRAMSTOPS T "
					+ "WHERE SDO_FILTER(T.TRAMS_SHAPE, "
					+ "SDO_GEOMETRY(2003, NULL, NULL, SDO_ELEM_INFO_ARRAY(1, 1003, 3), "
					+ "SDO_ORDINATE_ARRAY("+x1+", "+y1+", "+x2+", "+y2+"))) = 'TRUE' "
					+ "ORDER BY T.TRAMS_ID";
				//System.out.println(sql);
				rs = stmt.executeQuery(sql);
				while (rs.next()) 
				{
					String id = rs.getString("TRAMS_ID");
					System.out.println(id);
				}
       	}
       }
  	 catch (SQLException e)
       {
       	System.out.println(e);
       	return;
       }
  }
  
  
  
  public static void within(ResultSet rs, String s, String n)
  {

  	try 
      {
       	
       	stmt = conn.createStatement();
       	
       	//System.out.println("building");
			String sql;
			sql = "SELECT BU_ID FROM HW2BUILDINGS "
					+ "WHERE SDO_WITHIN_DISTANCE(BU_SHAPE,  "
					+ "(SELECT STU_SHAPE FROM HW2STUDENTS WHERE STU_ID = '" + s + "'), "
					+ "'distance = " + n + "') = 'TRUE' "
					+ "UNION "
					+ "SELECT TRAMS_ID FROM HW2TRAMSTOPS "
					+ "WHERE SDO_WITHIN_DISTANCE(TRAMS_SHAPE,  "
					+ "(SELECT STU_SHAPE FROM HW2STUDENTS WHERE STU_ID = '" + s + "'), "
					+ "'distance = " + n + "') = 'TRUE'";
				//System.out.println(sql);
				rs = stmt.executeQuery(sql);
				while (rs.next()) 
				{
					String id = rs.getString("BU_ID");
					System.out.println(id);
				}
			
     
       }
  	 catch (SQLException e)
       {
       	System.out.println(e);
       	return;
       }
  }
  
  
  public static void NN(String object_type, ResultSet rs, String s, String n)
  {
  	try 
      {
       	
       	stmt = conn.createStatement();
       	int n1 = Integer.parseInt(n);
       	int n2 = n1 + 1;
       	String n3 = String.valueOf(n2);
       	
       	if(object_type.equals("building"))
			{
				//System.out.println("building");
				String sql;
				sql = "SELECT BU_ID FROM HW2BUILDINGS "
					+ "WHERE SDO_NN(BU_SHAPE, "
					+ "(SELECT BU_SHAPE FROM HW2BUILDINGS WHERE BU_ID = '" + s + "'), "
					+ "'SDO_NUM_RES = " + n3 + "') = 'TRUE' AND BU_ID <> '" + s + "'";
				//System.out.println(sql);
				rs = stmt.executeQuery(sql);
				while (rs.next()) 
				{
					String id = rs.getString("BU_ID");
					System.out.println(id);
				}
			}
       	else if(object_type.equals("student"))
       	{
       		String sql;
				sql = "SELECT STU_ID FROM HW2STUDENTS "
	 					+ "WHERE SDO_NN(STU_SHAPE, "
	 					+ "(SELECT STU_SHAPE FROM HW2STUDENTS WHERE STU_ID = '" + s + "'), "
	 					+ "'SDO_NUM_RES = " + n3 + "') = 'TRUE' AND STU_ID <> '" + s + "'";
				//System.out.println(sql);
				rs = stmt.executeQuery(sql);
				while (rs.next()) 
				{
					String id = rs.getString("STU_ID");
					System.out.println(id);
				}
       	}
       	else if(object_type.equals("tramstops"))
       	{
       		String sql;
				sql = "SELECT TRAMS_ID FROM HW2TRAMSTOPS "
	 					+ "WHERE SDO_NN(TRAMS_SHAPE, "
	 					+ "(SELECT TRAMS_SHAPE FROM HW2TRAMSTOPS WHERE TRAMS_ID = '" + s + "'), "
	 					+ "'SDO_NUM_RES = " + n3 + "') = 'TRUE' AND TRAMS_ID <> '" + s + "'";
				//System.out.println(sql);
				rs = stmt.executeQuery(sql);
				while (rs.next()) 
				{
					String id = rs.getString("TRAMS_ID");
					System.out.println(id);
				}
       	}
       }
  	 catch (SQLException e)
       {
       	System.out.println(e);
       	return;
       }
  }
  
  
  public static void fixed(String object_type)
  {
  	if(object_type.equals("1"))
  	{
  		fixedquery1();
  	}
  	else if(object_type.equals("2"))
  	{
  		fixedquery2();
  	}
  	else if(object_type.equals("3"))
  	{
  		fixedquery3();
  	}
  	else if(object_type.equals("4"))
  	{
  		fixedquery4();
  	}
  	else if(object_type.equals("5"))
  	{
  		fixedquery5();
  	}
  }
  
  
  
  
  public static void fixedquery1()
  {
  	//System.out.println("111111111111111111");
  	try 
      {
  		ResultSet rs;
       	stmt = conn.createStatement();
       	String sql;
			sql = "SELECT STU_ID FROM HW2STUDENTS "
				+ "WHERE SDO_WITHIN_DISTANCE(STU_SHAPE, (SELECT TRAMS_SHAPE FROM HW2TRAMSTOPS WHERE TRAMS_ID = 't2ohe'), 'distance = 70') = 'TRUE' "
				+ "INTERSECT "
				+ "SELECT STU_ID FROM HW2STUDENTS "
				+ "WHERE SDO_WITHIN_DISTANCE(STU_SHAPE, (SELECT TRAMS_SHAPE FROM HW2TRAMSTOPS WHERE TRAMS_ID = 't6ssl'), 'distance = 50') = 'TRUE' "
				+ "UNION "
				+ "SELECT BU_ID FROM HW2BUILDINGS "
				+ "WHERE SDO_WITHIN_DISTANCE(BU_SHAPE, (SELECT TRAMS_SHAPE FROM HW2TRAMSTOPS WHERE TRAMS_ID = 't2ohe'), 'distance = 70') = 'TRUE' "
				+ "INTERSECT "
				+ "SELECT BU_ID FROM HW2BUILDINGS "
				+ "WHERE SDO_WITHIN_DISTANCE(BU_SHAPE, (SELECT TRAMS_SHAPE FROM HW2TRAMSTOPS WHERE TRAMS_ID = 't6ssl'), 'distance = 50') = 'TRUE'";
			//System.out.println(sql);
			rs = stmt.executeQuery(sql);
			
			while (rs.next()) 
			{
				String id = rs.getString("BU_ID");
				if(id.isEmpty())
				{
					System.out.println("no results!");
				}
			}
      }
  	catch (SQLException e)
      {
      	System.out.println(e);
      	return;
      }
			
  }
  
  
  public static void fixedquery2()
  {
  	//System.out.println("111111111111111111");
  	try 
      {
  		ResultSet rs;
       	stmt = conn.createStatement();
       	String sql;
			sql = "SELECT S.STU_ID, T.TRAMS_ID FROM HW2STUDENTS S, HW2TRAMSTOPS T "
				+ "WHERE SDO_NN(T.TRAMS_SHAPE, S.STU_SHAPE, 'SDO_NUM_RES = 2') = 'TRUE'";
			//System.out.println(sql);
			rs = stmt.executeQuery(sql);
			while (rs.next()) 
			{
				String sid = rs.getString("STU_ID");
				String tid = rs.getString("TRAMS_ID");
				System.out.print(sid + "	");
				System.out.println(tid);
			}
      }
  	catch (SQLException e)
      {
      	System.out.println(e);
      	return;
      }
			
  }
  
  
  public static void fixedquery3()
  {
  	//System.out.println("111111111111111111");
  	try 
      {
  		ResultSet rs;
       	stmt = conn.createStatement();
       	String sql;
			sql = "SELECT * "
				+ "FROM(SELECT T.TRAMS_ID, COUNT(B.BU_ID) AS NUM FROM HW2TRAMSTOPS T, HW2BUILDINGS B "
				+ "WHERE SDO_WITHIN_DISTANCE(B.BU_SHAPE, T.TRAMS_SHAPE, 'distance = 250') = 'TRUE' "
				+ "GROUP BY T.TRAMS_ID "
				+ "ORDER BY COUNT(B.BU_ID) DESC) "
				+ "WHERE ROWNUM = 1";
			//System.out.println(sql);
			rs = stmt.executeQuery(sql);
			while (rs.next()) 
			{
				String tid = rs.getString("TRAMS_ID");
				String bnum = rs.getString("NUM");
				System.out.print(tid + "	");
				System.out.println(bnum);
			}
      }
  	catch (SQLException e)
      {
      	System.out.println(e);
      	return;
      }
			
  }
  
  
  
  public static void fixedquery4()
  {
  	//System.out.println("111111111111111111");
  	try 
      {
  		ResultSet rs;
       	stmt = conn.createStatement();
       	String sql;
			sql = "SELECT * "
				+ "FROM(SELECT S.STU_ID, COUNT(B.BU_ID) AS NUM FROM HW2STUDENTS S, HW2BUILDINGS B "
				+ "WHERE SDO_NN(S.STU_SHAPE, B.BU_SHAPE, 'SDO_NUM_RES = 1') = 'TRUE' "
				+ "GROUP BY S.STU_ID "
				+ "ORDER BY COUNT(B.BU_ID) DESC) "
				+ "WHERE ROWNUM <= 5";
			//System.out.println(sql);
			rs = stmt.executeQuery(sql);
			while (rs.next()) 
			{
				String sid = rs.getString("STU_ID");
				String bnum = rs.getString("NUM");
				System.out.print(sid + "	");
				System.out.println(bnum);
			}
      }
  	catch (SQLException e)
      {
      	System.out.println(e);
      	return;
      }
			
  }
  
  
  public static void fixedquery5()
  {
  	//System.out.println("111111111111111111");
  	try 
      {
  		ResultSet rs;
       	stmt = conn.createStatement();
       	String sql;
			sql = "SELECT MIN(SDO_GEOM.SDO_MIN_MBR_ORDINATE(B.BU_SHAPE, U.DIMINFO, 1)) AS X1,"
				+ "MIN(SDO_GEOM.SDO_MIN_MBR_ORDINATE(B.BU_SHAPE, U.DIMINFO, 2)) AS Y1, "
				+ "MAX(SDO_GEOM.SDO_MAX_MBR_ORDINATE(B.BU_SHAPE, U.DIMINFO, 1)) AS X2, "
				+ "MAX(SDO_GEOM.SDO_MAX_MBR_ORDINATE(B.BU_SHAPE, U.DIMINFO, 2)) AS Y2 "
				+ "FROM HW2BUILDINGS B, USER_SDO_GEOM_METADATA U "
				+ "WHERE U.TABLE_NAME = 'HW2BUILDINGS' AND COLUMN_NAME = 'BU_SHAPE' AND B.BU_NAME LIKE 'SS%'";
			//System.out.println(sql);
			rs = stmt.executeQuery(sql);
			while (rs.next()) 
			{
				String leftx = rs.getString("X1");
				String lefty = rs.getString("Y1");
				String upx = rs.getString("X2");
				String upy = rs.getString("Y2");
				System.out.print(leftx + "	");
				System.out.print(lefty + "	");
				System.out.print(upx + "	");
				System.out.println(upy + "	");
				//System.out.println(bnum);
			}
      }
  	catch (SQLException e)
      {
      	System.out.println(e);
      	return;
      }
			
  }
}
