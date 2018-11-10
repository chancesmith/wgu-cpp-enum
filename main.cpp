#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int ROSTER_SIZE = 5;
const int DAYS_IN_COURSE_SIZE = 3;

enum Degree
{
  SECURITY,
  NETWORK,
  SOFTWARE
};

const string degreeStrings[] = {"SECURITY", "NETWORK", "SOFTWARE"};

///////////Student////////////
#pragma region Student
class Student
{
public:
  ~Student() {}
  Student()
  {
    studentId = "";
    firstName = "";
    lastName = "";
  }
  Student(string StudentId, string FirstName, string LastName, Degree aDegree)
  {
    studentId = StudentId;
    firstName = FirstName;
    lastName = LastName;

    return;
  }
  virtual void print()
  {

    cout << studentId << '\n';
    cout << firstName << '\n';
    cout << lastName << '\n';
    return;
  }

  void setStudentId(string StudentId) { studentId = StudentId; }
  void setFirstName(string FirstName) { firstName = FirstName; }
  void setLastName(string LastName) { lastName = LastName; }
  virtual void setDegreeProgram(Degree aDegree) = 0;

  string getStudentId() { return studentId; }
  string getFirstName() { return firstName; }
  string getLastName() { return lastName; }
  virtual Degree getDegreeProgram() = 0;

protected:
  string studentId;
  string firstName;
  string lastName;
  int numOfDaysToComplete;
  Degree degree;
};
#pragma endregion

///////////SecurityStudent////////////
#pragma region SecurityStudent
class SecurityStudent : public Student
{

public:
  ~SecurityStudent() {}
  SecurityStudent() : Student()
  {
    degree = SECURITY;
  }
  SecurityStudent(string StudentId, string FirstName, string LastName, Degree degree) : Student(StudentId, FirstName, LastName, degree)
  {
    degree = SECURITY;
  }
  Degree getDegreeProgram()
  {
    return SECURITY;
  }
  void setDegreeProgram(Degree aDegree)
  {
    degree = SECURITY;
  }
  void print()
  {
    this->Student::print();
    cout << "SECURITY" << '\n';
  }
};
#pragma endregion

///////////Roster////////////
#pragma region Roster
class Roster
{

public:
  ~Roster() {}
  Roster() { currentPosition = -1; }
  void add(string studentID, string firstName, string lastName, Degree degree)
  {
    Student *student;

    if (SECURITY == degree)
    {
      student = new SecurityStudent();
    }
    else if (NETWORK == degree)
    {
      student = new SecurityStudent();
    }
    else if (SECURITY == degree)
    {
      student = new SecurityStudent();
    }
    else
    {
      std::cout << "Failed to set degree type for: " << studentID << '\n';
      return;
    }

    student->setStudentId(studentID);
    student->setFirstName(firstName);
    student->setLastName(lastName);

    currentPosition += 1;
    classRosterArray[currentPosition] = student;
  }
  void printByDegreeProgram(Degree aDegree)
  {

    bool studentFound = false;
    int studentIndex = 0;

    cout << "Show students with " << degreeStrings[aDegree] << " degree: " << '\n';
    for (int i = 0; i < currentPosition + 1; i += 1)
    {
      if (classRosterArray[i]->getDegreeProgram() == aDegree)
      {
        cout << "Student " << classRosterArray[i]->getFirstName() << " " << '\n';
        studentFound = true;
      }
    }

    if (!studentFound)
    {
      // expected: the above line should print a message saying such a student with this ID was not found.
      cout << "No students found. 🤷‍♂️" << '\n'
           << '\n';
    }
  }

private:
  Student *classRosterArray[ROSTER_SIZE];
  int currentPosition;
};
#pragma endregion

int main()
{
  const string studentData[] =
      {"A1,John,Smith,John1989@gm ail.com,20,30,35,40,SECURITY",
       "A2,Suzan,Erickson,Erickson_1990@gmailcom,19,50,30,40,SECURITY",
       "A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SECURITY",
       "A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY"};

  // const string studentData[] = {"A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SOFTWARE"};

  // Create an instance of the Roster class called classRoster.
  Roster classRoster;
  const int MAX_ATRIBUTES = 9;

  // Add each student to classRoster.
  for (const string &student : studentData)
  {
    string singleStudentData[MAX_ATRIBUTES];
    int i = -1;
    Degree degreeType;

    istringstream ss(student);
    while (!ss.eof())
    {
      i += 1;
      string x;
      getline(ss, x, ','); // split string by comma
      singleStudentData[i] = x;
    }

    // check degree type
    if ("SECURITY" == singleStudentData[8])
    {
      degreeType = SECURITY;
    }
    else if ("NETWORK" == singleStudentData[8])
    {
      degreeType = NETWORK;
    }
    else if ("SOFTWARE" == singleStudentData[8])
    {
      degreeType = SOFTWARE;
    }

    classRoster.add(
        singleStudentData[0], // student id
        singleStudentData[1], // fname
        singleStudentData[2], // lname
        degreeType            // degree
    );
  } // END loop through studentData[]

  classRoster.printByDegreeProgram(SECURITY);

  return 0;
}
