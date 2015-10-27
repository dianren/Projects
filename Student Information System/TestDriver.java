import java.util.Scanner;
import java.io.*;
import java.util.ArrayList;

public class TestDriver 
{
	static Course course = new Course();
	static ArrayList<Student> studentList = new ArrayList<Student>();
	static int size = 100;
	static Scanner	in = new Scanner(System.in);
	
	
	public static void main(String[] args)
	{
		
		readFile();
		course.setList(studentList);
		printFile();
		course.dropScores();
		menu();
	}
	

	
	
	public static void menu()
	{
		System.out.println("\n\n\n\n\t\tWELCOME TO STUDENT COURSE SYSTEM!");
		System.out.println("-------------------------------------------------------------------");
		OK:
		for(int i = 0; i < size; i ++)
		{
			System.out.println("\n");
			System.out.println("\t\t\tHomepage            ");
			System.out.println("-------------------------------------------------------------------");
			System.out.println("\t\t1 : Exit the system.");
			System.out.println("\t\t2 : Print the course list.");
			System.out.println("\t\t3 : Add students.");
			System.out.println("\t\t4 : Remove students.");
			System.out.println("\t\t5 : Search students(According to last name).");
			System.out.println("\t\t6 : Edit students information.");
			System.out.println("\t\t7 : Sorting students according last name.");
			System.out.println("\t\t8 : Sorting students according average scores.");
			System.out.println("\t\t9 : Partial name search.");
			System.out.println("-------------------------------------------------------------------");
			System.out.print("\nPlease enter your choose : ");
			int deci = in.nextInt();
		    switch(deci)
		    {
		    	case 1 :
		    		System.out.println("\nThank you for using!!!");
		    		break OK;
		    	case 2 :
		    		course.printList();
		    		System.out.println("\n\t\tThe system will return to the homepage.");
		    		break;
		    	case 3 :
		    		course.addStudents();
		    		break;
		    	case 4 :
		    		course.removeStudents();
		    		break;
		    	case 5 : 
		    		course.searchStudent();
		    		break;
		    	case 6 :
		    		course.editInformation();
		    		break;
		    	case 7 :
		    		course.sortbyName();
		    		break;
		    	case 8 :
		    		course.sortbyAverage();
		    		break;
		    	case 9 :
		    		course.partialSearch();
		    }
		}
	}
	
	
	
	
	public static void readFile()
	{
		String fName, temp, name, ID, Location;
		String[] stuWholeName = new String[200];
		String[] stuFirstName = new String[200];
		String[] stuLastName = new String[200];
		String[] stuID = new String[200];
		int[] test = new int[200];
		Student[] stu = new Student[200];
		Scanner kb = new Scanner(System.in);
		for(int c = 0; c < size; c ++)
		{
			System.out.println("\nEnter input file name : ");
			fName = kb.nextLine();
			File file = new File(TestDriver.class.getClassLoader().getResource("").getPath() + fName);
			String a = "student_data.txt";
			if(!fName.equals(a))
			{
				System.out.println("\nFile name is wrong!! Please enter right name!!");
			}
			else
			{
				System.out.println("\nCongratulations!! You have read the file and You will go to the homepage.");
				try
				{
					Scanner in = new Scanner(file);
					while(in.hasNextLine())
					{
						String[] tmp = null;
						name = in.nextLine();
						course.setName(name);
						ID = in.nextLine();
						course.setID(ID);
						Location = in.nextLine();
						course.setLocation(Location);
						for(int i = 0; i < 6; i ++)
						{
							stu[i] = new Student();
							stuWholeName[i] = in.nextLine();
							stu[i].setWholeName(stuWholeName[i]);
							tmp = stuWholeName[i].split(" ");
							stuFirstName[i] = tmp[0];
							stu[i].setFirstName(stuFirstName[i]);
							stuLastName[i] = tmp[1];
							stu[i].setLastName(stuLastName[i]);
							stuID[i] = in.next();
							stu[i].setID(stuID[i]);
							for(int j = 0; j < 8; j ++)
							{
								test[j] = in.nextInt();
								stu[i].addScores(test[j]);
							}
							temp = in.nextLine();
							studentList.add(stu[i]);
						}
						//System.out.println(stuLastName);
					}
				}
				catch(FileNotFoundException e)
				{
					e.printStackTrace();
				}
				break;
			}
		}
	}
	
	
	
	
	public static void printFile()
	{
		System.out.println("\n");
		System.out.println("The datas in the original file are the following :");
		System.out.println("-------------------------------------------------");
		System.out.println(course.getName());
		System.out.println(course.getID());
		System.out.println(course.getLocation());
		for(int i = 0; i < studentList.size(); i ++)
		{
			System.out.println(studentList.get(i).getFirstName() + " " + studentList.get(i).getLastName());
			System.out.print(studentList.get(i).getID() + " ");
			for(int j = 0; j < 8; j ++)
			{
				System.out.print(studentList.get(i).getScores().get(j) + " ");
			}
			System.out.println();
		}
		System.out.println("-------------------------------------------------");
	}
}

	

	
	