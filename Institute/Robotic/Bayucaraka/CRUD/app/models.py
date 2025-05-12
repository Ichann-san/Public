from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()

class Task(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String(100), nullable=False)
    description = db.Column(db.Text, nullable=True)
    subject = db.Column(db.String(100), nullable=True)
    status = db.Column(db.String(20), default='Pending')
    tags = db.Column(db.String(200), nullable=True)  # Optional tags as a comma-separated string

    def __repr__(self):
        return f'<Task {self.title}>'