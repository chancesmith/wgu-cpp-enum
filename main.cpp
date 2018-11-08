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

    cout << studentId << endl;
    cout << firstName << endl;
    cout << lastName << endl;
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
    cout << "SECURITY" << endl;
  }
};
#pragma endregion

///////////Roster////////////
#pragma region Roster
class Roster
{

public:
  void add(string studentID, string firstName, string lastName, string degree)
  {
    Student *student;

    if ("SECURITY" == degree)
      student = new SecurityStudent();

    student->setStudentId(studentID);
    student->setFirstName(firstName);
    student->setLastName(lastName);
    student->setLastName(lastName);

    currentPosition += 1;
    classRosterArray[currentPosition] = *student;
  }
  void printByDegreeProgram(Degree aDegree)
  {

    bool studentFound = false;
    int studentIndex = 0;

    for (int i = 0; i < currentPosition; i += 1)
    {
      if (classRosterArray[i].getDegreeProgram() == aDegree)
      {
        studentFound = true;
        studentIndex = i;
      }
    }

    std::cout << "Show students with " << aDegree << "degree: " << endl;
    if (studentFound)
    {

      cout << "Student " << classRosterArray[studentIndex].getFirstName() << " " << endl;
    }
    else
    {
      // expected: the above line should print a message saying such a student with this ID was not found.
      std::cout << "Such a student with this ID was not found. 🤷‍♂️" << endl
                << endl;
    }
  }

private:
  Student classRosterArray[ROSTER_SIZE];
  int currentPosition = 0;
};
#pragma endregion

int main()
{
  // const string studentData[] =
  //     {"A1,John,Smith,John1989@gm ail.com,20,30,35,40,SECURITY",
  //      "A2,Suzan,Erickson,Erickson_1990@gmailcom,19,50,30,40,NETWORK",
  //      "A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SOFTWARE",
  //      "A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY"};

  const string studentData[] = {"A1,John,Smith,John1989@gm ail.com,20,30,35,40,SECURITY"};

  // Create an instance of the Roster class called classRoster.
  Roster classRoster;
  const int MAX_ATRIBUTES = 9;

  // Add each student to classRoster.
  for (const string &student : studentData)
  {
    string singleStudentData[MAX_ATRIBUTES];
    int i = -1;

    istringstream ss(student);
    while (!ss.eof())
    {
      i += 1;
      string x;
      getline(ss, x, ','); // split string by comma
      singleStudentData[i] = x;
    }

    // TODO: convert degree to enum and pass into pass Roster.add()
    classRoster.add(
        singleStudentData[0], // student id
        singleStudentData[1], // fname
        singleStudentData[2], // lname
        singleStudentData[8]  // degree
    );
  } // END loop through studentData[]

  classRoster.printByDegreeProgram(SOFTWARE);

  return 0;
}
