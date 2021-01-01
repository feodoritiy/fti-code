#include <map>
#include <ostream>
#include <vector>

struct Student {
   std::string name;
   int group;
   std::map<std::string, int> exams;


};

std::string str_repeat(std::string string, size_t times) {
   std::string res = "";
   for (size_t i = 0; i < times; i++) {
      res += string;
   }
   return res;
}

std::string student_cell_hr(size_t width) {
   std::string res;

   res = "+-";
   res += str_repeat("-", width);
   res += "-";

   return res;
}

std::string student_cell_content(size_t width, std::string content) {
   std::string res;

   res = "| ";
   res += content;
   res += str_repeat(" ", width - content.length());
   res += " ";

   return res;
}

std::string student_table(std::vector<Student> students) {
   // each student
   size_t width[6] = { 4, 5, 4, 4, 4, 4 };
   std::string titles[6] = { "Name", "Group", "Math", "Phys", "Hist", "Prog" };

   std::vector<std::string> table;

   // detect name width
   for (auto it = students.begin(); it != students.end(); it++) {
      auto student = (*it);
      size_t name_length = student.name.length();
      if (width[0] < name_length) {
         width[0] = name_length;
      }
   }

   int i = 0;
   table.push_back(""); // 0
   table.push_back(""); // 1
   std::string table_close = "";
   for (auto& title : titles) {
      auto hr = student_cell_hr(width[i]);
      auto cont = student_cell_content(width[i], title);

      table[0] += hr;
      table_close += hr;
      table[1] += cont;

      i++;
   }
   table[0] += "+";
   table[1] += "|";

   i = 0;
   for (auto& student : students) {
      size_t i0 = 2 + i * 2, i1 = 3 + i * 2;
      table.push_back("");
      table.push_back("");

      table[i0] += student_cell_hr(width[0]);
      table[i1] += student_cell_content(width[0], student.name);

      table[i0] += student_cell_hr(width[1]);
      table[i1] += student_cell_content(width[1], std::to_string(student.group));

      table[i0] += student_cell_hr(width[2]);
      table[i1] += student_cell_content(width[2], std::to_string(student.exams["mathematics"]));

      table[i0] += student_cell_hr(width[3]);
      table[i1] += student_cell_content(width[3], std::to_string(student.exams["physics"]));

      table[i0] += student_cell_hr(width[4]);
      table[i1] += student_cell_content(width[4], std::to_string(student.exams["history"]));

      table[i0] += student_cell_hr(width[5]);
      table[i1] += student_cell_content(width[5], std::to_string(student.exams["programming"]));

      table[i0] += "+";
      table[i1] += "|";

      i++;
   }

   table.push_back(table_close + "+");

   std::string res = "";
   for (auto& table_row : table) {
      res += table_row + "\n";
   }

   return res;
}

std::ostream& operator << (std::ostream& o, Student student) {
   std::vector<Student> students = { student };
   return o << student_table(students);
}

bool operator > (Student a, Student b) {
   return a.name > b.name;
}
bool operator < (Student a, Student b) {
   return a.name < b.name;
}

std::ostream& operator << (std::ostream& o, std::vector<Student> students) {
   return o << student_table(students);
}

// mathematics, physics, history, programming
std::vector<Student> students = {
   {"Nikonov F", 1, {
      {"mathematics", 3},
      {"physics", 3},
      {"history", 3},
      {"programming", 3}
   }},
   {"Nikonov G", 3, {
      {"mathematics", 4},
      {"physics", 3},
      {"history", 4},
      {"programming", 4}
   }},
   {"Nikonov H", 1, {
      {"mathematics", 2},
      {"physics", 4},
      {"history", 5},
      {"programming", 4}
   }},
   {"Nikonov I", 3, {
      {"mathematics", 5},
      {"physics", 3},
      {"history", 3},
      {"programming", 3}
   }},
   {"Nikonov J", 1, {
      {"mathematics", 4},
      {"physics", 4},
      {"history", 5},
      {"programming", 4}
   }},
   {"Nikonov K", 2, {
      {"mathematics", 2},
      {"physics", 2},
      {"history", 4},
      {"programming", 4}
   }},
   {"Nikonov L", 4, {
      {"mathematics", 3},
      {"physics", 3},
      {"history", 4},
      {"programming", 3}
   }},
   {"Nikonov M", 8, {
      {"mathematics", 4},
      {"physics", 4},
      {"history", 3},
      {"programming", 4}
   }},
   {"Nikonov N", 1, {
      {"mathematics", 2},
      {"physics", 4},
      {"history", 4},
      {"programming", 4}
   }},
   {"Nikonov O", 9, {
      {"mathematics", 2},
      {"physics", 4},
      {"history", 3},
      {"programming", 5}
   }},
};