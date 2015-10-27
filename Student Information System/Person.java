/*              Person
 * 
 * --------------------------------
 * 
 * -firstName : String
 * -lastName : String
 * -wholeName : String
 * -ID : String
 * 
 * -----------------------------------
 * 
 * +getFirstName() : String
 * +getLastName() : String
 * +getWholeName() : String
 * +getID() : String
 * +setFirstName(String) : void
 * +setLastName(String) : void
 * +setWholeName(String) : void
 * +setID(String) : void
 * +toString() : String
 * +equals(Object) : boolean
 * +print() : void
 * Person()
 * Person(String, String, String, String)
 * 
 */








public class Person 
{
	
	private String firstName, lastName, wholeName, ID;
	
	public Person()
	{
		firstName = "no firstname";
		lastName ="no lastname";
		wholeName = "no name";
		ID = "no ID";
	}
	
	public Person(String lastName, String firstName, String wholeName, String ID)
	{
		if(firstName == null || lastName == null || wholeName == null || ID == null)
		{
			System.out.println("Error creating a person!");
			System.exit(0);
		}
		this.firstName = firstName;
		this.lastName = lastName;
		this.wholeName = wholeName;
		this.ID = ID;
	}
	
	public Person(Person originalObject)
	{
		firstName = originalObject.firstName;
		lastName = originalObject.lastName;
		wholeName = originalObject.wholeName;
		ID = originalObject.ID;
	}
	
	public String getFirstName()
	{
		return firstName;
	}
	
	public String getLastName()
	{
		return lastName;
	}
	
	public String getWholeName()
	{
		return wholeName;
	}
	
	public String getID()
	{
		return ID;
	}
	
	public void setFirstName(String firstName)
	{
		if(firstName == null)
		{
			System.out.println("Error creating a person!");
			System.exit(0);
		}
		else
			this.firstName = firstName;
	}
	
	public void setLastName(String lastName)
	{
		if(lastName == null)
		{
			System.out.println("Error creating a person!");
			System.exit(0);
		}
		else
			this.lastName = lastName;
	}
	
	public void setWholeName(String wholeName)
	{
		if(wholeName == null)
		{
			System.out.println("Error creating a person!");
			System.exit(0);
		}
		else
			this.wholeName = wholeName;
	}
	
	public void setID(String ID)
	{
		if(ID == null)
		{
			System.out.println("Error creating a person!");
			System.exit(0);
		}
		else
			this.ID = ID;
	}
	
	public String toString()
	{
		return (lastName + ", " + firstName + "\t" + ID);
	}
	
	public boolean equals(Object otherObject)
	{
		if(otherObject == null)
		{
			return false;
		}
		else if(getClass() != otherObject.getClass())
		{
			return false;
		}
		else
		{
			Person otherPerson = (Person) otherObject;
			return (lastName.equalsIgnoreCase(otherPerson.lastName) && firstName.equalsIgnoreCase(otherPerson.firstName) && ID.equals(otherPerson.ID));
		}
	}
	
	public void print()
	{
		System.out.println("This person's name is " + lastName + " " + firstName +", ID is " + ID + ".");
	}

}
