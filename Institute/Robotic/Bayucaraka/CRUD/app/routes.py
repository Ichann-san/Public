from flask import render_template, request, redirect, url_for, flash
from .models import Task
from . import db

@app.route('/')
def index():
    tasks = Task.query.all()
    return render_template('index.html', tasks=tasks)

@app.route('/add', methods=['POST'])
def add_task():
    title = request.form.get('title')
    description = request.form.get('description')
    subject = request.form.get('subject')
    new_task = Task(title=title, description=description, subject=subject)
    db.session.add(new_task)
    db.session.commit()
    flash('Task added successfully!')
    return redirect(url_for('index'))

@app.route('/update/<int:task_id>', methods=['POST'])
def update_task(task_id):
    task = Task.query.get(task_id)
    task.status = request.form.get('status')
    db.session.commit()
    flash('Task updated successfully!')
    return redirect(url_for('index'))

@app.route('/delete/<int:task_id>')
def delete_task(task_id):
    task = Task.query.get(task_id)
    db.session.delete(task)
    db.session.commit()
    flash('Task deleted successfully!')
    return redirect(url_for('index'))

@app.route('/search', methods=['GET'])
def search_tasks():
    query = request.args.get('query')
    tasks = Task.query.filter(Task.title.contains(query)).all()
    return render_template('index.html', tasks=tasks)