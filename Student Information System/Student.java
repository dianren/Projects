/*               Student
 * 
 * -------------------------------------
 * 
 * -Scores : ArrayList<Integer>
 * -Grade : String
 * -Average : double
 * -twolowestScores : int[]
 * 
 * -------------------------------------
 * 
 * +getScores() : ArrayList<Integer>
 * +getGrade() : String
 * +getAverage() : double
 * +setScores(ArrayList<Integer>) : void
 * +setGrade(String) : void
 * +setAverage(double) : void
 * +calAverage() : double
 * +calGrade() : String
 * +toString() : String
 * +equals(Student) : boolean
 * +print() : void
 * +addScores(Integer) : void
 * +dropScores() : int[]
 * +printdropScores() : String
 * Student()
 * Student(String, String, String, String, ArrayList<Integer>, String, double)
 * Student(Student)
 * 
 */












import java.text.DecimalFormat;
import java.util.ArrayList;

public class Student extends Person 
{
	
	private ArrayList<Integer> Scores;
	private String Grade;
	private double Average;
	private int[] twolowestScores = new int[2];
	
	public Student()
	{
		super();
		Scores = new ArrayList<Integer>();
		Grade = "";
		Average = 0;
	}
	
	public Student(String lastName, String firstName, String wholeName, String ID, ArrayList<Integer> Scores, String Grade, double Average)
	{
		super(lastName, firstName, wholeName, ID);
		this.Scores = Scores;
		this.Grade = Grade;
		this.Average = Average;
	}
	
	public Student(Student originalObject)
	{
		super(originalObject);
		Scores = originalObject.Scores;
		Grade = originalObject.Grade;
		Average = originalObject.Average;
	}
	
	public ArrayList<Integer> getScores()
	{
		return Scores;
	}
	
	public String getGrade()
	{
		return Grade;
	}
	
	public double getAverage()
	{
		return Average;
	}
	
	public void setScores(ArrayList<Integer> Scores)
	{
		if(Scores.size() == 0)
		{
			System.out.println("Error creating a score!");
			System.exit(0);
		}
		this.Scores = Scores;
	}
	
	public void setGrade(String Grade)
	{
		if(Grade == null)
		{
			System.out.println("Error creating a student!");
			System.exit(0);
		}
		else
			this.Grade = Grade;
	}
	
	public void setAverage(double Average)
	{
		if(Average < 0)
		{
			System.out.println("Error creating a student!");
			System.exit(0);
		}
		else
			this.Average = Average;
	}
	
	

	
	public double calAverage()
	{
		int sum = 0;
		if(Scores.size() < 6)
		{
			Average = 0;
		}
		else
		{
			for(int i = 0; i < Scores.size(); i++)
			{
				sum += Scores.get(i);
			}
			Average = (sum * 1.0) / Scores.size();
		}
		return Average;
	}
	
	public void belowSixScores()
	{
		if(Scores.size() < 6)
		{
			Average = 0;
		}
	}
	
	public String calGrade()
	{
		double ave = calAverage();
		if(Scores.size() < 6 || ave <= 0 || ave > 100)
		{
			Grade = "I";
		}
		else if(ave < 60)
		{
			Grade = "F";
		}
		else if(ave >= 60 && ave < 70)
		{
			Grade = "D";
		}
		else if(ave >= 70 && ave < 80)
		{
			Grade = "C";
		}
		else if(ave >= 80 && ave < 83)
		{
			Grade = "B";
		}
		else if(ave >= 83 && ave < 87)
		{
			Grade = "B+";
		}
		else if(ave >= 87 && ave < 90)
		{
			Grade = "A-";
		}
		else if(ave >= 90 && ave < 100)
		{
			Grade = "A";
		}
		return Grade;
	}
	
	public String toString()
	{
		return (getLastName() + ", " + getFirstName() + "\t" + getID() + "\t" + Average + "\t" + Grade);
	}
	
	public boolean equals(Student otherStudent)
	{
		return (getLastName().equalsIgnoreCase(otherStudent.getLastName()) && getFirstName().equalsIgnoreCase(otherStudent.getFirstName()) && getID().equals(otherStudent.getID()) && Average == otherStudent.Average && Grade.equals(otherStudent.Grade));
	}
	
	
	public void print()
	{
		//dropScores();
		DecimalFormat df2 = new DecimalFormat("0.00");
		if(calAverage() == 0)
		{
			System.out.println(getLastName() + ", " + getFirstName() + "\t\t" + getID() + "\t\t" + df2.format(calAverage()) + "\t\t  " + calGrade() + "\t\t" + printdropScores()  + "\t\t" + getScores());
			//System.out.println("sssssssssssssssssssssssss");
			System.out.println("------------------------------------------------------------------------------------------------------------------------------");
		}
		else
		{
			System.out.println(getLastName() + ", " + getFirstName() + "\t\t" + getID() + "\t\t" + df2.format(calAverage()) + "\t\t  " + calGrade() + "\t\t" + printdropScores()  + "\t" + getScores());
			System.out.println("------------------------------------------------------------------------------------------------------------------------------");
		}
	}
	
	public void addScores(Integer grade)
	{
		Scores.add(grade);
	}
	
	public int[] dropScores()
	{
		
		for(int j=0; j<2; j++){
			int minIndex = 0;
			int min = Scores.get(0);
			for(int index = 1; index < Scores.size(); index++)
			{
				
				if(Scores.get(index) < min)
				{
					min = Scores.get(index);
					minIndex = index;
				}
			}
			
			twolowestScores[j] = min;
			Scores.remove(minIndex);
		}
		return twolowestScores;
	}
	
	
	public String printdropScores()
	{
		return ("[" + twolowestScores[0] + ", " + twolowestScores[1] + "]");
	}
	
		
		
		
	
}
