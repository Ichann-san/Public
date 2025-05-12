document.addEventListener('DOMContentLoaded', function() {
    const taskForm = document.getElementById('task-form');
    const taskList = document.getElementById('task-list');

    taskForm.addEventListener('submit', function(event) {
        event.preventDefault();
        const formData = new FormData(taskForm);
        const taskData = {
            title: formData.get('title'),
            description: formData.get('description'),
            subject: formData.get('subject'),
            status: 'Pending',
            tags: formData.get('tags').split(',')
        };

        fetch('/add-task', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(taskData)
        })
        .then(response => response.json())
        .then(data => {
            if (data.success) {
                addTaskToList(data.task);
                taskForm.reset();
            }
        });
    });

    function addTaskToList(task) {
        const listItem = document.createElement('li');
        listItem.textContent = `${task.title} - ${task.status}`;
        taskList.appendChild(listItem);
    }

    // Additional functions for updating and deleting tasks can be added here
});