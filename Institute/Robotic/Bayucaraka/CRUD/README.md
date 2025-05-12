# Flask To Do List

This project is a simple To Do List application built using the Flask framework. It allows users to create, read, update, and delete tasks, as well as search for tasks by title or subject.

## Project Structure

```
flask-todo-list
├── app
│   ├── __init__.py        # Initializes the Flask application and sets up configuration, database, and routes.
│   ├── routes.py          # Defines the routes for the application.
│   ├── models.py          # Contains the Task model defining the structure of tasks in the database.
│   └── templates          # Contains HTML templates for the application.
│       ├── base.html      # Base template with common HTML structure.
│       ├── index.html     # Main page displaying the list of tasks and form to add new tasks.
│       └── todo.html      # Displays details of a specific task for updates or deletion.
├── static                 # Contains static files such as CSS and JavaScript.
│   ├── css
│   │   └── styles.css     # CSS styles for the application.
│   └── js
│       └── scripts.js     # JavaScript code for client-side interactions.
├── instance               # Contains instance-specific configurations.
│   └── config.py          # Configuration settings for the Flask application.
├── requirements.txt       # Lists dependencies required for the project.
└── README.md              # Documentation for the project.
```

## Setup Instructions

1. Clone the repository:
   ```
   git clone <repository-url>
   cd flask-todo-list
   ```

2. Create a virtual environment:
   ```
   python -m venv venv
   ```

3. Activate the virtual environment:
   - On Windows:
     ```
     venv\Scripts\activate
     ```
   - On macOS/Linux:
     ```
     source venv/bin/activate
     ```

4. Install the required dependencies:
   ```
   pip install -r requirements.txt
   ```

5. Configure the application by editing `instance/config.py` with your database connection details.

6. Run the application:
   ```
   flask run
   ```

## Usage

- Navigate to `http://127.0.0.1:5000/crud` to access the To Do List application.
- Use the interface to add, view, update, and delete tasks.