$(document).ready(function() {
    // Form submission handler
    $("form[name='ContactForm']").submit(function(e) {
        e.preventDefault(); // Prevent the default form submission
        
        // Get form data
        var name = $("#name").val().trim();
        var email = $("#email").val().trim();
        var message = $("#message").val().trim();
        var $messageBox = $(".message_box");
        
        // Validate form data
        if(name === '') {
            $messageBox.html('<div class="alert alert-danger">Please enter your name.</div>');
            return false;
        }
        
        if(email === '') {
            $messageBox.html('<div class="alert alert-danger">Please enter your email.</div>');
            return false;
        }
        
        if(!isValidEmail(email)) {
            $messageBox.html('<div class="alert alert-danger">Please enter a valid email address.</div>');
            return false;
        }
        
        if(message === '') {
            $messageBox.html('<div class="alert alert-danger">Please enter your message.</div>');
            return false;
        }
        
        // Show loading message
        $messageBox.html('<div class="alert alert-info">Sending message...</div>');
        
        // Send data using AJAX
        $.ajax({
            type: "POST",
            url: "process.php", // Create this PHP file to handle the submission
            data: {
                name: name,
                email: email,
                message: message
            },
            success: function(response) {
                // Clear the form
                $("#name").val('');
                $("#email").val('');
                $("#message").val('');
                
                // Show success message
                $messageBox.html('<div class="alert alert-success">Your message has been sent successfully!</div>');
            },
            error: function() {
                // Show error message
                $messageBox.html('<div class="alert alert-danger">There was an error sending your message. Please try again.</div>');
            }
        });
    });
    
    // Email validation function
    function isValidEmail(email) {
        var regex = /^([a-zA-Z0-9_.+-])+\@(([a-zA-Z0-9-])+\.)+([a-zA-Z0-9]{2,4})+$/;
        return regex.test(email);
    }
});