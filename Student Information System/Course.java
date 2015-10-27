/*                Course
 * 
 * ----------------------------------------
 * 
 * -name : String
 * -ID : String
 * -Location : String
 * -studentList : ArrayList<Student>
 * -average : double
 * -size : int
 * 
 * ----------------------------------------
 * 
 * +getName() : String
 * +getID() : String
 * +getLocation() : String
 * +getList() : ArrayList<Student>
 * +getAverage() : double
 * +setName(String) : void
 * +setID(String) : void
 * +setLocation(String) : void
 * +setList(ArrayList<Student>) : void
 * +setAverage(double) : void
 * +toString() : String
 * +equals(Course) : boolean
 * +calAverage() : double
 * +removeStu(String, String) : void
 * +dropScores() : void
 * +printList() : void
 * +removeStudents() : void
 * +addStudents() : void
 * +searchStudent() : void
 * +editInformation() : void
 * +sortbyName() : void
 * +sortbyAverage() : void
 * Course()
 * Course(String, String, String, ArrayList<Student>, double)
 * Course(Course)
 * 
 * 
 */







import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Course {
	private String name;
	private String ID;
	private String Location;
	private ArrayList<Student> studentList;
	private double average;
	private int size = 100;
	
	
	public Course()
	{
		name = "no name";
		ID = "no ID";
		Location = "no Location";
		studentList = new ArrayList<Student>();
		average = 0;
	}
	
	public Course(String name, String ID, String Location, ArrayList<Student> studentList, double average)
	{
		this.name = name;
		this.ID = ID;
		this.Location = Location;
		this.studentList = studentList;
		this.average = average;
	}
	
	public Course(Course originalObject)
	{
		name = originalObject.name;
		ID = originalObject.ID;
		Location = originalObject.Location;
		average = originalObject.average;
	}
	
	public String getName()
	{
		return name;
	}
	
	public String getID()
	{
		return ID;
	}
	
	public String getLocation()
	{
		return Location;
	}
	
	public ArrayList<Student> getList()
	{
		return studentList;
	}
	
	public double getAverage()
	{
		return average;
	}
	
	public void setName(String name)
	{
		if(name == null)
		{
			System.out.println("Error creating a course!");
			System.exit(0);
		}
		else
			this.name = name;
	}
	
	public void setID(String ID)
	{
		if(ID == null)
		{
			System.out.println("Error creating a course!");
			System.exit(0);
		}
		else
			this.ID = ID;
	}
	
	public void setLocation(String Location)
	{
		if(Location == null)
		{
			System.out.println("Error creating a course!");
			System.exit(0);
		}
		else
			this.Location = Location;
	}
	
	public void setList(ArrayList<Student> studentList)
	{
		if(studentList.size() == 0)
		{
			System.out.println("Error creating a course!");
			System.exit(0);
		}
		else
			this.studentList = studentList;
	}
	
	public void setAverage(double average)
	{
		if(average < 0)
		{
			System.out.println("Error creating a course!");
			System.exit(0);
		}
		else
			this.average = average;
	}
	
	public String toString()
	{
		return (name + " " + ID + " " + Location + " " + average);
	}
	
	public boolean equals(Course otherCourse)
	{
		return (name.equalsIgnoreCase(otherCourse.name) && ID.equals(otherCourse.ID) && Location.equalsIgnoreCase(otherCourse.Location) && average == otherCourse.average);
	}
	
	public double calAverage()
	{
		int sum = 0;
		for(int i = 0; i < studentList.size(); i++)
		{
			sum += studentList.get(i).calAverage();
		}
		average = sum / studentList.size();
		return average;
	}
	
	public void removeStu(String lastName, String firstName)
	{
		boolean flag = false;
		for(int i = 0; i < studentList.size(); i++)
		{
			if(lastName.equalsIgnoreCase(studentList.get(i).getLastName()) && firstName.equalsIgnoreCase(studentList.get(i).getFirstName()))
			{
				flag = true;
				studentList.remove(i);
			}
		}
		if(flag == true)
		{
			System.out.println("\nYou have successfully removed the student!");
		}
		else
			System.out.println("\nError!! The student is not exist!!");
	}
	
	/*public void addStu(Student newStudent)
	{
		if(studentList.size() == 0)
		{
			studentList.add(newStudent);
		}
		else if(studentList.size() != 0 )
		{
			for(int i = 0; i < studentList.size(); i++)
			{
				if(verify(newStudent) == false)
				{
					studentList.add(newStudent);
				}
				else
				{
					System.out.println("This student has already existed!!");
				}
			}
		}
	}
	
	public boolean verify(Student newStudent)
	{
		boolean c = false;
		for(int i = 0; i < studentList.size(); i++)
		{
			if(newStudent.getLastName().equalsIgnoreCase(studentList.get(i).getLastName()) && newStudent.getFirstName().equalsIgnoreCase(studentList.get(i).getFirstName()))
			{
				c = true;
			}
		}	
		return c;
	}*/
	
	public void dropScores()
	{
		for(int i = 0; i < studentList.size(); i++)
		{
			studentList.get(i).dropScores();
		}
	}
	
	
	
	public void printList()
	{
		DecimalFormat df2 = new DecimalFormat("0.00");
		System.out.println("\n");
		System.out.println("Course Name :     " + getName());
		System.out.println("Course ID :       " + getID());
		System.out.println("Course Location : " + getLocation());
		System.out.println("\nStudents Information:");
		System.out.println("------------------------------------------------------------------------------------------------------------------------------");
		System.out.println("Name\t\t\t" + "ID\t\t\t" + "Average\t\t" + "Grade\t\t" + "Droped\t\t" + "Scores");
		System.out.println("------------------------------------------------------------------------------------------------------------------------------");
		for(int i = 0; i < studentList.size(); i++)
		{
			studentList.get(i).print();
		}
		if(studentList.size() == 0)
		{
			System.out.println("There are no students on the course list!");
			System.exit(0);
		}
		System.out.println("Average score for " + studentList.size() + " students is " + df2.format(calAverage()));
	}
	
	
	
	
	public void removeStudents()
	{
		Scanner	in = new Scanner(System.in);
		System.out.print("\nDo you want to remove students? Y = yes, N = no --> ");
		String deci = in.next();
		if((deci.equalsIgnoreCase("y")))
		{
			if(studentList.size() == 0)
			{
				System.out.println("There are no students on the course list!");
			}
			while(studentList.size() != 0)
			{
				System.out.print("\n");
				System.out.println("Please enter the name of this student!");
				System.out.print("Last Name : ");
				String lastN = in.next();
				System.out.print("First Name : ");
				String firstN = in.next();
				removeStu(lastN, firstN);
				printList();
				System.out.print("\nDo you want to continue remove students? Y/y = yes, N/n = no --> ");
				String de = in.next();
				if((de.equalsIgnoreCase("y")))
				{
					continue;
				}
				else if((de.equalsIgnoreCase("n")))
				{
					System.out.println("\nPlease do other operations!");
					break;
				}
			}
		}
		else if((deci.equalsIgnoreCase("n")))
		{
			System.out.println("\nPlease do other operations!");
		}
	}
	
	
	
	public void addStudents()
	{
		Scanner	in = new Scanner(System.in);
		do
		{
			System.out.print("\nDo you want to add students? Y/y = yes, N/n = no --> ");
			String deci = in.next();
			if(deci.equalsIgnoreCase("y"))
			{
				Student stu = new Student();
				System.out.println("\nPlease enter the name of this student!");
				System.out.print("\nLast Name : ");
				String lastN = in.next();
				stu.setLastName(lastN);
				System.out.print("\nFirst Name : ");
				String firstN = in.next();
				stu.setFirstName(firstN);
				for(int i = 0; i < size; i++)
				{
					System.out.println("\nPlease enter the ID of this student(10 digits) : ");
					String ID = in.next();
					if(ID.length() > 10 || ID.length() < 10)
					{
						System.out.println("Please enter exactly 10 digits!!");
						continue;
					}
					else
					{
						stu.setID(ID);
						break;
					}
				}
				System.out.println("\nPlease enter the scores of this student(should be integer and between 0 and 100. IF not, he will get a grade of I) : ");
				for(int i = 1; i < 9; i ++)
				{
					System.out.println("Test " + i + " : ");
					int testscore = in.nextInt();
					if(testscore < 0 || testscore > 100)
					{
						stu.setGrade("I");
						break;
					}
					else
						stu.addScores(testscore);
				}
				studentList.add(stu);
				if(stu.getScores().size() > 2)
				{
					stu.dropScores();
				}
				printList();
			}
			else if(deci.equalsIgnoreCase("n"))
			{
				System.out.println("\nPlease do other operations!");
				break;
			}
		}while(studentList.size() < size);
	}
	
	
	
	
	public void searchStudent()
	{
		Scanner	in = new Scanner(System.in);
		boolean a = false;
		for (int j = 0; j < size; j++)
		{
			System.out.print("\nDo you want to search students? Y/y = yes, N/n = no --> ");
			String deci = in.next();
			if(deci.equalsIgnoreCase("y"))
			{
				System.out.print("\nPlease enter the last name of this student : ");
				String lastName = in.next();
				for(int i = 0; i < studentList.size(); i++)
				{
					if(lastName.equalsIgnoreCase(studentList.get(i).getLastName()))
					{
						a = true;
						System.out.println("\nThe student is exist! This student's information");
						System.out.println("------------------------------------------------------------------------------------------------------------------------------");
						System.out.println("Name\t\t\t" + "ID\t\t\t" + "Average\t\t" + "Grade\t\t" + "dropedscores\t\t\t" + "Scores");
						System.out.println("------------------------------------------------------------------------------------------------------------------------------");
						studentList.get(i).print();
						break;
					}
					else
						a = false;
				}
				if(a == false)
				{
					System.out.println("\nThe student " + lastName + " is not exist! Please try again!");
				}
			}
			else if((deci.equalsIgnoreCase("n")))
			{
				System.out.println("\nPlease do other operations!");
				break;
			}
		}
	}
	
	
	
	
	public void editInformation()
	{
		Scanner	in = new Scanner(System.in);
		for(int j = 0; j < size; j ++)
		{
			System.out.println();
			System.out.print("Do you want to edit students' information? Y/y = yes, N/y = no --> ");
			String deci = in.next();
			if((deci.equalsIgnoreCase("y")))
			{
				printList();
				System.out.println("\nYou can only edit students' names and socres. Which information do you want to edit?");
				System.out.println("\n1 : Edit student' name.");
				System.out.println("\n2 : Edit student' scores");
				System.out.print("\nPlease enter your choise : ");
				int choise = in.nextInt();
				switch(choise)
				{
					case 1 :
					{
					
						System.out.println("\nHere are the students' names information!");
						for(int i = 0; i < studentList.size(); i ++)
						{
							System.out.println((i + 1) + " : " + studentList.get(i).getLastName() + ", " + studentList.get(i).getFirstName());
						}
						System.out.print("\nWhich student's name do you want to edit? Please enter your choise : ");
						int de = in.nextInt();
						for(int i = 0; i < studentList.size(); i ++)
						{
							if(de == (i + 1))
							{
								String a = studentList.get(i).getLastName();
								String b = studentList.get(i).getFirstName();
								System.out.println("\nThe student's name that you want to edit is " + a + ", " + b + ". Please enter this student's new name!");
								System.out.print("\nEnter new last name : ");
								String newLastName = in.next();
								studentList.get(i).setLastName(newLastName);
								System.out.print("\nEnter new first name : ");
								String newFirstName = in.next();
								studentList.get(i).setFirstName(newFirstName);
								System.out.println("\nYou have done it successfully!!!");
								System.out.println("\nThe student's original name is " + a + ", " + b + ".");
								System.out.println("\nThe student's new name is " + studentList.get(i).getLastName() + ", " + studentList.get(i).getFirstName() + ".");
								printList();
							}
						}
						if(de > (studentList.size()))
						{
							System.out.println("\nError!! Please enter right choise!!!");
						}
						break;
					}
					case 2 :
					{
						System.out.println("\nHere are the students' scores information!");
						for(int i = 0; i < studentList.size(); i ++)
						{
							if(studentList.get(i).calAverage() == 0)
							{
								System.out.println((i + 1) + " : " + studentList.get(i).getScores() + "\t" + "    ------>>" + studentList.get(i).getLastName() + ", " + studentList.get(i).getFirstName());
							}
							else
								System.out.println((i + 1) + " : " + studentList.get(i).getScores() + "------>>" + studentList.get(i).getLastName() + ", " + studentList.get(i).getFirstName());
						}
						System.out.print("\nWhich student's scores do you want to edit? Please enter your choise : ");
						int de = in.nextInt();
						for(int i = 0; i < studentList.size(); i ++)
						{
							ArrayList<Integer> a = studentList.get(i).getScores();
							if(de == (i + 1))
							{
								System.out.println("\nYou select " + studentList.get(i).getLastName() + ", " + studentList.get(i).getFirstName() + "  and his/her scores are " + a);
								System.out.print("\nWhich test score would you want to edit? Please enter your choise(between 1 to 6) : ");
								int ch = in.nextInt();
								for(int n = 0; n < 6; n ++)
								{
									if(ch == (n + 1))
									{
										System.out.println("\nThis is test " + (n + 1) + " and original score is " + a.get(n));
										System.out.print("\nPlease enter the new score of this test : ");
										int sc = in.nextInt();
										studentList.get(i).getScores().set(n, sc);
										System.out.println("\nYou have done it successfully!!!");
										System.out.println("\nThis is test " + (n + 1) + " and new score is " + studentList.get(i).getScores().get(n) + ".");
										System.out.println("\nThis is the student' new scores information.");
										System.out.println("----------------------------------------------------------------");
										System.out.println("\n" + (i + 1) + " : " + studentList.get(i).getScores() + "------>>" + studentList.get(i).getLastName() + ", " + studentList.get(i).getFirstName());
										System.out.println("----------------------------------------------------------------");
									}
								}
								if(ch > 6)
								{
									System.out.println("\nError!! Please enter right choise!!!");
								}
							}
						}
						if(de > (studentList.size()))
						{
							System.out.println("\nError!! Please enter right choise!!!");
						}
						break;
					}
				}
			}
			else 
			{
				break;
			}
		}
	}
	
	
	
	
	
	
	public void sortbyName()
	{
		Scanner	in = new Scanner(System.in);
		for(int c = 0; c < size; c ++)
		{
			System.out.print("\nDo you want to sort students information by their last names? Y/y = yes, N/y = no --> ");
			String deci = in.next();
			if((deci.equalsIgnoreCase("y")))
			{
				System.out.println();
				System.out.println("-----------------------------------------------------------------------");
				System.out.println("There are two kinds of sorting : ascending order and desending order.");
				System.out.println("\n1 : Ascending order.");
				System.out.println("\n2 : Desending order.");
				System.out.println("-----------------------------------------------------------------------");
				System.out.print("\nPlease enter your choise : ");
				int de = in.nextInt();
				switch (de)
				{
					case 1 :
					{
						for(int i = 0; i < studentList.size(); i++)
						{
							for(int j = i + 1; j < studentList.size(); j++)
							{
								if((studentList.get(i).getLastName().compareTo(studentList.get(j).getLastName()))> 0)
								{
									Collections.swap(studentList, i, j);
								}
								else
									continue;
							}
						}
						printList();
						break;
					}
					case 2 :
					{
						for(int i = 0; i < studentList.size(); i++)
						{
							for(int j = i + 1; j < studentList.size(); j++)
							{
								if((studentList.get(i).getLastName().compareTo(studentList.get(j).getLastName()))< 0)
								{
									Collections.swap(studentList, i, j);
								}
								else
									continue;
							}
						}
						printList();
						break;
					}
					
				}
			}
			else
			{
				System.out.println("\n\t\tThe system will return to the homepage.");
				break;
			}
		}
	}
	
	
	
	
	
	
	public void sortbyAverage()
	{
		Scanner	in = new Scanner(System.in);
		for(int c = 0; c < size; c ++)
		{
			System.out.print("\nDo you want to sort students information by their average scores? Y/y = yes, N/y = no --> ");
			String deci = in.next();
			if((deci.equalsIgnoreCase("y")))
			{
				System.out.println();
				System.out.println("-----------------------------------------------------------------------");
				System.out.println("There are two kinds of sorting : ascending order and desending order.");
				System.out.println("\n1 : Ascending order.");
				System.out.println("\n2 : Desending order.");
				System.out.println("-----------------------------------------------------------------------");
				System.out.print("\nPlease enter your choise : ");
				int de = in.nextInt();
				switch (de)
				{
					case 1 :
					{
						for(int i = 0; i < studentList.size(); i++)
						{
							for(int j = i + 1; j < studentList.size(); j++)
							{
								if(studentList.get(i).calAverage() > studentList.get(j).calAverage())
								{
									Collections.swap(studentList, i, j);
								}
								else
									continue;
							}
						}
						printList();
						break;
					}
					case 2 :
					{
						for(int i = 0; i < studentList.size(); i++)
						{
							for(int j = i + 1; j < studentList.size(); j++)
							{
								if(studentList.get(i).calAverage() < studentList.get(j).calAverage())
								{
									Collections.swap(studentList, i, j);
								}
								else
									continue;
							}
						}
						printList();
						break;
					}
				}
			}
			else
			{
				System.out.println("\n\t\tThe system will return to the homepage.");
				break;
			}
		}
	}
	
	
	public void partialSearch()
	{
		Scanner	in = new Scanner(System.in);
		for(int c = 0; c < size; c ++)
		{
			System.out.print("\nDo you want to search students using partial search? Y/y = yes, N/y = no --> ");
			String deci = in.next();
			if((deci.equalsIgnoreCase("y")))
			{
				boolean foundIt = false;
				System.out.print("\nPlease enter the parital name of this student : ");
				String pName = in.next();
				for(int i = 0; i < studentList.size(); i ++)
				{
					
					int L = studentList.get(i).getWholeName().length();
					int b = pName.length();
					for(int j = 0; j <=(L - b); j++)
					{
						
					//	System.out.print(studentList.get(i).getWholeName());
						if((studentList.get(i).getWholeName()).regionMatches(true, j, pName, 0, b))
						{
							//System.out.print(studentList.get(i).getWholeName());
							foundIt = true;
							studentList.get(i).print();
							break;
						}
					}
				}
				if(!foundIt)
					System.out.println("No match found.");
			}
			else
			{
				System.out.println("\n\t\tThe system will return to the homepage.");
				break;
			}
		}	
	}
}
	


	
	



