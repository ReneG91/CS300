# CS300
Reflection

What was the problem you were solving in the projects for this course?
The problem I was solving in these projects was designing and implementing an advising assistance program for computer science courses. The program needed to store course data, list all courses in alphanumeric order, and allow a user to search for a specific course and its prerequisites. To do this effectively, I had to evaluate and apply different data structures—including vectors, hash tables, and binary search trees—to determine the best way to organize and retrieve course information efficiently.

How did you approach the problem?
I approached the problem by first creating pseudocode to design the overall flow of the program. This allowed me to focus on the logic of how data would be stored, traversed, and displayed before writing actual code. Understanding the strengths and weaknesses of each data structure was central to my approach. Vectors offered simple sequential storage, hash tables provided faster lookups with good collision handling, and binary search trees supported naturally sorted output. Comparing these approaches helped me decide which structure best fit the project requirements.

How did you overcome any roadblocks you encountered while going through the activities or project?
One roadblock I encountered was dealing with file input and parsing CSV data correctly. Early on, I ran into issues where the program failed to read the file properly, causing crashes or incomplete data loads. I overcame this by breaking down the input step into smaller parts: verifying the file path, stripping whitespace, and carefully splitting each line by commas. Another challenge was managing null pointers when traversing the binary search tree. I fixed this by adding proper checks before dereferencing nodes, which made the program more robust and stable.

How has your work on this project expanded your approach to designing software and developing programs?
This project expanded my approach by showing me how important it is to start with design and pseudocode before writing actual code. It reinforced the idea that choosing the right data structure directly impacts performance, scalability, and ease of implementation. I also became more aware of writing modular functions that each handle one responsibility, which made debugging and testing much easier.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
Working on this project helped me appreciate the value of writing code that is clean and adaptable. I learned to use clear variable names, consistent formatting, and meaningful comments that explain why a change was made rather than just what the code does. I also structured the code so that new features, such as adding more course data or expanding menu options, could be included with minimal changes. This experience will carry over into future programming tasks, where maintainability and readability are just as important as functionality.
